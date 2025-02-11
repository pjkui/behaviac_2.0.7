#include "behaviac/agent/agent.h"
#include "behaviac/htn/agentstate.h"

namespace behaviac
{
    behaviac::Mutex					AgentState::ms_mutex;
    behaviac::vector<AgentState*>	AgentState::pool;

    AgentState::AgentState() : parent(NULL), m_forced(false), m_pushed(0)
    {
    }

    AgentState::AgentState(AgentState* parent) : parent(NULL), m_forced(false), m_pushed(0)
    {
        this->parent = parent;
    }

    AgentState::~AgentState()
    {
        //this->Pop();
    }

    int AgentState::Depth()
    {
        int d = 1;

        if (this->state_stack.size() > 0)
        {
            for (int i = this->state_stack.size() - 1; i >= 0; --i)
            {
                AgentState* t = this->state_stack[i];
#if BEHAVIAC_ENABLE_PUSH_OPT
                d += 1 + t->m_pushed;
#else
                d += 1;
#endif
            }
        }

        return d;
    }

    int AgentState::Top()
    {
        if (this->state_stack.size() > 0)
        {
            return this->state_stack.size() - 1;
        }

        return -1;
    }

    AgentState* AgentState::Push(bool bForcePush)
    {
#if BEHAVIAC_ENABLE_PUSH_OPT

        if (!bForcePush)
        {
            //if the top has nothing new added, to use it again
            if (this->state_stack.size() > 0)
            {
                AgentState* t = this->state_stack[this->state_stack.size() - 1];

                if (!t->m_forced && t->Vars().size() == 0)
                {
                    t->m_pushed++;
                    return t;
                }
            }
        }

#endif

        AgentState* newly = NULL;

        {
            behaviac::ScopedLock lock(ms_mutex);

            if (pool.size() > 0)
            {
                //last one
                newly = pool[pool.size() - 1];
                pool.pop_back();
                //set the parent
                newly->parent = this;

            }
            else
            {
                newly = BEHAVIAC_NEW AgentState(this);
            }

#if BEHAVIAC_ENABLE_PUSH_OPT
            newly->m_forced = bForcePush;
#endif

            if (bForcePush)
            {
                Variables::CopyTo(NULL, *newly);
            }
        }

        //add the newly one at the end of the list as the top
        this->state_stack.push_back(newly);

        return newly;
    }

    void AgentState::Pop()
    {
        if (this->parent == 0)
        {
            //if parent is 0, it is not created on the heap and not on the stack, not pop
            return;
        }

#if BEHAVIAC_ENABLE_PUSH_OPT

        if (this->m_pushed > 0)
        {
            this->m_pushed--;

            if (this->m_variables.size() > 0)
            {
                this->m_variables.clear();
                return;
            }

            return;
        }

#endif

        if (this->state_stack.size() > 0)
        {
            AgentState* top = this->state_stack[this->state_stack.size() - 1];
            top->Pop();
            return;
        }

        this->Clear();
        //Debug.Check(this->state_stack == NULL);
        BEHAVIAC_ASSERT(this->state_stack.size() == 0);
        //Debug.Check(this.parent != NULL);
        BEHAVIAC_ASSERT(this->parent != NULL);
        this->parent->PopTop();
        this->parent = NULL;

        {
            behaviac::ScopedLock lock(ms_mutex);
            //BEHAVIAC_ASSERT(!pool.Contains(this));
            pool.push_back(this);
        }
    }

    void AgentState::PopTop()
    {
        BEHAVIAC_ASSERT(this->state_stack.size() > 0);
        //remove the last one
        this->state_stack.pop_back();//
    }

    void AgentState::Log(Agent* pAgent, bool bForce)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(bForce);
#if !BEHAVIAC_RELEASE

        if (Config::IsLoggingOrSocketing())
        {
            if (this->state_stack.size() > 0)
            {
                map<behaviac::string, bool> logged;

                for (int i = this->state_stack.size() - 1; i >= 0; --i)
                {
                    AgentState* t = this->state_stack[i];
                    behaviac::map<uint32_t, IVariable*>& _value = t->Vars();

                    for (behaviac::map<uint32_t, IVariable*>::iterator it = _value.begin(); it != _value.end(); it++)
                    {
                        IVariable* pVar = it->second;

                        if (bForce || pVar->IsChanged())
                        {
                            if (logged.find(pVar->Name()) != logged.end())
                            {
                                //logged.insert(pVar->Name(), true);
                                logged.insert(map<behaviac::string, bool>::value_type(pVar->Name(), true));
                            }
                        }
                    }

                    //foreach(IVariable pVar in t.Vars.Values)
                    //{
                    //	if (bForce || pVar.IsChanged())
                    //	{
                    //		if (!logged.ContainsKey(pVar.Name))
                    //		{
                    //			pVar.Log(pAgent);
                    //			logged.Add(pVar.Name, true);
                    //		}
                    //	}
                    //}
                }//end of for

            }
            else
            {
                //base.Log(pAgent, bForce);
                Variables::Log(pAgent, bForce);
            }
        }

#endif
    }
}

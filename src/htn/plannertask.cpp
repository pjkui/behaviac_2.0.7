/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tencent is pleased to support the open source community by making behaviac available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at http://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "behaviac/agent/agent.h"

#include "behaviac/htn/plannertask.h"

#include "behaviac/behaviortree/nodes/actions/action.h"
#include "behaviac/behaviortree/nodes/composites/sequence.h"
#include "behaviac/behaviortree/nodes/composites/selector.h"
#include "behaviac/behaviortree/nodes/composites/parallel.h"
#include "behaviac/behaviortree/nodes/decorators/decoratorloop.h"
#include "behaviac/behaviortree/nodes/decorators/decoratoriterator.h"
#include "behaviac/htn/agentstate.h"
#include "behaviac/behaviortree/nodes/composites/referencebehavior.h"
#include "behaviac/base/object/method.h"
#include "behaviac/htn/method.h"
#include "behaviac/htn/task.h"
namespace behaviac
{
    PlannerTask::PlannerTask() : Parent(NULL)
    { }

    PlannerTask::~PlannerTask()
    { }

    PlannerTask::PlannerTask(BehaviorNode* node, Agent* pAgent) : BehaviorTask(), Parent(NULL)
    {
        BEHAVIAC_UNUSED_VAR(node);
        BEHAVIAC_UNUSED_VAR(pAgent);

        this->m_node = node;
        this->m_id = this->m_node->GetId();
    }

    PlannerTask::PlannerTaskFactory_t* PlannerTask::ms_factory;
    template<typename T>
    PlannerTask* PlannerTaskCreator(BehaviorNode* node, Agent* pAgent)
    {
        PlannerTask* task = BEHAVIAC_NEW T(node, pAgent);

        return task;
    }

    template<typename T, typename TT>
    void PlannerTask::Register()
    {
        const char* typeName = T::GetClassTypeName();
        CStringID typeNameId(typeName);
        ms_factory->insert(std::pair<CStringID, TaskCreator>(typeNameId, PlannerTaskCreator<TT>));
    }

    PlannerTask* PlannerTask::Create(BehaviorNode* node, Agent* pAgent)
    {
        if (ms_factory == 0)
        {
            ms_factory = BEHAVIAC_NEW PlannerTaskFactory_t();

            Register<Action, PlannerTaskAction>();
            Register<Task, PlannerTaskTask>();
            Register<Method, PlannerTaskMethod>();
            Register<Sequence, PlannerTaskSequence>();
            Register<Selector, PlannerTaskSelector>();
            Register<Parallel, PlannerTaskParallel>();
            Register<ReferencedBehavior, PlannerTaskReference>();
            Register<DecoratorLoop, PlannerTaskLoop>();
            Register<DecoratorIterator, PlannerTaskIterator>();
        }

        const PlannerTaskFactory_t& factory = (*ms_factory);

        //const char* objectTypeName = node->GetObjectTypeName();

        const SHierarchyInfo* pHierarchy = node->GetHierarchyInfo();

        uint32_t hiecharyLevels = pHierarchy->m_hierarchyLevel;

        TaskCreator creator = 0;

        for (int i = (int)(hiecharyLevels - 1); i >= 0; --i)
        {
            const CStringID& typeNameId = pHierarchy->m_hierarchy[i];
            PlannerTaskFactory_t::const_iterator it = factory.find(typeNameId);

            if (it != factory.end())
            {
                creator = it->second;
                break;
            }
        }

        if (creator != 0)
        {
            PlannerTask* task = creator(node, pAgent);

            return task;
        }

        return NULL;
    }

    void PlannerTask::Cleanup()
    {
        if (ms_factory)
        {
            ms_factory->clear();
            BEHAVIAC_DELETE ms_factory;
            ms_factory = 0;
        }
    }

    bool PlannerTask::IsHigherPriority(PlannerTask* other)
    {
        BEHAVIAC_UNUSED_VAR(other);
        return true;
    }
    void PlannerTask::traverse(NodeHandler_t handler, Agent* pAgent, void* user_data)
    {
        BEHAVIAC_UNUSED_VAR(handler);
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(user_data);
    }

    void PlannerTask::Init(const BehaviorNode* node)
    {
        BEHAVIAC_UNUSED_VAR(node);
    };
    void PlannerTask::copyto(BehaviorTask* target) const
    {
        BEHAVIAC_UNUSED_VAR(target);
    };
    void PlannerTask::save(ISerializableNode* node) const
    {
        BEHAVIAC_UNUSED_VAR(node);
    };
    void PlannerTask::load(ISerializableNode* node)
    {
        BEHAVIAC_UNUSED_VAR(node);
    };
    EBTStatus PlannerTask::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(childStatus);
        BEHAVIAC_ASSERT(false);
        return BT_INVALID;
    };

    //////////////////////////////////////////////////////////////
    //implement all the methods in PlannarTaskAction
    //////////////////////////////////////////////////////////////
    //private object[] ParamsValue { get; set; }

    PlannerTaskAction::PlannerTaskAction(BehaviorNode* node, Agent* pAgent) : PlannerTask(node, pAgent)
    {
        //BEHAVIAC_ASSERT(node is Action);
        BEHAVIAC_ASSERT(Action::DynamicCast(node) != 0);
        //Action action = node as Action;
    }

    bool PlannerTaskAction::onenter(Agent* pAgent)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        //BEHAVIAC_ASSERT(true);
        return true;
    }

    void PlannerTaskAction::onexit(Agent* pAgent, EBTStatus s)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(s);
        //BEHAVIAC_ASSERT(true);
        //base.onexit(pAgent, s);
        PlannerTask::onexit(pAgent, s);
    }

    EBTStatus PlannerTaskAction::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(childStatus);

        BEHAVIAC_ASSERT(Action::DynamicCast(this->m_node) != 0);

        Action* action = (Action*)this->m_node;

        //this->m_status = action.Execute(pAgent, this->ParamsValue);
        this->m_status = action->Execute(pAgent, childStatus);

        return this->m_status;
    }

    /////////////////////////////////////////////////////////
    /// implement all the methods in the PlannerTaskComplex
    /////////////////////////////////////////////////////////

    void PlannerTaskComplex::AddChild(PlannerTask* task)
    {
        this->m_children.push_back(task);
        task->Parent = this;
    }

    void PlannerTaskComplex::RemoveChild(PlannerTask* childTask)
    {
        BEHAVIAC_ASSERT(this->m_children.size() > 0 && this->m_children[this->m_children.size() - 1] == childTask);

        //this->m_children.Remove(childTask);
        for (behaviac::vector<BehaviorTask*>::iterator it = this->m_children.begin(); it != this->m_children.end(); it++)
        {
            if (*it == childTask)
            {
                m_children.erase(it);
            }
        }
    }

    PlannerTaskComplex::PlannerTaskComplex(BehaviorNode* node, Agent* pAgent)
        : PlannerTask(node, pAgent), m_activeChildIndex(-1)
    {
    }

    //~PlannerTaskComplex()
    //{
    //    foreach (BehaviorTask t in this->m_children)
    //    {
    //        BehaviorTask.DestroyTask(t);
    //    }

    //    this->m_children.Clear();
    //}

    bool PlannerTaskComplex::onenter(Agent* pAgent)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        this->m_activeChildIndex = 0;
        return true;
    }

    void PlannerTaskComplex::onexit(Agent* pAgent, EBTStatus s)
    {
        PlannerTask::onexit(pAgent, s);
    }

    EBTStatus PlannerTaskComplex::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(childStatus);

        BEHAVIAC_ASSERT(false);
        return BT_SUCCESS;
    }

    /////////////////////////////////////////////
    //PlannerTaskSequence
    /////////////////////////////////////////////

    PlannerTaskSequence::PlannerTaskSequence(BehaviorNode* node, Agent* pAgent)
        : PlannerTaskComplex(node, pAgent)
    {
    }

    EBTStatus PlannerTaskSequence::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_ASSERT(Sequence::DynamicCast(this->m_node) != 0);
        Sequence* node = (Sequence*) this->m_node;

        EBTStatus s = node->SequenceUpdate(pAgent, childStatus, this->m_activeChildIndex, this->m_children);

        return s;
    }

    PlannerTaskSelector::PlannerTaskSelector(BehaviorNode* node, Agent* pAgent)
        : PlannerTaskComplex(node, pAgent)
    {
    }

    EBTStatus PlannerTaskSelector::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_ASSERT(Selector::DynamicCast(this->m_node) != 0);
        Selector* node = (Selector*) this->m_node;

        EBTStatus s = node->SelectorUpdate(pAgent, childStatus, this->m_activeChildIndex, this->m_children);

        return s;
    }

    PlannerTaskParallel::PlannerTaskParallel(BehaviorNode* node, Agent* pAgent)
        : PlannerTaskComplex(node, pAgent)
    {
    }

    EBTStatus PlannerTaskParallel::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(childStatus);

        BEHAVIAC_ASSERT(Parallel::DynamicCast(this->m_node) != 0);
        Parallel* node = (Parallel*)this->m_node;
        EBTStatus s = node->ParallelUpdate(pAgent, this->m_children);

        return s;
    }

    PlannerTaskLoop::PlannerTaskLoop(BehaviorNode* node, Agent* pAgent)
        : PlannerTaskComplex(node, pAgent)
    {
    }

    bool PlannerTaskLoop::onenter(Agent* pAgent)
    {
        PlannerTaskComplex::onenter(pAgent);

        //don't reset the m_n if it is restarted
        if (this->m_n == 0)
        {
            int count = this->GetCount(pAgent);

            if (count == 0)
            {
                return false;
            }

            this->m_n = count;

        }
        else
        {
            BEHAVIAC_ASSERT(true);
        }

        return true;
    }

    int PlannerTaskLoop::GetCount(Agent* pAgent)
    {
        BEHAVIAC_ASSERT(DecoratorLoop::DynamicCast(this->GetNode()) != 0);
        DecoratorLoop* pDecoratorCountNode = (DecoratorLoop*)(this->GetNode());

        return pDecoratorCountNode != NULL ? pDecoratorCountNode->GetCount(pAgent) : 0;
    }

    EBTStatus PlannerTaskLoop::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(childStatus);

        BEHAVIAC_ASSERT(DecoratorLoop::DynamicCast(this->m_node) != 0);
        // DecoratorLoop* node = (DecoratorLoop*)this->m_node;
        BEHAVIAC_ASSERT(this->m_children.size() == 1);
        BehaviorTask* c = this->m_children[0];

        EBTStatus s = c->exec(pAgent);
        BEHAVIAC_UNUSED_VAR(s);

        if (this->m_n > 0)
        {
            this->m_n--;

            if (this->m_n == 0)
            {
                return BT_SUCCESS;
            }

            return BT_RUNNING;
        }

        if (this->m_n == -1)
        {
            return BT_RUNNING;
        }

        BEHAVIAC_ASSERT(this->m_n == 0);

        return BT_SUCCESS;
    }

    PlannerTaskIterator::PlannerTaskIterator(BehaviorNode* node, Agent* pAgent)
        : PlannerTaskComplex(node, pAgent)
    {
    }

    bool PlannerTaskIterator::onenter(Agent* pAgent)
    {
        bool bOk = PlannerTaskComplex::onenter(pAgent);

        DecoratorIterator* pNode = (DecoratorIterator*)this->m_node;
        int count = 0;
        bOk = pNode->IterateIt(pAgent, this->m_index, count);

        return bOk;
    }

    EBTStatus PlannerTaskIterator::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(childStatus);

        BEHAVIAC_ASSERT(DecoratorIterator::DynamicCast(this->m_node) != 0);
        // DecoratorIterator* pNode = (DecoratorIterator*)this->m_node;

        BEHAVIAC_ASSERT(this->m_children.size() == 1);
        BehaviorTask* c = this->m_children[0];

        EBTStatus s = c->exec(pAgent);

        return s;
    }

    PlannerTaskReference::PlannerTaskReference(BehaviorNode* node, Agent* pAgent)
		: PlannerTaskComplex(node, pAgent), currentState(0), m_subTree(0)
    {
#if !BEHAVIAC_RELEASE
        _logged = false;
#endif
    }

    bool PlannerTaskReference::CheckPreconditions(Agent* pAgent, bool bIsAlive)
    {
        this->currentState = pAgent->m_variables.Push(false);
        BEHAVIAC_ASSERT(this->currentState != NULL);

        bool bOk = PlannerTaskComplex::CheckPreconditions(pAgent, bIsAlive);

        if (!bOk)
        {
            this->currentState->Pop();
            this->currentState = NULL;
        }

        return bOk;
    }

    bool PlannerTaskReference::onenter(Agent* pAgent)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);

        BEHAVIAC_ASSERT(ReferencedBehavior::DynamicCast(this->m_node) != 0);
        ReferencedBehavior* pNode = (ReferencedBehavior*)this->m_node;
        BEHAVIAC_UNUSED_VAR(pNode);
        BEHAVIAC_ASSERT(pNode != NULL);

#if !BEHAVIAC_RELEASE
         _logged = false;
#endif
		pNode->SetTaskParams(pAgent);
		this->m_subTree = Workspace::GetInstance()->CreateBehaviorTreeTask(pNode->GetReferencedTree());

        return true;
    }

    void PlannerTaskReference::onexit(Agent* pAgent, EBTStatus status)
    {
        BEHAVIAC_UNUSED_VAR(pAgent);
        BEHAVIAC_UNUSED_VAR(status);

        BEHAVIAC_ASSERT(ReferencedBehavior::DynamicCast(this->m_node) != 0);
        ReferencedBehavior* pNode = (ReferencedBehavior*)this->m_node;
        BEHAVIAC_UNUSED_VAR(pNode);

        BEHAVIAC_ASSERT(pNode != NULL);

		this->m_subTree = 0;

#if !BEHAVIAC_RELEASE
        pAgent->LogReturnTree(pNode->GetReferencedTree());
#endif

        BEHAVIAC_ASSERT(this->currentState != NULL);
        this->currentState->Pop();
    }

    EBTStatus PlannerTaskReference::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(childStatus);

        BEHAVIAC_ASSERT(ReferencedBehavior::DynamicCast(this->m_node) != 0);
        //BEHAVIAC_ASSERT(this->m_node is ReferencedBehavior);
        ReferencedBehavior* pNode = (ReferencedBehavior*)this->m_node;
        //ReferencedBehavior pNode = this->m_node as ReferencedBehavior;
        BEHAVIAC_ASSERT(pNode != NULL);

        EBTStatus status = BT_RUNNING;

        pNode->SetTaskParams(pAgent);

        if (pNode->RootTaskNode() == NULL)
        {
			status = this->m_subTree->exec(pAgent);
        }
        else
        {
#if !BEHAVIAC_RELEASE
            if (!_logged)
            {
				pAgent->LogJumpTree(pNode->GetReferencedTree());
				_logged = true;
            }
#endif
            BEHAVIAC_ASSERT(this->m_children.size() == 1);
            BehaviorTask* c = this->m_children[0];

            status = c->exec(pAgent);
        }

        return status;
    }

    PlannerTaskTask::PlannerTaskTask(BehaviorNode* node, Agent* pAgent)
        : PlannerTaskComplex(node, pAgent)
    {
    }

    bool PlannerTaskTask::onenter(Agent* pAgent)
    {
        this->m_node->GetParent()->InstantiatePars(pAgent);
        return true;
    }

    void PlannerTaskTask::onexit(Agent* pAgent, EBTStatus s)
    {
        this->m_node->GetParent()->UnInstantiatePars(pAgent);
        PlannerTaskComplex::onexit(pAgent, s);
    }

    EBTStatus PlannerTaskTask::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(childStatus);
        //BEHAVIAC_ASSERT(Task::Da);
        // Task* pNode = (Task*) this->m_node;// as Task;

        BEHAVIAC_ASSERT(this->m_children.size() == 1);
        BehaviorTask* c = this->m_children[0];

        EBTStatus s = c->exec(pAgent);

        return s;
    }

    PlannerTaskMethod::PlannerTaskMethod(BehaviorNode* node, Agent* pAgent)
        : PlannerTaskComplex(node, pAgent)
    {
    }

    EBTStatus PlannerTaskMethod::update(Agent* pAgent, EBTStatus childStatus)
    {
        BEHAVIAC_UNUSED_VAR(childStatus);
        //BEHAVIAC_ASSERT(Method::D);

        // Method* pNode = (Method*)this->m_node;

        BEHAVIAC_ASSERT(this->m_children.size() == 1);
        BehaviorTask* c = this->m_children[0];

        EBTStatus s = c->exec(pAgent);

        return s;
    }
}

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

namespace Behaviac.Design
{
    partial class ControlsDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ControlsDialog));
            this.webBrowser = new System.Windows.Forms.WebBrowser();
            this.buttonClose = new System.Windows.Forms.Button();
            this.checkBoxNext = new System.Windows.Forms.CheckBox();
            this.workspaceLabel = new System.Windows.Forms.Label();
            this.workspace1Button = new System.Windows.Forms.Button();
            this.workspace2Button = new System.Windows.Forms.Button();
            this.workspace4Button = new System.Windows.Forms.Button();
            this.workspace3Button = new System.Windows.Forms.Button();
            this.nodeRefDocButton = new System.Windows.Forms.Button();
            this.insideDocButton = new System.Windows.Forms.Button();
            this.tutorialDocbutton = new System.Windows.Forms.Button();
            this.overviewDocButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.performenceDocButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // webBrowser
            // 
            resources.ApplyResources(this.webBrowser, "webBrowser");
            this.webBrowser.Name = "webBrowser";
            this.webBrowser.Url = new System.Uri("", System.UriKind.Relative);
            this.webBrowser.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.webBrowser_PreviewKeyDown);
            // 
            // buttonClose
            // 
            resources.ApplyResources(this.buttonClose, "buttonClose");
            this.buttonClose.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(65)))), ((int)(((byte)(65)))), ((int)(((byte)(65)))));
            this.buttonClose.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkGray;
            this.buttonClose.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DarkGray;
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.UseVisualStyleBackColor = false;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // checkBoxNext
            // 
            resources.ApplyResources(this.checkBoxNext, "checkBoxNext");
            this.checkBoxNext.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(65)))), ((int)(((byte)(65)))), ((int)(((byte)(65)))));
            this.checkBoxNext.Name = "checkBoxNext";
            this.checkBoxNext.UseVisualStyleBackColor = false;
            // 
            // workspaceLabel
            // 
            resources.ApplyResources(this.workspaceLabel, "workspaceLabel");
            this.workspaceLabel.Name = "workspaceLabel";
            // 
            // workspace1Button
            // 
            resources.ApplyResources(this.workspace1Button, "workspace1Button");
            this.workspace1Button.Name = "workspace1Button";
            this.workspace1Button.UseVisualStyleBackColor = true;
            this.workspace1Button.Click += new System.EventHandler(this.workspace1Button_Click);
            // 
            // workspace2Button
            // 
            resources.ApplyResources(this.workspace2Button, "workspace2Button");
            this.workspace2Button.Name = "workspace2Button";
            this.workspace2Button.UseVisualStyleBackColor = true;
            this.workspace2Button.Click += new System.EventHandler(this.workspace2Button_Click);
            // 
            // workspace4Button
            // 
            resources.ApplyResources(this.workspace4Button, "workspace4Button");
            this.workspace4Button.Name = "workspace4Button";
            this.workspace4Button.UseVisualStyleBackColor = true;
            this.workspace4Button.Click += new System.EventHandler(this.workspace4Button_Click);
            // 
            // workspace3Button
            // 
            resources.ApplyResources(this.workspace3Button, "workspace3Button");
            this.workspace3Button.Name = "workspace3Button";
            this.workspace3Button.UseVisualStyleBackColor = true;
            this.workspace3Button.Click += new System.EventHandler(this.workspace3Button_Click);
            // 
            // nodeRefDocButton
            // 
            resources.ApplyResources(this.nodeRefDocButton, "nodeRefDocButton");
            this.nodeRefDocButton.Name = "nodeRefDocButton";
            this.nodeRefDocButton.UseVisualStyleBackColor = true;
            this.nodeRefDocButton.Click += new System.EventHandler(this.nodeRefDocButton_Click);
            // 
            // insideDocButton
            // 
            resources.ApplyResources(this.insideDocButton, "insideDocButton");
            this.insideDocButton.Name = "insideDocButton";
            this.insideDocButton.UseVisualStyleBackColor = true;
            this.insideDocButton.Click += new System.EventHandler(this.insideDocButton_Click);
            // 
            // tutorialDocbutton
            // 
            resources.ApplyResources(this.tutorialDocbutton, "tutorialDocbutton");
            this.tutorialDocbutton.Name = "tutorialDocbutton";
            this.tutorialDocbutton.UseVisualStyleBackColor = true;
            this.tutorialDocbutton.Click += new System.EventHandler(this.tutorialDocbutton_Click);
            // 
            // overviewDocButton
            // 
            resources.ApplyResources(this.overviewDocButton, "overviewDocButton");
            this.overviewDocButton.Name = "overviewDocButton";
            this.overviewDocButton.UseVisualStyleBackColor = true;
            this.overviewDocButton.Click += new System.EventHandler(this.overviewDocButton_Click);
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // performenceDocButton
            // 
            resources.ApplyResources(this.performenceDocButton, "performenceDocButton");
            this.performenceDocButton.Name = "performenceDocButton";
            this.performenceDocButton.UseVisualStyleBackColor = true;
            this.performenceDocButton.Click += new System.EventHandler(this.performenceDocButton_Click);
            // 
            // ControlsDialog
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(56)))), ((int)(((byte)(56)))), ((int)(((byte)(56)))));
            this.Controls.Add(this.performenceDocButton);
            this.Controls.Add(this.nodeRefDocButton);
            this.Controls.Add(this.insideDocButton);
            this.Controls.Add(this.tutorialDocbutton);
            this.Controls.Add(this.overviewDocButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.workspace3Button);
            this.Controls.Add(this.workspace4Button);
            this.Controls.Add(this.workspace2Button);
            this.Controls.Add(this.workspace1Button);
            this.Controls.Add(this.workspaceLabel);
            this.Controls.Add(this.checkBoxNext);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.webBrowser);
            this.ForeColor = System.Drawing.Color.LightGray;
            this.KeyPreview = true;
            this.Name = "ControlsDialog";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ControlsDialog_FormClosed);
            this.Load += new System.EventHandler(this.ControlsDialog_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ControlsDialog_KeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.WebBrowser webBrowser;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.CheckBox checkBoxNext;
        private System.Windows.Forms.Label workspaceLabel;
        private System.Windows.Forms.Button workspace1Button;
        private System.Windows.Forms.Button workspace2Button;
        private System.Windows.Forms.Button workspace4Button;
        private System.Windows.Forms.Button workspace3Button;
        private System.Windows.Forms.Button nodeRefDocButton;
        private System.Windows.Forms.Button insideDocButton;
        private System.Windows.Forms.Button tutorialDocbutton;
        private System.Windows.Forms.Button overviewDocButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button performenceDocButton;


    }
}
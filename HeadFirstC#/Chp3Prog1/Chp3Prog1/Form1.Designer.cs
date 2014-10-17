namespace Chp3Prog1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textToSay = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.numOfTimes = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.speakAction = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numOfTimes)).BeginInit();
            this.SuspendLayout();
            // 
            // textToSay
            // 
            this.textToSay.Location = new System.Drawing.Point(78, 13);
            this.textToSay.Name = "textToSay";
            this.textToSay.Size = new System.Drawing.Size(194, 20);
            this.textToSay.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Say this:";
            // 
            // numOfTimes
            // 
            this.numOfTimes.Location = new System.Drawing.Point(78, 39);
            this.numOfTimes.Name = "numOfTimes";
            this.numOfTimes.Size = new System.Drawing.Size(120, 20);
            this.numOfTimes.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 46);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "# of times: ";
            // 
            // speakAction
            // 
            this.speakAction.AutoSize = true;
            this.speakAction.Location = new System.Drawing.Point(78, 66);
            this.speakAction.Name = "speakAction";
            this.speakAction.Size = new System.Drawing.Size(81, 23);
            this.speakAction.TabIndex = 4;
            this.speakAction.Text = "Speak to Me!";
            this.speakAction.UseVisualStyleBackColor = true;
            this.speakAction.Click += new System.EventHandler(this.speakAction_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 104);
            this.Controls.Add(this.speakAction);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.numOfTimes);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textToSay);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.numOfTimes)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textToSay;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numOfTimes;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button speakAction;
    }
}


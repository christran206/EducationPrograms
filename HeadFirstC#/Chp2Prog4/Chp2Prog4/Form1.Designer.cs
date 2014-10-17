namespace Chp2Prog4
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
            this.changeTextButton = new System.Windows.Forms.Button();
            this.labelChangeBox = new System.Windows.Forms.CheckBox();
            this.changeLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // changeTextButton
            // 
            this.changeTextButton.AccessibleName = "";
            this.changeTextButton.AutoSize = true;
            this.changeTextButton.Location = new System.Drawing.Point(13, 13);
            this.changeTextButton.Name = "changeTextButton";
            this.changeTextButton.Size = new System.Drawing.Size(154, 23);
            this.changeTextButton.TabIndex = 0;
            this.changeTextButton.Text = "Change the label if checked";
            this.changeTextButton.UseVisualStyleBackColor = true;
            this.changeTextButton.Click += new System.EventHandler(this.changeTextButton_Click);
            // 
            // labelChangeBox
            // 
            this.labelChangeBox.AutoSize = true;
            this.labelChangeBox.Checked = true;
            this.labelChangeBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.labelChangeBox.Location = new System.Drawing.Point(341, 17);
            this.labelChangeBox.Name = "labelChangeBox";
            this.labelChangeBox.Size = new System.Drawing.Size(131, 17);
            this.labelChangeBox.TabIndex = 1;
            this.labelChangeBox.Text = "Enable label changing";
            this.labelChangeBox.UseVisualStyleBackColor = true;
            // 
            // changeLabel
            // 
            this.changeLabel.Location = new System.Drawing.Point(13, 62);
            this.changeLabel.Name = "changeLabel";
            this.changeLabel.Size = new System.Drawing.Size(459, 20);
            this.changeLabel.TabIndex = 2;
            this.changeLabel.Text = "Press the button to change my text";
            this.changeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 91);
            this.Controls.Add(this.changeLabel);
            this.Controls.Add(this.labelChangeBox);
            this.Controls.Add(this.changeTextButton);
            this.Name = "Form1";
            this.Text = "My Desktop App";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button changeTextButton;
        private System.Windows.Forms.CheckBox labelChangeBox;
        private System.Windows.Forms.Label changeLabel;
    }
}


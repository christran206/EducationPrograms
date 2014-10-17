using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Chp2Prog4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void changeTextButton_Click(object sender, EventArgs e)
        {
            if (labelChangeBox.Checked == true)
            {
                if (changeLabel.Text == "Right")
                {
                    changeLabel.Text = "Left";
                    changeLabel.TextAlign = ContentAlignment.MiddleLeft;
                }
                else
                {
                    changeLabel.Text = "Right";
                    changeLabel.TextAlign = ContentAlignment.MiddleRight;
                }
            }
            else
            {
                changeLabel.Text = "Text changing is disabled";
                changeLabel.TextAlign = ContentAlignment.MiddleCenter;
            }
        }


    }
}

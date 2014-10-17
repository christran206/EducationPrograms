using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Chp3Prog1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void speakAction_Click(object sender, EventArgs e)
        {
            int sLength = Talker.BlahBlahBlah(textToSay.Text, (int)numOfTimes.Value);
            MessageBox.Show("The message length is " + sLength);
        }
    }
}

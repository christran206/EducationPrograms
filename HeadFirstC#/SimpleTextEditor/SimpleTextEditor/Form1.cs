using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SimpleTextEditor
{
    public partial class Form1 : Form
    {

        private string name;
        private bool hasChanged;
        public Form1()
        {
            InitializeComponent();
            hasChanged = false;
            closeButton.Enabled = false;
            saveButton.Enabled = false;

            //Dialog Box Options
            openFileDialog1.Filter = "Text Files (*.txt)|*.txt";
            saveFileDialog1.Filter = "Text Files (*.txt)|*.txt";
        }

        private void openButton_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                name = openFileDialog1.FileName;
                textBox1.Clear();
                textBox1.Text = File.ReadAllText(name);
                closeButton.Enabled = false;
                saveButton.Enabled = false;
                saveFileDialog1.InitialDirectory = openFileDialog1.InitialDirectory;
                saveFileDialog1.FileName = openFileDialog1.FileName;
            }
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            hasChanged = true;
            closeButton.Enabled = true;
            saveButton.Enabled = true;
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            if (hasChanged)
            {
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    name = saveFileDialog1.FileName;
                    File.WriteAllText(name, textBox1.Text);
                    hasChanged = false;
                    saveButton.Enabled = false;
                }
            }
        }
    }
}

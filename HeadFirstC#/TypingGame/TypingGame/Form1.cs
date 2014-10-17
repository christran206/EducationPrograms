using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TypingGame
{
    public partial class Form1 : Form
    {
        Random random = new Random();
        Stats stats = new Stats();
        bool gameOver = false;
        public Form1()
        {
            InitializeComponent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //Add a random key to the ListBox of 7 items
            listBox1.Items.Add((Keys)random.Next(65,90));
            if (listBox1.Items.Count > 7)
            {
                listBox1.Items.Clear();
                gameOver = true;
                listBox1.Items.Add("Game Over");
                timer1.Stop();
                //Show message to start a new game
                MessageBox.Show("Press OK to start a new game");
                startGame();
            }
        }

        private void listBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (!gameOver) { 
                //If a user presses a key in the listbox, remove it and make the game faster
                //The higher the interval, the shorter the interval gets
                if (listBox1.Items.Contains(e.KeyCode))
                {
                    listBox1.Items.Remove(e.KeyCode);
                    listBox1.Refresh();
                    if (timer1.Interval > 400)
                    {
                        timer1.Interval -= 10;
                    }
                    if (timer1.Interval > 250)
                    {
                        timer1.Interval -= 7;
                    }
                    if (timer1.Interval > 100)
                    {
                        timer1.Interval -= 2;
                    }

                    //Progress bar will show the progression
                    difficultyProgressBar.Value = 800 - timer1.Interval;

                    stats.Update(true);
                }
                else
                {
                    //User pressed incorrect key
                    stats.Update(false);
                }

                updateStats();
            }
        }

        //Start the game for a fresh start
        private void startGame()
        {
            gameOver = false;
            listBox1.Items.Clear();
            timer1.Interval = 800;
            timer1.Start();
            stats = new Stats();
            updateStats();
        }

        //Update stats on call
        private void updateStats()
        {
            correctLabel.Text = "Correct: " + stats.Correct;
            missedLabel.Text = "Missed: " + stats.Missed;
            totalLabel.Text = "Total: " + stats.Total;
            accuracyLabel.Text = "Accuracy: " + stats.Accuracy + "%";
        }
    }
}

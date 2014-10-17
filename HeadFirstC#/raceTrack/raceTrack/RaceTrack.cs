using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace raceTrack
{
    public partial class RaceTrack : Form
    {
        Random random;
        Greyhound[] greyhounds;
        Guy[] guys;
        public RaceTrack()
        {
            InitializeComponent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            for(int i = 0; i < greyhounds.Length; i++) {
                if(greyhounds[i].Run()) {
                    timer1.Stop();
                    MessageBox.Show("Dog#" + (i + 1) + " has WON!");
                    foreach (Guy g in guys)
                    {
                        g.Collect(i + 1);
                    }
                    foreach (Greyhound g in greyhounds)
                    {
                        g.TakeStartingPosition();
                    }
                    betParlorGroup.Enabled = true;
                    break;
                }
            }
        }

        private void RaceTrack_Load(object sender, EventArgs e)
        {
            //Create a random object shared by all greyhounds
            random = new Random();

            //Update minimum bet label
            minBetLabel.Text = "Minimum Bet: $" + betMoney.Minimum;

            //On application load, create the greyhound objects
            greyhounds = new Greyhound[4];
            greyhounds[0] = new Greyhound()
            {
                MyPictureBox = greyhound1,
                StartingPosition = greyhound1.Left,
                RacetrackLength = raceTrackPhoto.Width,
                Location = 1,
                Randomizer = random
            };
            greyhounds[1] = new Greyhound()
            {
                MyPictureBox = greyhound2,
                StartingPosition = greyhound2.Left,
                RacetrackLength = raceTrackPhoto.Width,
                Location = 2,
                Randomizer = random
            };
            greyhounds[2] = new Greyhound()
            {
                MyPictureBox = greyhound3,
                StartingPosition = greyhound3.Left,
                RacetrackLength = raceTrackPhoto.Width,
                Location = 3,
                Randomizer = random
            };
            greyhounds[3] = new Greyhound()
            {
                MyPictureBox = greyhound4,
                StartingPosition = greyhound4.Left,
                RacetrackLength = raceTrackPhoto.Width,
                Location = 4,
                Randomizer = random
            };
            //On appilcation load, create the Guy Objects
            guys = new Guy[3];
            guys[0] = new Guy()
            {
                Name = "Joe",
                Cash = 10,
                MyRadioButton = joeRadioButton,
                MyLabel = joeBetLabel
            };
            guys[1] = new Guy()
            {
                Name = "Bob",
                Cash = 10,
                MyRadioButton = bobRadioButton,
                MyLabel = bobBetLabel
            };
            guys[2] = new Guy()
            {
                Name = "Al",
                Cash = 10,
                MyRadioButton = alRadioButton,
                MyLabel = alBetLabel
            };

            //Each guy needs to have a bet object added and labels updated
            foreach(Guy g in guys) {
                g.MyBet = new Bet()
                {
                    Amount = 0,
                    Dog = 0,
                    Bettor = g
                };
                g.UpdateLabels();
            }
        }

        private void betButton_Click(object sender, EventArgs e)
        {
            if (dogBox.Text == "Select Dog")
            {
                MessageBox.Show("Please select a dog to bet on");
            }
            if (joeRadioButton.Checked)
            {
                if (guys[0].PlaceBet((int)betMoney.Value, dogBox.SelectedIndex + 1))
                {
                    guys[0].UpdateLabels();
                }
                else
                {
                    MessageBox.Show("Not enough money to place bet!");
                }
                
            }
            if (bobRadioButton.Checked)
            {
                if (guys[1].PlaceBet((int)betMoney.Value, dogBox.SelectedIndex + 1))
                {
                    guys[1].UpdateLabels();
                }
                else
                {
                    MessageBox.Show("Not enough money to place bet!");
                }
            }
            if (alRadioButton.Checked)
            {
                if (guys[2].PlaceBet((int)betMoney.Value, dogBox.SelectedIndex + 1))
                {
                    guys[2].UpdateLabels();
                }
                else
                {
                    MessageBox.Show("Not enough money to place bet!");
                }
            }
        }

        private void startRaceButton_Click(object sender, EventArgs e)
        {
            betParlorGroup.Enabled = false;
            timer1.Start();
        }
    }
}

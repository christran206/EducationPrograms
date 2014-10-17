using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Chp3Prog1
{
    class Talker
    {
        public static int BlahBlahBlah(string thingTosay, int numberOfTimes)
        {
            string finalString = "";
            for (int i = 0; i < numberOfTimes; i++)
            {
                finalString += thingTosay + "\n";
            }

            MessageBox.Show(finalString);
            return finalString.Length;
        }
    }
}

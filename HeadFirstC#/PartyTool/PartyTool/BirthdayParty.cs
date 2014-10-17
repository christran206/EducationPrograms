using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PartyTool
{
    class BirthdayParty : Party
    {
        //Properties and Variables
        public string CakeWriting { get; set; }

        public int Actuallength
        {
            get
            {
                if (CakeWriting.Length > MaxWritingLength())
                {
                    return MaxWritingLength();
                }
                else
                {
                    return CakeWriting.Length;
                }
            }
        }

        public bool CakeWritingTooLong
        {
            get
            {
                return CakeWriting.Length > MaxWritingLength();
            }
        }

        public override decimal Cost
        {
            get
            {
                decimal totalCost = base.Cost;
                decimal cakeCost;
                if (CakeSize() == 8)
                {
                    cakeCost = 40M + Actuallength * 0.25M;
                }
                else
                {
                    cakeCost = 75M + Actuallength * 0.25M;
                }
                return totalCost + cakeCost;
            }
        }

        //Constructors
        public BirthdayParty(int numberOfPeople, bool fancyDecoration, string cakeWriting)
        {
            NumberOfPeople = numberOfPeople;
            FancyDecorations = fancyDecoration;
            CakeWriting = cakeWriting;
        }

        //Private Methods
        private int CakeSize()
        {
            if (NumberOfPeople <= 4)
            {
                return 8;
            }
            else
            {
                return 16;
            }
        }

        private int MaxWritingLength()
        {
            if (CakeSize() == 8)
            {
                return 16;
            }
            else
            {
                return 40;
            }
        }


        //Public Methods
    }
}

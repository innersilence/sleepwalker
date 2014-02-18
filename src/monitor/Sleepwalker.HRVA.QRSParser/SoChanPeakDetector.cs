using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sleepwalker.HRVA.Realtime
{
    public class SoChanPeakDetector : IPeakDetector
    {
        readonly double Threashold = 8;
        readonly double Filter = 16;
        readonly int SampleRate = 250;

        public SoChanPeakDetector(double threashold, double filter, int sampleRate)
        {
            Threashold = threashold;
            Filter = filter;
            SampleRate = sampleRate;
        }

        public DataPoint[] GetPeaks(DataPoint[] points)
        {
            // initial maxi should be the max slope of the first 250 points.
            double initialMaxi = -2 * points[0].Value - points[1].Value + points[3].Value + 2 * points[4].Value;

            for (int i = 2; i < SampleRate; i++)
            {
                double slope = -2 * points[i - 2].Value - points[i - 1].Value + points[i + 1].Value + 2 * points[i + 2].Value;
                if (slope > initialMaxi)
                    initialMaxi = slope;
            }

            // Since we don't know how many R peaks we'll have, we'll use an ArrayList
            List<int> rTime = new List<int>();

            // set initial maxi
            double maxi = initialMaxi;
            bool firstSatisfy = false;
            bool secondSatisfy = false;
            int onset_point = 0;
            int R_point = 0;

            // I want a way to plot all the r dots that are found...
            int[] rExist = new int[points.Length];

            // First two voltages should be ignored because we need rom length
            for (int i = 2; i < points.Length - 2; i++)
            {

                // Last two voltages should be ignored too
                if (!firstSatisfy || !secondSatisfy)
                {
                    // Get Slope:
                    double slope = -2 * points[i - 2].Value - points[i - 1].Value + points[i + 1].Value + 2 * points[i + 2].Value;

                    // Get slope threshold
                    double slope_threshold = (Threashold / 16) * maxi;

                    // We need two consecutive datas that satisfy slope > slope_threshold
                    if (slope > slope_threshold)
                    {
                        if (!firstSatisfy)
                        {
                            firstSatisfy = true;
                            onset_point = i;
                        }
                        else
                        {
                            if (!secondSatisfy)
                            {
                                secondSatisfy = true;
                            }
                        }
                    }
                }
                // We found the ONSET already, now we find the R point
                else
                {

                    if (points[i].Value < points[i - 1].Value)
                    {
                        rTime.Add(i - 1);
                        R_point = i - 1;

                        // Since we have the R, we should reset
                        firstSatisfy = false;
                        secondSatisfy = false;

                        // and update maxi
                        double first_maxi = points[R_point].Value - points[onset_point].Value;
                        maxi = ((first_maxi - maxi) / Filter) + maxi;
                    }
                }
            }

            DataPoint[] results = new DataPoint[rTime.Count];

            // Now we convert the ArrayList to an array and return it
            for (int i = 0; i < rTime.Count; i++)
            {
                results[i].Value = rTime[i];
            }

            return results;
        }
    }
}

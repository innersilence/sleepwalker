using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


// http://www.codeforge.com/article/218374
// http://blog.kenliao.info/2012/03/c-so-and-chan-method-r-peak-detection.html



namespace Sleepwalker.HRVA.Realtime
{
    class SoAndChan
    {
        // We need some initial data...
        const double THRESHOLD_PARAM = 8;
        const double FILTER_PARAMETER = 16;
        const int SAMPLE_RATE = 250;

        public static double[] GetPeaks(double[] voltages)
        {
            // initial maxi should be the max slope of the first 250 points.
            double initial_maxi = -2 * voltages[0] - voltages[1] + voltages[3] + 2 * voltages[4];
            for (int i = 2; i < SAMPLE_RATE; i++)
            {
                double slope = -2 * voltages[i - 2] - voltages[i - 1] + voltages[i + 1] + 2 * voltages[i + 2];
                if (slope > initial_maxi)
                    initial_maxi = slope;
            }

            // Since we don't know how many R peaks we'll have, we'll use an ArrayList
            List<int> rTime = new List<int>();

            // set initial maxi
            double maxi = initial_maxi;
            bool first_satisfy = false;
            bool second_satisfy = false;
            int onset_point = 0;
            int R_point = 0;

            //bool rFound = false;

            // I want a way to plot all the r dots that are found...
            int[] rExist = new int[voltages.Length];
            // First two voltages should be ignored because we need rom length
            for (int i = 2; i < voltages.Length - 2; i++)
            {

                // Last two voltages should be ignored too
                if (!first_satisfy || !second_satisfy)
                {
                    // Get Slope:
                    double slope = -2 * voltages[i - 2] - voltages[i - 1] + voltages[i + 1] + 2 * voltages[i + 2];

                    // Get slope threshold
                    double slope_threshold = (THRESHOLD_PARAM / 16) * maxi;

                    // We need two consecutive datas that satisfy slope > slope_threshold
                    if (slope > slope_threshold)
                    {
                        if (!first_satisfy)
                        {
                            first_satisfy = true;
                            onset_point = i;
                        }
                        else
                        {
                            if (!second_satisfy)
                            {
                                second_satisfy = true;
                            }
                        }
                    }
                }
                // We found the ONSET already, now we find the R point
                else
                {

                    if (voltages[i] < voltages[i - 1])
                    {
                        rTime.Add(i - 1);
                        R_point = i - 1;

                        // Since we have the R, we should reset
                        first_satisfy = false;
                        second_satisfy = false;

                        // and update maxi
                        double first_maxi = voltages[R_point] - voltages[onset_point];
                        maxi = ((first_maxi - maxi) / FILTER_PARAMETER) + maxi;
                    }
                }
            }

            double[] results = new double[rTime.Count];

            // Now we convert the ArrayList to an array and return it
            for (int i = 0; i < rTime.Count; i++)
            {
                results[i] = rTime[i];
            }

            return results;
        }
    }
}

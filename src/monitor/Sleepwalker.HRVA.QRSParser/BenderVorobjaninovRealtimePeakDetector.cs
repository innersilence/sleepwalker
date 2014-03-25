using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace Sleepwalker.HRVA.Realtime
{
    public class BenderVorobjaninovRealtimePeakDetector : IPeakDetector
    {
        public static class Constants
        {
            public const double DefaultThreshold = 4000;
            public const double DefaultKappa = 5;
        }

        readonly double Threshold = Constants.DefaultThreshold;
        readonly double Kappa = Constants.DefaultKappa;

        private double travel = 0;
        private DataPoint startDataPoint = new DataPoint(0);
        private DataPoint lastDataPoint = new DataPoint(0);

        public BenderVorobjaninovRealtimePeakDetector()
        {
            Threshold = Constants.DefaultThreshold;
            Kappa = Constants.DefaultKappa;

            startDataPoint.Value = 0;
            lastDataPoint.Value = 0;
        }

        public BenderVorobjaninovRealtimePeakDetector(int threashold, int kappa)
        {
            Threshold = threashold;
            Kappa = kappa;

            startDataPoint.Value = 0;
            lastDataPoint.Value = 0;
        }

        public DataPoint GetPeak(DataPoint dataPoint)
        {
            if (startDataPoint.Value == 0) { startDataPoint = dataPoint; lastDataPoint = dataPoint; return new DataPoint(PeakDetector.Constants.NotAPeak); } // First run. 

            travel += Math.Abs(dataPoint.Value - lastDataPoint.Value);
            double rise = Math.Abs(dataPoint.Value - startDataPoint.Value) + Kappa;

            if ((travel / rise >= 1)) // Peak found.     
            {
                DataPoint peak = lastDataPoint;

                startDataPoint = dataPoint;
                lastDataPoint = dataPoint;
                travel = 0;

                if (rise > Threshold)
                    return peak;
                else
                    return new DataPoint(PeakDetector.Constants.NotAPeak);
            }

            lastDataPoint = dataPoint;
            return new DataPoint(PeakDetector.Constants.NotAPeak);
        }

        //public void TestPeakDetector()
        //{
        //    List<string> lines = System.IO.File.ReadAllLines(@".\data_papa_400.csv").ToList();
        //    List<DataPoint> points = new List<DataPoint>();

        //    lines.ForEach(l => 
        //    { 
        //        points.Add(new DataPoint(int.Parse(l.Trim('\n')))); 
        //    });


        //    var peakDetector = new BenderVorobjaninovRealtimePeakDetector(4000, 5) as IPeakDetector;

        //    List<int> peaksRealtime = new List<int>();
        //    points.ForEach(p =>
        //    {
        //        DataPoint peak = peakDetector.GetPeak(p);
        //        if (PeakDetector.Constants.NotAPeak != peak.Value)
        //        {
        //            peaksRealtime.Add(peak.Value);
        //        }
        //    });
        //}
    }
}

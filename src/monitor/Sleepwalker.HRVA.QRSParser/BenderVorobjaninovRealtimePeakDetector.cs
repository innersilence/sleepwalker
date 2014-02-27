using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//namespace ConsoleApp
//{
//    class Program
//    {
//        const double Threshold = 8;
//        const double FilterValue = 16;
//        const int SampleRate = 50;

//        static void Main(string[] args)
//        {
//            List<string> lines = System.IO.File.ReadAllLines(@".\data_papa.csv").ToList();
//            List<int> points = new List<int>();
//            List<int> peakIndices = new List<int>();

//            for (int i = 0; i < lines.Count; ++i)
//            {
//                string[] tokens = lines[i].Split(new char[] { ' ', '\n' });
//                points.Add(int.Parse(tokens[0]));
//                if (tokens.Length > 1)
//                    peakIndices.Add(i);
//            }

//            List<Tuple<int, int>> peaksRealtime = new List<Tuple<int, int>>();
//            var peakDetector = new BenderVorobjaninovRealtimePeakDetector(4000, 5);

//            for (int i = 0; i < points.Count; ++i)
//            {
//                int peak = peakDetector.GetPeak(points[i]);
//                if (Constants.NotAPeak != peak)
//                {
//                    peaksRealtime.Add(new Tuple<int, int>(peak, i - 1));
//                }
//            }
//        }
//    }
//}


namespace Sleepwalker.HRVA.Realtime
{
    public class BenderVorobjaninovRealtimePeakDetector : IPeakDetector
    {
        public static class Constants
        {
            public const int DefaultThreshold = 4000;
            public const int DefaultKappa = 5;
        }

        readonly int Threshold = Constants.DefaultThreshold;
        readonly int Kappa = Constants.DefaultKappa;

        private int travel = 0;
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
            int rise = Math.Abs(dataPoint.Value - startDataPoint.Value) + Kappa;

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
    }
}

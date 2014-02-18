using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sleepwalker.HRVA.Realtime
{
    public delegate void DataPointReceivedEventHandler(object sender, DataPoint p);

    public interface IPeakDetector
    {
        DataPoint[] GetPeaks(DataPoint[] points);
    }

    public class RParser
    {
        private Queue<DataPoint> dataPoints;
        private IPeakDetector peakDetector;

        public DataPointReceivedEventHandler EmitDataPoint;

        public RParser()
        {
            dataPoints = new Queue<DataPoint>();
            peakDetector = new SoChanPeakDetector(8, 16, 50) as IPeakDetector;
        }

        public void DataPointReceived(object sender, DataPoint p)
        {
            dataPoints.Enqueue(p);

            List<DataPoint> peaks = peakDetector.GetPeaks(dataPoints.ToArray()).ToList();
            if (peaks.Count > 0)
            {
                peaks.ForEach(pk => EmitDataPoint(this, pk));
                dataPoints.Clear(); // Discard already processed data.
            }
        }
    }
}

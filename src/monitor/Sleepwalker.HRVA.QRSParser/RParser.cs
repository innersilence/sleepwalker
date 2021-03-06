﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Sleepwalker.HRVA.Realtime
{
    public delegate void DataPointReceivedEventHandler(object sender, DataPoint p);

    public class RParser
    {
        //private Queue<DataPoint> dataPoints;
        private IPeakDetector peakDetector;

        public DataPointReceivedEventHandler EmitDataPoint;

        public RParser()
        {
            //dataPoints = new Queue<DataPoint>();
            peakDetector = new BenderVorobjaninovRealtimePeakDetector() as IPeakDetector;
        }

        public void DataPointReceived(object sender, DataPoint p)
        {
            DataPoint peak = peakDetector.GetPeak(p);
            if (peak.Value != PeakDetector.Constants.NotAPeak)
            {
                //dataPoints.Enqueue(peak);
                EmitDataPoint(this, peak);
            }
        }
    }
}

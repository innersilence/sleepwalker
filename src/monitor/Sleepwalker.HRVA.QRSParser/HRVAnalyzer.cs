using System;
using System.Collections.Generic;
using System.Linq;


namespace Sleepwalker.HRVA.Realtime
{
    public enum SleepState
    {
        NonREM,
        REM
    }

    public delegate void HeartRateEventHandler(object sender, double rate);
    public delegate void SleepStateEventHandler(object sender, SleepState state);

    public class HRVAnalyzer
    {
        private List<DataPoint> heartratePoints = new List<DataPoint>();

        public DataPoint LastPoint { get; set; }
        private double Average { get; set; }
        private double Deviation { get; set; }

        public HeartRateEventHandler UpdateHeartRate;
        public SleepStateEventHandler UpdateSleepPhase;

        double HeartRate(DataPoint p)
        {
            TimeSpan between = p.Timestamp - LastPoint.Timestamp;
            double minutes = between.TotalSeconds / 60;
            return 1 / minutes; // Beats per minute.
        }

        public void DataPointReceived(object sender, DataPoint point)
        {
            double hr = HeartRate(point);
            heartratePoints.Add(new DataPoint(hr, point.Timestamp));
            LastPoint = point;

            if (UpdateHeartRate != null)
                UpdateHeartRate(this, hr);

            TimeSpan measurementInterval = new TimeSpan();
            if (RemDetected(heartratePoints.Where(p => DateTime.Now - p.Timestamp < measurementInterval).ToList(), measurementInterval))
            {
                if (UpdateSleepPhase != null)
                    UpdateSleepPhase(this, SleepState.REM);

                const int keepItems = 1000; // Keep hratePoints size to approx 1000 to 2000 points (~10 - 20) minutes
                if (heartratePoints.Count > keepItems * 2)
                    heartratePoints = heartratePoints.Skip(heartratePoints.Count - keepItems).ToList();
            } 
            else
            {
                UpdateSleepPhase(this, SleepState.NonREM);
            }
        }

        private bool RemDetected(List<DataPoint> points, TimeSpan span)
        {
            // If high -> erratic pulse, most likely REM.
            double deviation = points.Max().Value - points.Min().Value;

            // Increase in HR most likely when entering REM.
            double average = points.Aggregate((a, b) => { return new DataPoint(a.Value + b.Value); }).Value / points.Count;

            bool erraticPulse = deviation > Deviation;
            bool increasedHeartrate = average > Average;

            Average = average;
            Deviation = deviation;

            if (erraticPulse && increasedHeartrate)
                return true; // Most likely in REM.

            return false;
        }
    }
}

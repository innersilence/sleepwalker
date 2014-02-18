using System;
using System.Collections.Generic;


namespace Sleepwalker.HRVA.Realtime
{
    public class HRVAnalyzer
    {
        public void DataPointReceived(object sender, DataPoint p)
        {
            Console.WriteLine("R: " + p.ToString());
        }
    }
}

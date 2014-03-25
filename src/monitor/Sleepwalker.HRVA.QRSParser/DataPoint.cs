using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sleepwalker.HRVA.Realtime
{
    public class DataPoint
    {
        public double Value { get; set; }
        public DateTime Timestamp { get; set; }

        public DataPoint(double val)
        {
            Value = val;
            Timestamp = DateTime.Now.ToUniversalTime();
        }

        public DataPoint(double val, DateTime timestamp)
        {
            Value = val;
            Timestamp = timestamp;
        }

        public override string ToString()
        {
            return string.Format("{0}@{1}", Value, Timestamp);
        }
    }
}

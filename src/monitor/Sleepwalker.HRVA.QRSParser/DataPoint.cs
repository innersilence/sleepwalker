using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sleepwalker.HRVA.Realtime
{
    public class DataPoint
    {
        public int Value { get; set; }
        public DateTime Timestamp { get; set; }

        public override string ToString()
        {
            return string.Format("{0}@{1}", Value, Timestamp);
        }
    }
}

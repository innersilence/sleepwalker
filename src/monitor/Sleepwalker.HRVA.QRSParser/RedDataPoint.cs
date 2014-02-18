using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sleepwalker.HRVA.Realtime
{
    public class RedDataPoint : DataPoint
    {
        public RedDataPoint(int val)
        {
            Value = val;
            Timestamp = DateTime.Now.ToUniversalTime();
        }
    }
}

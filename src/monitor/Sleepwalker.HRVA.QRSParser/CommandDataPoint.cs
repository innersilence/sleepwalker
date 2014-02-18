using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sleepwalker.HRVA.Realtime
{
    public class CommandDataPoint : DataPoint
    {
        public CommandDataPoint(int val)
        {
            Value = val;
            Timestamp = DateTime.Now.ToUniversalTime();
        }
    }
}

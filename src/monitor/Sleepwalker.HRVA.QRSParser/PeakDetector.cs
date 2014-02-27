using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sleepwalker.HRVA.Realtime
{
    public interface IPeakDetector
    {
        DataPoint GetPeak(DataPoint p);
    }

    public class PeakDetector
    {
        public static class Constants
        {
            public const int NotAPeak = -1;
        }
    }
}

using System;
using System.Collections.Concurrent;
using System.Linq;


namespace Sleepwalker.HRVA.Realtime
{
    public class FixedSizeConcurrentQueue<T> 
    {
        public ConcurrentQueue<T> Queue = new ConcurrentQueue<T>();

        public int Limit { get; private set; }

        public FixedSizeConcurrentQueue(int maxSize)
        {
            Limit = maxSize;
        }

        public void Enqueue(T item)
        {
            Queue.Enqueue(item);
            lock (this)
            {
                T overflow;
                while (Queue.Count > Limit && Queue.TryDequeue(out overflow)) ;
            }
        }

        public T Dequeue()
        {
            T result;
            if (Queue.TryDequeue(out result))
                return result;

            return default(T);
        }
    }
}

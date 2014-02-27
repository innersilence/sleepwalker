using System;
using System.IO.Ports;

using Sleepwalker.HRVA.Realtime;

namespace Sleepwalker.Collector
{
    public class SerialCollector
    {
        public static class Constants
        {
            public const int DefaultBaudRate = 115200;
            public const int DefaultDataPointQueueSize = 1000;
        }

        private SerialPort serialPort;

        public DataPointReceivedEventHandler EmitDataPoint;
        public FixedSizeConcurrentQueue<IRDataPoint> irDataPointQueue;
        //private FixedSizeConcurrentQueue<IRDataPoint> redDataPointQueue;
        public bool Stopped { get; set; }

        public SerialCollector(string port)
        {
            serialPort = new SerialPort(port, Constants.DefaultBaudRate, Parity.None, 8, StopBits.One);
            serialPort.Handshake = Handshake.None;
            serialPort.DataReceived += new SerialDataReceivedEventHandler(OnIncomingData);
            Stopped = true;

            irDataPointQueue = new FixedSizeConcurrentQueue<IRDataPoint>(Constants.DefaultDataPointQueueSize);
        }

        public void Start()
        {
            try
            {
                serialPort.Open();
                Stopped = false;
            }
            catch (Exception) { }
        }

        public void Stop()
        {
            try
            {
                serialPort.Close();
                Stopped = true;
            }
            catch (Exception) { }
        }

        private void OnIncomingData(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data;
            try
            {
                data = sp.ReadLine();
                DataPoint p = Parse(data);
                if (p != null)
                {
                    if (p.GetType() == typeof(IRDataPoint))
                    {
                        irDataPointQueue.Enqueue(p as IRDataPoint);
                        EmitDataPoint(this, p);
                    }
                }
            
            }
            catch (Exception) { }
        }

        private DataPoint Parse(string data)
        {
            string[] tokens = data.Split(new char[] { ' ', '\n' });
            if (tokens.Length < 2)
                return null;

            if (string.IsNullOrEmpty(tokens[0]) || string.IsNullOrEmpty(tokens[1]))
                return null;

            int channel = int.Parse(tokens[0]);
            int value = int.Parse(tokens[1]);

            switch (channel)
            {
                case 0: // System/Command channel.
                    return new CommandDataPoint(value);
                case 1: // IR channel.
                    return new IRDataPoint(value);
                case 2: // Red channel;
                    return new RedDataPoint(value);
            }

            return null;
        }
    }
}

using System;
using System.IO.Ports;

using Sleepwalker.HRVA.Realtime;

namespace Sleepwalker.Collector
{
    public class SerialCollector
    {
        private SerialPort serialPort;

        public DataPointReceivedEventHandler EmitDataPoint;
        public bool Stopped { get; set; }

        public SerialCollector(string port)
        {
            serialPort = new SerialPort(port, 115200, Parity.None, 8, StopBits.One);
            serialPort.Handshake = Handshake.None;
            serialPort.DataReceived += new SerialDataReceivedEventHandler(OnIncomingData);
            Stopped = true;
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
            string data = sp.ReadLine();

            DataPoint dp = Parse(data);
            if (dp != null)
            {
                if (dp.GetType() == typeof(IRDataPoint))
                    EmitDataPoint(this, dp);
            }
        }

        private DataPoint Parse(string data)
        {
            string[] tokens = data.Split(new char[] { ' ', '\n' });
            if (tokens.Length < 2)
                return null;

            int channel = int.Parse(tokens[0]);
            int value = int.Parse(tokens[1]);
            //double timestamp = double.Parse(tokens[2]);

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

/*
The MIT License (MIT)

Copyright (c) 2013 Dmitry Mukhin <zxorro@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

using System;
using System.Windows;
using System.Collections.Generic;
using System.Linq;
using System.IO.Ports;
using System.Threading;
using System.ComponentModel;
using Microsoft.Research.DynamicDataDisplay;
using Microsoft.Research.DynamicDataDisplay.DataSources;
using Microsoft.Research.DynamicDataDisplay.PointMarkers;



namespace DataMonitor
{
    public class MonitorData 
    {
        public double Value { get; set; }
        public TimeSpan Elapsed { get; set; }

        public MonitorData(double value, TimeSpan elapsed)
        {
            Value = value;
            Elapsed = elapsed;
        }
    }

    public class MonitorDataModel //: INotifyPropertyChanged
    {
        private CompositeDataSource timeData;
        private SerialPort comPort = null;
        private DateTime monitorStarted;
        private Thread serialPortSimulatorThread = null;
        //public event PropertyChangedEventHandler PropertyChanged;

        public MonitorDataModel()
        {
            Values = new List<MonitorData>();
            Baud = 38400;
            Port = "COM4";
        }

        #region Properties
        public string Port { get; set; }

        public int Baud { get; set; }

        public List<MonitorData> Values { get; private set; }

        public CompositeDataSource MonitorData
        {
            get
            {
                if (timeData == null)
                {
                    var xData = new EnumerableDataSource<double>(Values.Select(v => v.Elapsed.TotalMilliseconds));
                    xData.SetXMapping(x => x);
                    var yData = new EnumerableDataSource<double>(Values.Select(v => v.Value));
                    yData.SetYMapping(y => y);

                    timeData = xData.Join(yData);
                }

                return timeData;
            }
        }
        #endregion

        //#region INotifyPropertyChanged
        //protected virtual void OnPropertyChanged(string propertyName)
        //{
        //    if (PropertyChanged != null)
        //    {
        //        PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        //    }
        //}
        //#endregion

        #region Serial
        public void Start()
        {
            comPort = new SerialPort(Port, Baud, Parity.None, 8, StopBits.One);
            comPort.DataReceived += new SerialDataReceivedEventHandler(SerialPortReceiveHandler);
            try
            {
                comPort.Open();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }

            monitorStarted = DateTime.Now;
        }

        public void Stop()
        {
            if (comPort != null)
                comPort.Close();
        }
        public void StartSimulation()
        {
            monitorStarted = DateTime.Now;
            serialPortSimulatorThread = new Thread(SerialPortSimulator);
            serialPortSimulatorThread.Start();
        }

        private void SerialPortReceiveHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort port = (SerialPort)sender;
            string indata = port.ReadLine();

            string[] readings = indata.Split(' ');
            int ir = int.Parse(readings[0]);
            int red = int.Parse(readings[1]);

            Values.Add(new MonitorData((double)red, DateTime.Now - monitorStarted));
        }

        private void SerialPortSimulator()
        {
            const double amplitude = 1000.0;
            while (true)
            {
                double sample = amplitude * Math.Sin(1000);
                Values.Add(new MonitorData(sample, DateTime.Now - monitorStarted));
                Thread.Sleep(100);
                //OnPropertyChanged("MonitorData");
            }
        }
        #endregion
    }
}

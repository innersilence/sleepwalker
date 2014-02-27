using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

using Sleepwalker.Collector;
using Sleepwalker.HRVA.Realtime;


namespace Sleepwalker
{
    public partial class MainForm : Form
    {
        HRVAnalyzer analyser = null;
        RParser parser = null;
        SerialCollector collector = null;

        public MainForm()
        {
            InitializeComponent();
            InitializeComPortList();
            InitializeGraphlib(new EventHandler(SetFrameData));           
        }

        private void InitializeComPortList()
        {
            List<string> ports = SerialPort.GetPortNames().ToList();
            ports.ForEach(p => serialPortsComboBox.Items.Add(p));
            serialPortsComboBox.SelectedIndex = serialPortsComboBox.Items.Count - 1; // Last.
        }

        private void InitializeHrva()
        {
            analyser = new HRVAnalyzer();
            parser = new RParser();
            parser.EmitDataPoint += analyser.DataPointReceived;

            string port = serialPortsComboBox.Items[serialPortsComboBox.SelectedIndex].ToString();
            collector = new SerialCollector(port);       
            collector.EmitDataPoint += parser.DataPointReceived;

            heartRateLabel.Text = "00";  
        }

        private void SetFrameData(object sender, EventArgs e)
        {
            IRDataPoint[] collectedPoints = collector.irDataPointQueue.Queue.Take(display.DataSources[0].Length).ToArray();
            try
            {
                GraphLib.cPoint[] displayPoints = display.DataSources[0].Samples;
                for (int i = 0; i < collectedPoints.Length; ++ i)
                {
                    displayPoints[i].x = i;
                    displayPoints[i].y = (float)collectedPoints[i].Value;
                }
                
                this.Invoke(new MethodInvoker(RefreshGraph));
            }
            catch (ObjectDisposedException) { } // we get this on closing of form            
            catch (Exception) { }
        }

        private void collectorStartStopButton_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            if (collector == null || collector.Stopped)
            {
                InitializeHrva();
             
                collector.Start();
                display.Start();
                StartGraph();
                
                b.Text = "Stop";
            }
            else
            {
                collector.Stop();
                StopGraph();
                display.Stop();

                b.Text = "Start";
            }
        }

        //private void TestPeakDetector()
        //{
        //    List<string> lines = System.IO.File.ReadAllLines(@".\data_papa_400.csv").ToList();
        //    List<DataPoint> points = new List<DataPoint>();

        //    lines.ForEach(l => 
        //    { 
        //        points.Add(new DataPoint(int.Parse(l.Trim('\n')))); 
        //    });


        //    var peakDetector = new BenderVorobjaninovRealtimePeakDetector(4000, 5) as IPeakDetector;

        //    List<int> peaksRealtime = new List<int>();
        //    points.ForEach(p =>
        //    {
        //        DataPoint peak = peakDetector.GetPeak(p);
        //        if (PeakDetector.Constants.NotAPeak != peak.Value)
        //        {
        //            peaksRealtime.Add(peak.Value);
        //        }
        //    });
        //}
    }
}

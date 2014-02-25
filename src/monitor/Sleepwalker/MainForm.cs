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
            InitializeGraphlib();
        }

        private void InitializeComPortList()
        {
            List<string> ports = SerialPort.GetPortNames().ToList();
            ports.ForEach(p => serialPortsComboBox.Items.Add(p));
            serialPortsComboBox.SelectedIndex = 0;
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

        private void collectorStartStopButton_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            if (collector == null || collector.Stopped)
            {
                InitializeHrva();
              
                //TestPeakDetector();

                collector.Start();
                b.Text = "Stop";
            }
            else
            {
                collector.Stop();
                b.Text = "Start";
            }
        }

        private void TestPeakDetector()
        {
            List<string> lines = System.IO.File.ReadAllLines(@".\data_papa_400.csv").ToList();
            List<DataPoint> points = new List<DataPoint>();
            List<int> peakIndices = new List<int>();

            for (int i = 0; i < lines.Count; ++i)
            {
                string[] tokens = lines[i].Split(new char[] { ' ', '\n' });
                points.Add(new DataPoint(int.Parse(tokens[0])));
                if (tokens.Length > 1)
                    peakIndices.Add(i);
            }

            List<Tuple<int, int>> peaksRealtime = new List<Tuple<int, int>>();
            var peakDetector = new BenderVorobjaninovRealtimePeakDetector(4000, 5);

            for (int i = 0; i < points.Count; ++i)
            {
                DataPoint peak = peakDetector.GetPeak(points[i]);
                if (Constants.PeakDetector.NotAPeak != peak.Value)
                {
                    peaksRealtime.Add(new Tuple<int, int>(peak.Value, i - 1));
                }
            }
        }
    }
}

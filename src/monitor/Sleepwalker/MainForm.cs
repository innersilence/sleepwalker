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
                InitializeGraphlib();

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
            SoChanPeakDetector pd = new SoChanPeakDetector(8, 16, 50);

            DataPoint[] gozinta = LoadDataPointsFromFile(".\\data_papa.csv");
            DataPoint[] gozoutta = pd.GetPeaks(gozinta);
        }

        private DataPoint[] LoadDataPointsFromFile(string filename)
        {
            if (!File.Exists(filename))
                return null;

            List<DataPoint> points = new List<DataPoint>();
            using (StreamReader r = new StreamReader(filename, Encoding.ASCII))
            {
                string data = r.ReadLine();
                string[] tokens = data.Split(new char[] { ' ', '\n' });
                if (tokens.Length >= 2)
                {
                    int channel = int.Parse(tokens[0]);
                    int value = int.Parse(tokens[1]);
                    points.Add(new IRDataPoint(value));
                }
            }

            return points.ToArray();
        }
    }

    /*
     [todo]
     
     * Two graps (all data + R only)
     * Pulse, RR interval
     
     */
}

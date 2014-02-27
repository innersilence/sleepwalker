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
            InitializeHrva();
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
        }

        private void SetFrameData(object sender, EventArgs e)
        {
            IRDataPoint[] collectedPoints = collector.irDataPointQueue.Queue.Take(display.DataSources[0].Length).ToArray();
            try
            {
                GraphLib.cPoint[] displayPoints = display.DataSources[0].Samples;
                for (int i = 0; i < collectedPoints.Length; ++i)
                {
                    displayPoints[i].x = i;
                    displayPoints[i].y = (float)collectedPoints[i].Value;
                }

                //this.Invoke(new MethodInvoker(RefreshGraph));
            }
            catch (ObjectDisposedException) { } // we get this on closing of form            
            catch (Exception) { }
        }

        private void collectorStartStopButton_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            b.Enabled = false;
            if (collector == null || collector.Stopped)
            {
                if (collector.Start())
                {
                    display.Start();
                    StartGraph();

                    b.Text = "Stop";
                }
            }
            else
            {
                if (collector.Stop())
                {
                    StopGraph();
                    display.Stop();

                    b.Text = "Start";
                }
            }
            b.Enabled = true;
        }
    }
}

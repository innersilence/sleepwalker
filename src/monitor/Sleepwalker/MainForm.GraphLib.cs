using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

using GraphLib;


namespace Sleepwalker
{
    public partial class MainForm
    {
        private PrecisionTimer.Timer mTimer = null;
        
        private void InitializeGraphlib(EventHandler onTimerTick)
        {
            ApplyDisplaySchema("green");
            SetupGraph(Color.FromArgb(0, 255, 0), 0);
            
            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
            //display.Refresh();

            mTimer = new PrecisionTimer.Timer();
            mTimer.Period = 50;         // Milliseconds between frames
            mTimer.Tick += onTimerTick;
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            display.Dispose();
            base.OnClosing(e);
        } 

        protected override void OnClosed(EventArgs e)
        {
            mTimer.Stop();
            mTimer.Dispose();
            base.OnClosed(e);
        }

        private void StartGraph()
        {
            mTimer.Start();
        }

        private void StopGraph()
        {
            mTimer.Stop();
        }

        private void RefreshGraph()
        {
            display.Refresh();
        }

        private void ApplyDisplaySchema(string schema)
        {
            switch (schema)
            {
                case "green":
                    display.BackgroundColorTop = Color.FromArgb(0, 64, 0);
                    display.BackgroundColorBot = Color.FromArgb(0, 64, 0);
                    display.SolidGridColor = Color.FromArgb(0, 128, 0);
                    display.DashedGridColor = Color.FromArgb(0, 128, 0);
                    break;
                case "white":
                    display.BackgroundColorTop = Color.White;
                    display.BackgroundColorBot = Color.White;
                    display.SolidGridColor = Color.LightGray;
                    display.DashedGridColor = Color.LightGray;
                    break;
                case "gray":
                    display.BackgroundColorTop = Color.White;
                    display.BackgroundColorBot = Color.LightGray;
                    display.SolidGridColor = Color.LightGray;
                    display.DashedGridColor = Color.LightGray;
                    break;
                case "black":
                    display.BackgroundColorTop = Color.Black;
                    display.BackgroundColorBot = Color.Black;
                    display.SolidGridColor = Color.DarkGray;
                    display.DashedGridColor = Color.DarkGray;
                    break;
            }
        }

        protected void SetupGraph(Color colour, int index)
        {
            this.SuspendLayout();

            display.DataSources.Clear();
            display.SetDisplayRangeX(0, 500);

            display.DataSources.Add(new DataSource());
            display.DataSources[index].Name = "Sensor data";
            display.DataSources[index].OnRenderXAxisLabel += RenderXLabel;

            this.Text = "Monitor";
            display.PanelLayout = PlotterGraphPaneEx.LayoutMode.STACKED;
            display.DataSources[index].Length = 500;
            display.DataSources[index].AutoScaleY = false;
            display.DataSources[index].AutoScaleX = true;
            display.DataSources[index].XAutoScaleOffset = 50;
            display.DataSources[index].SetDisplayRangeY(0, 75000);
            display.DataSources[index].SetGridDistanceY(10000);
            display.DataSources[index].OnRenderYAxisLabel = RenderYLabel;
            display.DataSources[index].GraphColor = colour;

            DataSource src = display.DataSources[index];
            for (int i = 0; i < src.Length; i++)
            { 
                src.Samples[i].y = 10000; src.Samples[i].x = i; 
            }

            this.ResumeLayout();
        }

        private String RenderXLabel(DataSource s, int idx)
        {
            if (s.AutoScaleX)
            {
                int Value = (int)(s.Samples[idx].x);
                return "" + Value;
            }
            else
            {
                int Value = (int)(s.Samples[idx].x / 200);
                String Label = "" + Value + "\"";
                return Label;
            }
        }

        private String RenderYLabel(DataSource s, float value)
        {
            return String.Format("{0:00}", value);
        }
    }
}

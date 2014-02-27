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
            
            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;
            display.Refresh();

            mTimer = new PrecisionTimer.Timer();
            mTimer.Period = 100;         // Milliseconds between frames
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
            display.SetDisplayRangeX(0, 400);

            display.DataSources.Add(new DataSource());
            display.DataSources[index].Name = "Sensor data";
            display.DataSources[index].OnRenderXAxisLabel += RenderXLabel;

            this.Text = "Running dynamic graph";
            display.PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL;
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
            { src.Samples[i].y = 0; src.Samples[i].x = i; }

            this.ResumeLayout();
        }

        //protected void CalcDataGraphs(string example)
        //{
        //    this.SuspendLayout();

        //    display.DataSources.Clear();
        //    display.SetDisplayRangeX(0, 400);

        //    for (int j = 0; j < NumGraphs; j++)
        //    {
        //        display.DataSources.Add(new DataSource());
        //        display.DataSources[j].Name = "Sensor data";
        //        display.DataSources[j].OnRenderXAxisLabel += RenderXLabel;

        //        switch (example)
        //        {
        //            case "ANIMATED_AUTO":
        //                this.Text = "Animated graphs fixed x range";
        //                display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
        //                display.DataSources[j].Length = 402;
        //                display.DataSources[j].AutoScaleY = false;
        //                display.DataSources[j].AutoScaleX = true;
        //                display.DataSources[j].SetDisplayRangeY(-300, 500);
        //                display.DataSources[j].SetGridDistanceY(100);
        //                display.DataSources[j].XAutoScaleOffset = 50;
        //                CalcSinusFunction_3(display.DataSources[j], j, 0);
        //                display.DataSources[j].OnRenderYAxisLabel = RenderYLabel;
        //                break;
        //        }
        //    }

        //    this.ResumeLayout();
        //}

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

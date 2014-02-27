using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

using GraphLib;


namespace Sleepwalker
{
    public partial class MainForm
    {
        private int NumGraphs = 1;
        private PrecisionTimer.Timer mTimer = null;
        
        private void InitializeGraphlib(EventHandler onTimerTick)
        {
            CalcDataGraphs("DYNAMICGRAPH" /*"ANIMATED_AUTO" "TILED_VERTICAL_AUTO" */);
            ApplyColorSchema("DARK_GREEN");

            display.Smoothing = System.Drawing.Drawing2D.SmoothingMode.None;
            display.Refresh();

            mTimer = new PrecisionTimer.Timer();
            mTimer.Period = 40;         // 20 fps
            mTimer.Tick += onTimerTick; //  new EventHandler(OnTimerTick);
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

        //private DateTime lastTimerTick = DateTime.Now;
        //private void OnTimerTick(object sender, EventArgs e)
        //{
        //    if (CurExample == "ANIMATED_AUTO")
        //    {
        //        try
        //        {
        //            TimeSpan dt = DateTime.Now - lastTimerTick;

        //            for (int j = 0; j < NumGraphs; j++)
        //            {
        //                CalcSinusFunction_3(display.DataSources[j], j, (float)dt.TotalMilliseconds);
        //            }

        //            this.Invoke(new MethodInvoker(RefreshGraph));
        //        }
        //        catch (ObjectDisposedException)
        //        {
        //            // we get this on closing of form
        //        }
        //        catch (Exception ex)
        //        {
        //            Console.Write("exception invoking refreshgraph(): " + ex.Message);
        //        }
        //    }
        //}

        //private void StartGraph()
        //{
        //    lastTimerTick = DateTime.Now;
        //    mTimer.Start();
        //}

        //private void StopGraph()
        //{
        //    mTimer.Stop();
        //}

        private void RefreshGraph()
        {
            display.Refresh();
        }

        private void ApplyColorSchema(string schema)
        {
            switch (schema)
            {
                case "DARK_GREEN":
                    {
                        Color[] cols = { Color.FromArgb(0,255,0), 
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(0,255,0), 
                                         Color.FromArgb(0,255,0), 
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(0,255,0),                              
                                         Color.FromArgb(0,255,0) };

                        for (int j = 0; j < NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.FromArgb(0, 64, 0);
                        display.BackgroundColorBot = Color.FromArgb(0, 64, 0);
                        display.SolidGridColor = Color.FromArgb(0, 128, 0);
                        display.DashedGridColor = Color.FromArgb(0, 128, 0);
                    }
                    break;
                case "WHITE":
                    {
                        Color[] cols = { Color.DarkRed, 
                                         Color.DarkSlateGray,
                                         Color.DarkCyan, 
                                         Color.DarkGreen, 
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,                              
                                         Color.DeepPink };

                        for (int j = 0; j < NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.White;
                        display.BackgroundColorBot = Color.White;
                        display.SolidGridColor = Color.LightGray;
                        display.DashedGridColor = Color.LightGray;
                    }
                    break;

                case "BLUE":
                    {
                        Color[] cols = { Color.Red, 
                                         Color.Orange,
                                         Color.Yellow, 
                                         Color.LightGreen, 
                                         Color.Blue ,
                                         Color.DarkSalmon,                              
                                         Color.LightPink };

                        for (int j = 0; j < NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.Navy;
                        display.BackgroundColorBot = Color.FromArgb(0, 0, 64);
                        display.SolidGridColor = Color.Blue;
                        display.DashedGridColor = Color.Blue;
                    }
                    break;

                case "GRAY":
                    {
                        Color[] cols = { Color.DarkRed, 
                                         Color.DarkSlateGray,
                                         Color.DarkCyan, 
                                         Color.DarkGreen, 
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,                              
                                         Color.DeepPink };

                        for (int j = 0; j < NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.White;
                        display.BackgroundColorBot = Color.LightGray;
                        display.SolidGridColor = Color.LightGray;
                        display.DashedGridColor = Color.LightGray;
                    }
                    break;

                case "RED":
                    {
                        Color[] cols = { Color.DarkCyan, 
                                         Color.Yellow,
                                         Color.DarkCyan, 
                                         Color.DarkGreen, 
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,                              
                                         Color.DeepPink };

                        for (int j = 0; j < NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.DarkRed;
                        display.BackgroundColorBot = Color.Black;
                        display.SolidGridColor = Color.Red;
                        display.DashedGridColor = Color.Red;
                    }
                    break;

                case "LIGHT_BLUE":
                    {
                        Color[] cols = { Color.DarkRed, 
                                         Color.DarkSlateGray,
                                         Color.DarkCyan, 
                                         Color.DarkGreen, 
                                         Color.DarkBlue ,
                                         Color.DarkMagenta,                              
                                         Color.DeepPink };

                        for (int j = 0; j < NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.White;
                        display.BackgroundColorBot = Color.FromArgb(183, 183, 255);
                        display.SolidGridColor = Color.Blue;
                        display.DashedGridColor = Color.Blue;
                    }
                    break;

                case "BLACK":
                    {
                        Color[] cols = { Color.FromArgb(255,0,0), 
                                         Color.FromArgb(0,255,0),
                                         Color.FromArgb(255,255,0), 
                                         Color.FromArgb(64,64,255), 
                                         Color.FromArgb(0,255,255) ,
                                         Color.FromArgb(255,0,255),                              
                                         Color.FromArgb(255,128,0) };

                        for (int j = 0; j < NumGraphs; j++)
                        {
                            display.DataSources[j].GraphColor = cols[j % 7];
                        }

                        display.BackgroundColorTop = Color.Black;
                        display.BackgroundColorBot = Color.Black;
                        display.SolidGridColor = Color.DarkGray;
                        display.DashedGridColor = Color.DarkGray;
                    }
                    break;
            }

        }

        protected void CalcDataGraphs(string example)
        {
            this.SuspendLayout();

            display.DataSources.Clear();
            display.SetDisplayRangeX(0, 400);

            for (int j = 0; j < NumGraphs; j++)
            {
                display.DataSources.Add(new DataSource());
                display.DataSources[j].Name = "Graph " + (j + 1);
                display.DataSources[j].OnRenderXAxisLabel += RenderXLabel;

                switch (example)
                {
                    //case "NORMAL":
                    //    this.Text = "Normal Graph";
                    //    display.DataSources[j].Length = 5800;
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL;
                    //    display.DataSources[j].AutoScaleY = false;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 300);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    display.DataSources[j].OnRenderYAxisLabel = RenderYLabel;
                    //    CalcSinusFunction_0(display.DataSources[j], j);
                    //    break;

                    //case "NORMAL_AUTO":
                    //    this.Text = "Normal Graph Autoscaled";
                    //    display.DataSources[j].Length = 5800;
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL;
                    //    display.DataSources[j].AutoScaleY = true;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 300);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    display.DataSources[j].OnRenderYAxisLabel = RenderYLabel;
                    //    CalcSinusFunction_0(display.DataSources[j], j);
                    //    break;

                    //case "STACKED":
                    //    this.Text = "Stacked Graph";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.STACKED;
                    //    display.DataSources[j].Length = 5800;
                    //    display.DataSources[j].AutoScaleY = false;
                    //    display.DataSources[j].SetDisplayRangeY(-250, 250);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    CalcSinusFunction_1(display.DataSources[j], j);
                    //    break;

                    //case "VERTICAL_ALIGNED":
                    //    this.Text = "Vertical aligned Graph";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.VERTICAL_ARRANGED;
                    //    display.DataSources[j].Length = 5800;
                    //    display.DataSources[j].AutoScaleY = false;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 300);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    CalcSinusFunction_2(display.DataSources[j], j);
                    //    break;

                    //case "VERTICAL_ALIGNED_AUTO":
                    //    this.Text = "Vertical aligned Graph autoscaled";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.VERTICAL_ARRANGED;
                    //    display.DataSources[j].Length = 5800;
                    //    display.DataSources[j].AutoScaleY = true;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 300);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    CalcSinusFunction_2(display.DataSources[j], j);
                    //    break;

                    //case "TILED_VERTICAL":
                    //    this.Text = "Tiled Graphs (vertical prefered)";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_VER;
                    //    display.DataSources[j].Length = 5800;
                    //    display.DataSources[j].AutoScaleY = false;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 600);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    CalcSinusFunction_2(display.DataSources[j], j);
                    //    break;

                    //case "TILED_VERTICAL_AUTO":
                    //    this.Text = "Tiled Graphs (vertical prefered) autoscaled";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_VER;
                    //    display.DataSources[j].Length = 5800;
                    //    display.DataSources[j].AutoScaleY = true;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 600);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    CalcSinusFunction_2(display.DataSources[j], j);
                    //    break;

                    //case "TILED_HORIZONTAL":
                    //    this.Text = "Tiled Graphs (horizontal prefered)";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
                    //    display.DataSources[j].Length = 5800;
                    //    display.DataSources[j].AutoScaleY = false;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 600);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    CalcSinusFunction_2(display.DataSources[j], j);
                    //    break;

                    //case "TILED_HORIZONTAL_AUTO":
                    //    this.Text = "Tiled Graphs (horizontal prefered) autoscaled";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
                    //    display.DataSources[j].Length = 5800;
                    //    display.DataSources[j].AutoScaleY = true;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 600);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    CalcSinusFunction_2(display.DataSources[j], j);
                    //    break;

                    //case "ANIMATED_AUTO":
                    //    this.Text = "Animated graphs fixed x range";
                    //    display.PanelLayout = PlotterGraphPaneEx.LayoutMode.TILES_HOR;
                    //    display.DataSources[j].Length = 402;
                    //    display.DataSources[j].AutoScaleY = false;
                    //    display.DataSources[j].AutoScaleX = true;
                    //    display.DataSources[j].SetDisplayRangeY(-300, 500);
                    //    display.DataSources[j].SetGridDistanceY(100);
                    //    display.DataSources[j].XAutoScaleOffset = 50;
                    //    CalcSinusFunction_3(display.DataSources[j], j, 0);
                    //    display.DataSources[j].OnRenderYAxisLabel = RenderYLabel;
                    //    break;

                    case "DYNAMICGRAPH":
                        this.Text = "Running dynamic graph";
                        display.PanelLayout = PlotterGraphPaneEx.LayoutMode.NORMAL; //PlotterGraphPaneEx.LayoutMode.TILES_HOR;
                        display.DataSources[j].Length = 500;
                        display.DataSources[j].AutoScaleY = false;
                        display.DataSources[j].AutoScaleX = true;
                        display.DataSources[j].XAutoScaleOffset = 50;
                        display.DataSources[j].SetDisplayRangeY(0, 55000);
                        display.DataSources[j].SetGridDistanceY(10000);
                        display.DataSources[j].OnRenderYAxisLabel = RenderYLabel;
                        break;
                }
            }

            this.ResumeLayout();
        }

        private String RenderXLabel(DataSource s, int idx)
        {
            if (s.AutoScaleX)
            {
                //if (idx % 2 == 0)
                {
                    int Value = (int)(s.Samples[idx].x);
                    return "" + Value;
                }
                //return "";
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
            return String.Format("{0}", value);
        }

        protected void CalcSinusFunction_0(DataSource src, int idx)
        {
            for (int i = 0; i < src.Length; i++)
            {
                src.Samples[i].x = i;
                src.Samples[i].y = (float)(((float)200 * Math.Sin((idx + 1) * (i + 1.0) * 48 / src.Length)));
            }
        }

        protected void CalcSinusFunction_1(DataSource src, int idx)
        {
            for (int i = 0; i < src.Length; i++)
            {
                src.Samples[i].x = i;

                src.Samples[i].y = (float)(((float)20 *
                                            Math.Sin(20 * (idx + 1) * (i + 1) * 3.141592 / src.Length)) *
                                            Math.Sin(40 * (idx + 1) * (i + 1) * 3.141592 / src.Length)) +
                                            (float)(((float)200 *
                                            Math.Sin(200 * (idx + 1) * (i + 1) * 3.141592 / src.Length)));
            }
            src.OnRenderYAxisLabel = RenderYLabel;
        }

        protected void CalcSinusFunction_2(DataSource src, int idx)
        {
            for (int i = 0; i < src.Length; i++)
            {
                src.Samples[i].x = i;

                src.Samples[i].y = (float)(((float)20 *
                                            Math.Sin(40 * (idx + 1) * (i + 1) * 3.141592 / src.Length)) *
                                            Math.Sin(160 * (idx + 1) * (i + 1) * 3.141592 / src.Length)) +
                                            (float)(((float)200 *
                                            Math.Sin(4 * (idx + 1) * (i + 1) * 3.141592 / src.Length)));
            }
            src.OnRenderYAxisLabel = RenderYLabel;
        }

        protected void CalcSinusFunction_3(DataSource ds, int idx, float time)
        {
            cPoint[] src = ds.Samples;
            for (int i = 0; i < src.Length; i++)
            {
                src[i].x = i;
                src[i].y = 200 + (float)((200 * Math.Sin((idx + 1) * (time + i * 100) / 8000.0))) +
                                +(float)((40 * Math.Sin((idx + 1) * (time + i * 200) / 2000.0)));
            }

        }
    }
}

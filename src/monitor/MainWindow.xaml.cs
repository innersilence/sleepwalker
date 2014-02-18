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
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using Microsoft.Research.DynamicDataDisplay;
using Microsoft.Research.DynamicDataDisplay.DataSources;
using Microsoft.Research.DynamicDataDisplay.PointMarkers;
using System.Globalization;


namespace DataMonitor
{
    public partial class MainWindow : Window
    {
        double phase = 0;
        readonly double[] animatedX = new double[1000];
        readonly double[] animatedY = new double[1000];
        //FixedSizedQueue<double> anuimatedX = new FixedSizedQueue<double>();
        //FixedSizedQueue<double> anuimatedX = new FixedSizedQueue<double>();
       
        readonly DispatcherTimer timer = new DispatcherTimer();
        Header chartHeader = new Header();
        TextBlock headerContents = new TextBlock();
        EnumerableDataSource<double> animatedDataSource = null;

        public MainWindow()
        {
            InitializeComponent();
            headerContents.FontSize = 24;
            headerContents.Text = "Heart Rate = 0.00";
            headerContents.HorizontalAlignment = HorizontalAlignment.Center;
            chartHeader.Content = headerContents;
            plotter.Children.Add(chartHeader);
            // RenderOptions.SetEdgeMode(plotter, EdgeMode.Aliased); // http://dynamicdatadisplay.codeplex.com/discussions/74901
        }

        private void AnimatedPlot_Timer(object sender, EventArgs e)
        {
            phase += 0.1;

            if (phase > 2 * Math.PI)
            {
                phase -= 2 * Math.PI;
            }

            for (int i = 0; i < animatedX.Length; i++)
            {
                animatedY[i] = Math.Sin(animatedX[i] + phase);
            }

            animatedDataSource.RaiseDataChanged();
            headerContents.Text = String.Format(CultureInfo.InvariantCulture, "Heart Rate = {0:N2}", phase);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < animatedX.Length; i++)
            {
                animatedX[i] = 2 * Math.PI * i / animatedX.Length;
                animatedY[i] = Math.Sin(animatedX[i]);
            }

            EnumerableDataSource<double> xSrc = new EnumerableDataSource<double>(animatedX);
            xSrc.SetXMapping(x => x);
            animatedDataSource = new EnumerableDataSource<double>(animatedY);
            animatedDataSource.SetYMapping(y => y);

            plotter.AddLineGraph(new CompositeDataSource(xSrc, animatedDataSource), new Pen(Brushes.Magenta, 3), new PenDescription("Heart Rate"));

            timer.Interval = TimeSpan.FromMilliseconds(50);
            timer.Tick += AnimatedPlot_Timer;
            timer.IsEnabled = true;

            plotter.FitToView();
        }
    }
}

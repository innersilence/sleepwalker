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


namespace DataMonitor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// http://research.microsoft.com/en-us/um/cambridge/projects/ddd/d3isdk/
    /// http://dynamicdatadisplay.codeplex.com/discussions/443837
    /// http://msdn.microsoft.com/en-us/magazine/ff714591.aspx
    /// http://stackoverflow.com/questions/7090345/dynamic-line-chart-in-c-sharp-wpf-application
    /// http://dynamicdatadisplay.codeplex.com/discussions/224503
    /// Animation: http://stackoverflow.com/questions/13142173/dynamicdatadisplay-chartplotter-remove-all-plots
    /// Animation: http://dynamicdatadisplay.codeplex.com/discussions/73597
    /// http://dynamicdatadisplay.codeplex.com/discussions/227992
    /// </summary>
    public partial class MainWindow : Window
    {
        //private DispatcherTimer plotTimer = new System.Windows.Threading.DispatcherTimer();

        private MonitorDataModel Model { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            Loaded += new RoutedEventHandler(MainWindow_Loaded);
            Closed += new EventHandler(MainWindow_Closed);
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs args)
        {
            Model = new MonitorDataModel();

            for (int i = 0; i < 10; i++)
            {
                Model.Values.Add(new MonitorData((double)i, TimeSpan.FromSeconds(i)));
                Model.Values.Add(new MonitorData((double)i, TimeSpan.FromSeconds(i + 1)));
            }

            DataContext = Model;
            //Model.Start();
        }

        private void MainWindow_Closed(object sender, EventArgs args)
        {
            //Model.Stop();
        }
    }
}

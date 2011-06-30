using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;
using System.Threading;
using System.Drawing.Drawing2D;
using System.Collections;
using System.Drawing.Printing;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using ZedGraph;

namespace OWTSV1
{
    public partial class Form1 : Form
    {
        #region SerialCode
        string RxString;
        string start;
        char[] hugeBuffer = new char[10000000];
        int hugeBufferCounter = 0;
        int i = 0;
        int readIndex = 0;
        int getLine = 0;
        char[] testString = new char[50];
        int liftCounter = 1;

        int weight = 0;
        double force = 0;
        double power = 0;



        bool onHold = false;
        private Thread graphThread;

        Stopwatch sw = new Stopwatch();
        
        //TextWriter tw = new StreamWriter(@"E:\OWTSdata.txt");

        private void refreshGraphs()
        {

            sw.Start();

            while (true)
            {
                if (sw.ElapsedMilliseconds >= 15)
                {
                    // only update one tab at a time here
                    if (tabControl1.SelectedTab == tabPage1)
                    {
                        zedGraphControl1.AxisChange();
                        zedGraphControl1.Invalidate();
                    } 
                    else if (tabControl1.SelectedTab == tabPage2)
                    {
                        if (true)
                        {
                            zedGraphControl2.AxisChange();
                            zedGraphControl2.Invalidate();
                        }

                    }
                    else if (tabControl1.SelectedTab == tabPage3)
                    {
                        //if (RxString != null)
                        //{
                            //textBox1.AppendText(RxString);
                        //}
                    }
                    else if (tabControl1.SelectedTab == tabPage4)
                    {
                        zedGraphControl3.AxisChange();
                        zedGraphControl3.Invalidate();
                    }
                    else if (tabControl1.SelectedTab == tabPage5)
                    {
                        pictureBox1.Invalidate();
                        pictureBox2.Invalidate();
                        pictureBox3.Invalidate();
                    }
                    

                    sw.Reset();
                    sw.Start();
                }
            }
        }



        private void SerialIOThread(object sender, EventArgs e)
        {
                try
                {
                    while (readIndex < (hugeBufferCounter - 50))
                    {
                        //start = new string(hugeBuffer);
                        int count = 0;
                        //readIndex = 0;
                        char t = 't';

                        while (t != '\0')
                        {
                            t = hugeBuffer[readIndex];
                            testString[count] = hugeBuffer[readIndex];
                            count++;
                            readIndex++;
                        }

                        start = new string(testString);
                        if (tabControl1.SelectedTab == tabPage3)
                        {
                            textBox1.AppendText(start);    
                        }
                        //tw.WriteLine(start);
                        this.Invoke(new EventHandler(parseLine));

                    }
                }
                catch { }
        }

        private void parseLine(object sender, EventArgs e)
        {
            GraphPane gp = zedGraphControl1.GraphPane;
            GraphPane gp2 = zedGraphControl2.GraphPane;
            GraphPane gp3 = zedGraphControl3.GraphPane;
            IPointListEdit list;
            
                                

                                if (!onHold)
                                {
                                    try
                                    {


                                        double time;
                                        double.TryParse(start.Substring(0, start.IndexOf(":")), out time);
                                        ChangeLabel(label7, time.ToString("  0.00") + " s");

                                        if (time == 0)
                                        {
                                            gp.CurveList[0].Clear();
                                            gp3.CurveList[0].Clear();
                                            gp3.CurveList[1].Clear();
                                            gp3.CurveList[2].Clear();
                                            gp.CurveList[1].Clear();
                                            gp.CurveList[2].Clear();
                                           
                                        }

                                        string[] lineArray = start.Substring(start.IndexOf(":") + 1).Split(new char[] { ',' });

                                        foreach (string data in lineArray)
                                        {
                                            char type = data[0];
                                            double value;
                                            double.TryParse(data.Substring(1), out value);

                                            switch (type)
                                            {
                                                case 'A':

                                                    //list = gp.CurveList[0].Points as IPointListEdit;
                                                    //list.Add(time, value);

                                                    list = gp3.CurveList[0].Points as IPointListEdit;
                                                    list.Add(time, value);

                                                    kalman_acc = Convert.ToInt32(value);

                                                    acc_angle1.Text = value.ToString("  0.00");
                                                    label17.Text = value.ToString("  0.00");
                                                    //textBox2.AppendText(value.ToString("  0.00") + " deg.");         

                                                    break;

                                                case 'B':
                                                    //list = gp.CurveList[1].Points as IPointListEdit;
                                                    //list.Add(time, value);

                                                    list = gp3.CurveList[1].Points as IPointListEdit;
                                                    list.Add(time, value);

                                                    kalman_gyro = Convert.ToInt32(value);

                                                    gyro_angle1.Text = value.ToString("  0.00");
                                                    label18.Text = value.ToString("  0.00");


                                                    //ChangeLabel(label9, value.ToString("  0.00") + " m/s");
                                                    //ChangeLabel(label18, value.ToString("  0.00") + " deg.");
                                                    break;

                                                case 'C':
                                                    //list = gp2.CurveList[0].Points as IPointListEdit;
                                                    //list.Add(time, value);

                                                    list = gp3.CurveList[2].Points as IPointListEdit;
                                                    list.Add(time, value);

                                                    kalman_filter = Convert.ToInt32(value);

                                                    kalman_angle1.Text = value.ToString("  0.00");
                                                    label19.Text = value.ToString("  0.00");

                                                    //ChangeLabel(label19, value.ToString("  0.00") + " deg.");
                                                    break;
                                                case 'D':
                                                    //list = gp2.CurveList[1].Points as IPointListEdit;
                                                    //list.Add(time, value);
                                                    label24.Text = value.ToString("  0.00"); 
                                                    break;
                                                case 'E':
                                                    //list = gp2.CurveList[2].Points as IPointListEdit;
                                                    //list.Add(time, value);
                                                    label25.Text = value.ToString("  0.00"); 
                                                    break;
                                                case 'F':
                                                    //list = gp2.CurveList[3].Points as IPointListEdit;
                                                    //list.Add(time, value);
                                                    label26.Text = value.ToString("  0.00"); 
                                                    break;

                                                case 'G':
                                                    //list = gp2.CurveList[3].Points as IPointListEdit;
                                                    //list.Add(time, value);
                                                    label30.Text = value.ToString("  0.00");
                                                    break;

                                                case 'H':
                                                    //list = gp2.CurveList[3].Points as IPointListEdit;
                                                    //list.Add(time, value);
                                                    label31.Text = value.ToString("  0.00");
                                                    break;

                                                case 'I':
                                                    //list = gp2.CurveList[3].Points as IPointListEdit;
                                                    //list.Add(time, value);
                                                    label32.Text = value.ToString("  0.00");
                                                    break;

                                                case 'J':
                                                    list = gp.CurveList[0].Points as IPointListEdit;
                                                    list.Add(time, value);

                                                    vert_acc1.Text = value.ToString("  0.00");
                                                    label8.Text = value.ToString("  0.00"); 

                                                    break;

                                                case 'K':
                                                    list = gp.CurveList[1].Points as IPointListEdit;
                                                    list.Add(time, value);

                                                    label9.Text = value.ToString("  0.00"); 
                                                    label10.Text = value.ToString("  0.00"); 

                                                    break;

                                                case 'L':
                                                    //list = gp.CurveList[2].Points as IPointListEdit;
                                                    //list.Add(time, value);

                                                    label20.Text = value.ToString("  0.00"); 
                                                    break;

                                                case 'M':
                                                    list = gp2.CurveList[0].Points as IPointListEdit;
                                                    list.Add(liftCounter, value);
                                                    label40.Text = value.ToString("  0.00");
                                                    label36.Text = value.ToString("  0.00"); 

                                                    force = weight * value;
                                                    //list = gp2.CurveList[3].Points as IPointListEdit;
                                                    //list.Add(liftCounter, force);
                                                    label43.Text = force.ToString("  0.00"); 
                                                    
                                                    
                                                    break;

                                                case 'N':
                                                    list = gp2.CurveList[1].Points as IPointListEdit;
                                                    list.Add(liftCounter, value);
                                                    label41.Text = value.ToString("  0.00");
                                                    label37.Text = value.ToString("  0.00"); 

                                                    power = force * value;
                                                    //list = gp2.CurveList[2].Points as IPointListEdit;
                                                    //list.Add(liftCounter, power);
                                                    label42.Text = power.ToString("  0.00"); 

                                                    liftCounter++;

                                                    break;
                                            }
                                        }
                                    }
                                    catch
                                    { }
                                }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            OpenConnectionForm ocf = new OpenConnectionForm();
            DialogResult result = ocf.ShowDialog();

            if (result == DialogResult.OK)
            {
                try
                {
                    serialPort1.PortName = ocf.Port;
                    serialPort1.BaudRate = 115200;//921600;//9600;
                    //serialPort1.ReceivedBytesThreshold = 10;
                    //serialPort1.ReadBufferSize = 128;

                    serialPort1.Open();
                    //serialPort1.Handshake = Handshake.None;
                    //serialPort1.NewLine = "\r\n";

                    serialPort1.ReceivedBytesThreshold = 10;

                    //serialPort1.DiscardInBuffer();
                    //serialPort1.DiscardOutBuffer();


                    ChangeLabel(label6, "Connected to " + ocf.Port);


                }
                catch (Exception ex)
                {
                    MessageBox.Show("Unable to open device. " + ex.Message, "Device Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
 
        }

        private void DisplayText(object sender, EventArgs e)
        {
            //            textBox1.AppendText(RxString);

            try
            {
                for (i = 0; i < (RxString.Length); i++)
                {
                    //if (hugeBufferCounter < 5000000)
                    {
                        hugeBuffer[hugeBufferCounter] = RxString[i];
                        hugeBufferCounter++;
                        if (RxString[i] == '\n')
                        {
                            hugeBuffer[hugeBufferCounter] = '\0';
                            hugeBufferCounter++;
                            //this.Invoke(new EventHandler(SerialIOThread));
                            //SerialIOThread();
                        }
                    }
                }
            }
            catch { }

        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            RxString = serialPort1.ReadExisting();
            this.Invoke(new EventHandler(DisplayText));
            this.Invoke(new EventHandler(SerialIOThread));
            //textBox1.AppendText(RxString);            
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                graphThread.Abort();
                //Process.Start(@"C:\OWTSdata.txt");
                //tw.Close();
                //txtFile.Dispose();
            }
            catch { }
        }
        #endregion


        public void CreateMeasurementChart(ZedGraphControl zgc)
        {
            GraphPane myPane = zgc.GraphPane;

            // Set the titles and axis labels
            myPane.Title.Text = "Barbell Measurements";
            myPane.XAxis.Title.Text = "Time";
            myPane.YAxis.Title.Text = "Acceleration";
            myPane.Y2Axis.Title.Text = "Velocity";

            // Make up some data points based on the Sine function
            //RollingPointPairList list = new RollingPointPairList(500);
            //RollingPointPairList list2 = new RollingPointPairList(500);

            PointPairList list = new PointPairList();
            PointPairList list2 = new PointPairList();
//            PointPairList list3 = new PointPairList();

            // Generate a red curve with diamond symbols, and "Alpha" in the legend
            LineItem myCurve = myPane.AddCurve("Acceleration",
               list, Color.Red, SymbolType.None);
            // Fill the symbols with white
            myCurve.Symbol.Fill = new Fill(Color.White);
            myCurve.Line.Width = 2.5F;

            myCurve = myPane.AddCurve("Velocity",
               list2, Color.Blue, SymbolType.None);
            // Fill the symbols with white
            myCurve.Line.Width = 2.5F;
            // Generate a blue curve with circle symbols, and "Beta" in the legend
            // Associate this curve with the Y2 axis
            myCurve.IsY2Axis = true;

            // Generate a green curve with square symbols, and "Distance" in the legend
//            myCurve = myPane.AddCurve("Displacement",
//               list3, Color.Green, SymbolType.None);
            // Fill the symbols with white
//            myCurve.Line.Width = 2.5F;
//           myCurve.Symbol.Fill = new Fill(Color.White);
            // Associate this curve with the second Y axis
//            myCurve.YAxisIndex = 1;

            // Show the x axis grid
            //myPane.XAxis.MajorGrid.IsVisible = true;

            // Make the Y axis scale red
            myPane.YAxis.Scale.FontSpec.FontColor = Color.Red;
            myPane.YAxis.Title.FontSpec.FontColor = Color.Red;
            // turn off the opposite tics so the Y tics don't show up on the Y2 axis
            myPane.YAxis.MajorTic.IsOpposite = false;
            myPane.YAxis.MinorTic.IsOpposite = false;
            // Don't display the Y zero line
            myPane.YAxis.MajorGrid.IsZeroLine = true;
            // Align the Y axis labels so they are flush to the axis
            myPane.YAxis.Scale.Align = AlignP.Inside;
            // Manually set the axis range
            myPane.YAxis.Scale.Min = -20;
            myPane.YAxis.Scale.Max = 30;

            // Enable the Y2 axis display
            myPane.Y2Axis.IsVisible = true;
            // Make the Y2 axis scale blue
            myPane.Y2Axis.Scale.FontSpec.FontColor = Color.Blue;
            myPane.Y2Axis.Title.FontSpec.FontColor = Color.Blue;
            // turn off the opposite tics so the Y2 tics don't show up on the Y axis
            myPane.Y2Axis.MajorTic.IsOpposite = false;
            myPane.Y2Axis.MinorTic.IsOpposite = false;
            // Display the Y2 axis grid lines
            myPane.Y2Axis.MajorGrid.IsVisible = true;
            // Align the Y2 axis labels so they are flush to the axis
            myPane.Y2Axis.Scale.Align = AlignP.Inside;
            myPane.Y2Axis.MajorGrid.IsZeroLine = false;
            myPane.Y2Axis.Scale.Min = -10;
            myPane.Y2Axis.Scale.Max = 15;

            // Create a second Y Axis, green
//            YAxis yAxis3 = new YAxis("Displacement");
//            myPane.YAxisList.Add(yAxis3);
//            yAxis3.Scale.FontSpec.FontColor = Color.Green;
//            yAxis3.Title.FontSpec.FontColor = Color.Green;
//            yAxis3.Color = Color.Green;
            // turn off the opposite tics so the Y2 tics don't show up on the Y axis
//            yAxis3.MajorTic.IsInside = false;
//            yAxis3.MinorTic.IsInside = false;
//            yAxis3.MajorTic.IsOpposite = false;
//            yAxis3.MinorTic.IsOpposite = false;
            // Align the Y2 axis labels so they are flush to the axis
//            yAxis3.Scale.Align = AlignP.Inside;
//            yAxis3.Scale.Min = -2;
//            yAxis3.Scale.Max = 3;
            

            myPane.XAxis.Scale.MinorStep = 10;
            myPane.XAxis.Scale.MajorStep = 10;

            myPane.XAxis.Scale.MaxGrace = 0;
            myPane.XAxis.Scale.MinGrace = 0;


            // Fill the axis background with a gradient
            myPane.Chart.Fill = new Fill(Color.White, Color.LightGray, 45.0f);

            // Calculate the Axis Scale Ranges
            zgc.AxisChange();
        }

        public void CreateSummaryChart(ZedGraphControl zgc)
        {
            GraphPane myPane = zgc.GraphPane;

            // Set the titles and axis labels
            myPane.Title.Text = "Summary for Current Set";
            myPane.XAxis.Title.Text = "Lift number";
            myPane.YAxis.Title.Text = "Peak Acceleration";
            myPane.Y2Axis.Title.Text = "Peak Velocity";
            
            // Make up some data points based on the Sine function
            RollingPointPairList list1 = new RollingPointPairList(500);
            RollingPointPairList list2 = new RollingPointPairList(500);
            RollingPointPairList list3 = new RollingPointPairList(500);
            RollingPointPairList list4 = new RollingPointPairList(500);


            // Generate a red curve with diamond symbols, and "Alpha" in the legend
            LineItem myCurve = myPane.AddCurve("Acceleration",
               list1, Color.Red, SymbolType.Diamond);
            // Fill the symbols with white
            myCurve.Symbol.Fill = new Fill(Color.White);
            myCurve.Line.Width = 2.5F;

            // Generate a blue curve with circle symbols, and "Beta" in the legend
            myCurve = myPane.AddCurve("Velocity",
               list2, Color.Blue, SymbolType.Circle);
            // Fill the symbols with white
            myCurve.Symbol.Fill = new Fill(Color.White);
            // Associate this curve with the Y2 axis
            myCurve.IsY2Axis = true;
            myCurve.Line.Width = 2.5F;

            // Generate a green curve with square symbols, and "Distance" in the legend
            myCurve = myPane.AddCurve("Power",
               list3, Color.Green, SymbolType.Square);
            // Fill the symbols with white
            myCurve.Symbol.Fill = new Fill(Color.White);
            // Associate this curve with the second Y axis
            myCurve.YAxisIndex = 1;
            myCurve.Line.Width = 2.5F;

            // Generate a Black curve with triangle symbols, and "Energy" in the legend
            myCurve = myPane.AddCurve("Force",
               list4, Color.Black, SymbolType.Triangle);
            // Fill the symbols with white
            myCurve.Symbol.Fill = new Fill(Color.White);
            // Associate this curve with the Y2 axis
            myCurve.IsY2Axis = true;
            // Associate this curve with the second Y2 axis
            myCurve.YAxisIndex = 1;
            myCurve.Line.Width = 2.5F;




            // Show the x axis grid
            myPane.XAxis.MajorGrid.IsVisible = true;

            // Make the Y axis scale red
            myPane.YAxis.Scale.FontSpec.FontColor = Color.Red;
            myPane.YAxis.Title.FontSpec.FontColor = Color.Red;
            // turn off the opposite tics so the Y tics don't show up on the Y2 axis
            myPane.YAxis.MajorTic.IsOpposite = false;
            myPane.YAxis.MinorTic.IsOpposite = false;
            // Don't display the Y zero line
            myPane.YAxis.MajorGrid.IsZeroLine = true;
            // Align the Y axis labels so they are flush to the axis
            myPane.YAxis.Scale.Align = AlignP.Inside;
            // Manually set the axis range
            //myPane.YAxis.Scale.Min = -30;
            //myPane.YAxis.Scale.Max = 30;
            
            // Enable the Y2 axis display
            myPane.Y2Axis.IsVisible = true;
            // Make the Y2 axis scale blue
            myPane.Y2Axis.Scale.FontSpec.FontColor = Color.Blue;
            myPane.Y2Axis.Title.FontSpec.FontColor = Color.Blue;
            // turn off the opposite tics so the Y2 tics don't show up on the Y axis
            myPane.Y2Axis.MajorTic.IsOpposite = false;
            myPane.Y2Axis.MinorTic.IsOpposite = false;
            // Display the Y2 axis grid lines
            myPane.Y2Axis.MajorGrid.IsVisible = true;
            // Align the Y2 axis labels so they are flush to the axis
            myPane.Y2Axis.Scale.Align = AlignP.Inside;

            // Create a second Y Axis, green
            YAxis yAxis3 = new YAxis("Peak Power");
            myPane.YAxisList.Add(yAxis3);
            yAxis3.Scale.FontSpec.FontColor = Color.Green;
            yAxis3.Title.FontSpec.FontColor = Color.Green;
            yAxis3.Color = Color.Green;
            // turn off the opposite tics so the Y2 tics don't show up on the Y axis
            yAxis3.MajorTic.IsInside = false;
            yAxis3.MinorTic.IsInside = false;
            yAxis3.MajorTic.IsOpposite = false;
            yAxis3.MinorTic.IsOpposite = false;
            // Align the Y2 axis labels so they are flush to the axis
            yAxis3.Scale.Align = AlignP.Inside;

            Y2Axis yAxis4 = new Y2Axis("Peak Force");
            yAxis4.IsVisible = true;
            myPane.Y2AxisList.Add(yAxis4);
            // turn off the opposite tics so the Y2 tics don't show up on the Y axis
            yAxis4.MajorTic.IsInside = false;
            yAxis4.MinorTic.IsInside = false;
            yAxis4.MajorTic.IsOpposite = false;
            yAxis4.MinorTic.IsOpposite = false;
            // Align the Y2 axis labels so they are flush to the axis
            yAxis4.Scale.Align = AlignP.Inside;
            //yAxis4.Type = AxisType.Log;
            //yAxis4.Scale.Min = 100;


            myPane.XAxis.Scale.MinorStep = 1;
            myPane.XAxis.Scale.MajorStep = 5;

            // Fill the axis background with a gradient
            myPane.Chart.Fill = new Fill(Color.White, Color.LightGray, 45.0f);

            // Calculate the Axis Scale Ranges
            zgc.AxisChange();
        }

        public void CreateKalmanChart(ZedGraphControl zgc)
        {
            GraphPane myPane = zgc.GraphPane;

            // Set the titles and axis labels
            myPane.Title.Text = "Kalman Filter Demonstration";
            myPane.XAxis.Title.Text = "Time";
            myPane.YAxis.Title.Text = "Rotation";

            // Make up some data points based on the Sine function
            PointPairList list1 = new PointPairList();
            PointPairList list2 = new PointPairList();
            PointPairList list3 = new PointPairList();


            LineItem myCurve = myPane.AddCurve("Accelerometer",
               list1, Color.Red, SymbolType.None);
            myCurve.Line.Width = 2.5F;
            myCurve = myPane.AddCurve("Gyroscope",
               list2, Color.Blue, SymbolType.None);
            myCurve.Line.Width = 2.5F;
            myCurve = myPane.AddCurve("Kalman Filter",
               list3, Color.Green, SymbolType.None);
            myCurve.Line.Width = 2.5F;

            // Show the x axis grid
            //myPane.XAxis.MajorGrid.IsVisible = true;
            // Make the Y axis scale Black
            myPane.YAxis.Scale.FontSpec.FontColor = Color.Black;
            myPane.YAxis.Title.FontSpec.FontColor = Color.Black;
            // Don't display the Y zero line
            myPane.YAxis.MajorGrid.IsZeroLine = false;
            // Align the Y axis labels so they are flush to the axis
            myPane.YAxis.Scale.Align = AlignP.Inside;
            // Manually set the axis range
            myPane.YAxis.Scale.Min = -190;
            myPane.YAxis.Scale.Max = 190;
            myPane.XAxis.Scale.MinorStep = 10;
            myPane.XAxis.Scale.MajorStep = 10;


            myPane.XAxis.Scale.MaxGrace = 0;
            myPane.XAxis.Scale.MinGrace = 0;


            // Fill the axis background with a gradient
            myPane.Chart.Fill = new Fill(Color.White, Color.LightGray, 45.0f);

            // Calculate the Axis Scale Ranges
            zgc.AxisChange();
        }



        private void ChangeLabel(System.Windows.Forms.Label label, string text)
        {
            if (InvokeRequired)
            {
                Invoke(new MethodInvoker(delegate() { label.Text = text; }));
                return;
            }

            label.Text = text;
        }


        private System.Drawing.Brush myBrush = new SolidBrush(System.Drawing.Color.Black);
        private System.Drawing.Pen myPen = new Pen(System.Drawing.Color.Black, 3);
        private System.Drawing.Pen pen1 = new System.Drawing.Pen(Color.Blue, 2F);
        //private System.Drawing.Rectangle myRectangle = new Rectangle(20, 80, 300, 300);
        private System.Drawing.Rectangle myRectangle = new Rectangle(-150, -150, 300, 300);
        private System.Drawing.Rectangle myRectangle2 = new Rectangle(355, 80, 300, 300);
        private System.Drawing.Rectangle myRectangle3 = new Rectangle(690, 80, 300, 300);

        private System.Drawing.SolidBrush solidBrush = new SolidBrush(Color.Blue);
        private System.Drawing.SolidBrush solidBrush2 = new SolidBrush(Color.Green);

        private Int32 kalman_acc = 0;
        private Int32 kalman_gyro = 0;
        private Int32 kalman_filter = 0;





        public Form1()
        {
            InitializeComponent();


            CreateMeasurementChart(zedGraphControl1);
            CreateSummaryChart(zedGraphControl2);
            CreateKalmanChart(zedGraphControl3);

            try
            {
                // cant seem to write to C drive (protected?)
                //TextWriter tw = new StreamWriter(@"D:\OWTSdata.txt");
                //tw.WriteLine("Hello");
                //tw.Close();
            }
            catch { }

            textBox2.Text = null;

            graphThread = new Thread(new ThreadStart(refreshGraphs));
            graphThread.Start();


            //textBox1.AppendText("teng" + "\n");
        }

        private void checkBox1_CheckStateChanged(object sender, EventArgs e)
        {
            GraphPane gp = zedGraphControl1.GraphPane;
            IPointListEdit list = gp.CurveList[0].Points as IPointListEdit;
            list.Clear();
        }


        LinearGradientBrush linGrBrush = new LinearGradientBrush(

        new Point(0, -150),
        new Point(0, 1),
        Color.FromArgb(255, 0, 0, 255),   // Opaque red
        Color.FromArgb(255, 51, 204, 255));  // Opaque blue

        LinearGradientBrush linGrBrush2 = new LinearGradientBrush(
        new Point(0, 0),
        new Point(0, 150),
        Color.FromArgb(255, 0, 100, 0),   // Opaque red
        Color.FromArgb(255, 0, 200, 0));  // Opaque blue

        
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            e.Graphics.TranslateTransform(200, 280);

            //e.Graphics.FillPie(linGrBrush, myRectangle, Convert.ToInt32(kalman_acc) + 180, 180);
            //e.Graphics.FillPie(solidBrush, myRectangle, 180, 180);
            e.Graphics.RotateTransform(Convert.ToInt32(-kalman_acc));
            e.Graphics.FillPie(linGrBrush, myRectangle, 180, 180);
            e.Graphics.FillPie(linGrBrush2, myRectangle, 0, 180);

            //e.Graphics.TranslateTransform(-170, -230);

            //e.Graphics.TranslateTransform(505, 230);
            //e.Graphics.RotateTransform(Convert.ToInt32(kalman_gyro));
            //e.Graphics.FillPie(linGrBrush, myRectangle, 180, 180);
            //e.Graphics.FillPie(linGrBrush2, myRectangle, 0, 180);
            //e.Graphics.FillPie(solidBrush, myRectangle2, Convert.ToInt32(kalman_gyro) + 180, 180);
            //e.Graphics.FillPie(solidBrush2, myRectangle2, Convert.ToInt32(kalman_gyro), 180);

            //e.Graphics.FillPie(solidBrush, myRectangle3, Convert.ToInt32(kalman_filter) + 180, 180);
            //e.Graphics.FillPie(solidBrush2, myRectangle3, Convert.ToInt32(kalman_filter), 180);


        }

        private void pictureBox2_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            e.Graphics.TranslateTransform(200, 280);

            e.Graphics.RotateTransform(Convert.ToInt32(-kalman_gyro));
            e.Graphics.FillPie(linGrBrush, myRectangle, 180, 180);
            e.Graphics.FillPie(linGrBrush2, myRectangle, 0, 180);
        }

        private void pictureBox3_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            e.Graphics.TranslateTransform(200, 280);

            e.Graphics.RotateTransform(Convert.ToInt32(-kalman_filter));
            e.Graphics.FillPie(linGrBrush, myRectangle, 180, 180);
            e.Graphics.FillPie(linGrBrush2, myRectangle, 0, 180);
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                weight = Int32.Parse(textBox2.Text);
                MessageBox.Show("You selected a weight of " + textBox2.Text + " Kg");
            }
        }




    }
}

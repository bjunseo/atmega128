using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;
using System.Media;

namespace Obstacle_detection
{
    public partial class Form1 : Form
    {
        private SerialPort _serialPort;
        int Count = 1;
        
        public Form1()
        {
            InitializeComponent();

            string[] Portnom = SerialPort.GetPortNames();

            foreach (string portnum in Portnom)
            {
                PortList.Items.Add(portnum);
            }
 
        }

        private void Connect_Click(object sender, EventArgs e)
        {
            _serialPort = new SerialPort();
            if (_serialPort.IsOpen == false)
            {
                _serialPort.PortName = PortList.SelectedItem.ToString();
                _serialPort.BaudRate = 9600;
                _serialPort.DataBits = (int)8;
                _serialPort.Parity = Parity.None;
                _serialPort.StopBits = StopBits.One;
                _serialPort.ReadTimeout = (int)500;
                _serialPort.WriteTimeout = (int)500;
                _serialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);

                _serialPort.Open();

                status.Text = _serialPort.PortName + "연결되었습니다.";
            }
            else
                status.Text = _serialPort.PortName + "연결되어 있습니다.";
        }
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            this.Invoke(new EventHandler(MySerialReceived));
            //invoke
        }
        private void MySerialReceived(object s, EventArgs e)
        {
            string ReceiveData = _serialPort.ReadChar().ToString();
            Receive.Text = ReceiveData;
            Thread thread = new Thread(playWP);
            if (ReceiveData == "1")
            {
                thread.Start();
                this.BackColor = Color.Red;
                ssss.Text = "침입감지";
                
            }
            else if (ReceiveData == "2")
            {
                thread.Abort();
                this.BackColor = Color.Blue;
                ssss.Text = "침입감지중";
            }
        }
        
        private void playWP()
        {
            if(Count == 1)
            {
                Count = 0;
                SoundPlayer wp1 = new SoundPlayer("C:/Users/user/Documents/Atmel Studio/7.0/schoolbook/LaserModuale_1111/gui/녹음.wav");
                wp1.PlaySync();
                Count = 1;
            }
            else            
            {

            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }
        private void label2_Click(object sender, EventArgs e)
        {
         
        }
    }
}

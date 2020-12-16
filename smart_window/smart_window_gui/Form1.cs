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

namespace smart_window_gui
{
    
    public partial class Form1 : Form
    {
        private SerialPort _serialPort;

        private SerialPort _serial;
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
            }
            else
                MessageBox.Show("찌빨");

        }
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            this.Invoke(new EventHandler(MySerialReceived));
            //invoke
        }
        private void MySerialReceived(object s, EventArgs e)
        {
            string ReceiveData = _serialPort.ReadChar().ToString();
            if (ReceiveData == "2")
            {
                ssss.Text = "감지중";
                timer1.Start();
                timer1.Interval = 1000;
            }
            else if (ReceiveData == "1")
            {
                ssss.Text = "침임감지";
                string a = DateTime.Now.ToString("HH:mm:ss");
                a = a + " 침입";
                listBox1.Items.Add(a);

            }
            else if(ReceiveData == "3")
            {
                ssss.Text = "편안";
                timer1.Start();
                timer1.Interval = 1000;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
         
           
        }
    }
}

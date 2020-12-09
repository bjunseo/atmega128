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

namespace modeboll
{
    public partial class Form1 : Form
    {
        private SerialPort _serialPort;
        public Form1()
        {
            InitializeComponent();
            
            string[] Portnom = SerialPort.GetPortNames();

            foreach (string portnum in Portnom)
            {
                PortList.Items.Add(portnum);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void MySerialSend(object sender, EventArgs e)
        {
            string str = 'R' + textBox1.Text + 'B' + textBox2.Text + 'G' + textBox3.Text + '\n';
            _serialPort.Write(str);
        }
        private void serialPort_DataSend(object sender, SerialDataReceivedEventArgs e)
        {
            this.Invoke(new EventHandler(MySerialSend));
            //invoke
        }
        private void button2_Click(object sender, EventArgs e)
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
                _serialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataSend);

                _serialPort.Open();
            }
            else { }
        }
    }
}

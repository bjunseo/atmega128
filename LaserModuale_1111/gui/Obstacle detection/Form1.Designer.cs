﻿namespace Obstacle_detection
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.PortList = new System.Windows.Forms.ComboBox();
            this.Receive = new System.Windows.Forms.TextBox();
            this.status = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.ssss = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("휴먼모음T", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label1.ForeColor = System.Drawing.Color.Maroon;
            this.label1.Location = new System.Drawing.Point(81, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(397, 53);
            this.label1.TabIndex = 0;
            this.label1.Text = "침입 감지 프로그램";
            // 
            // PortList
            // 
            this.PortList.FormattingEnabled = true;
            this.PortList.Location = new System.Drawing.Point(90, 85);
            this.PortList.Name = "PortList";
            this.PortList.Size = new System.Drawing.Size(121, 20);
            this.PortList.TabIndex = 1;
            // 
            // Receive
            // 
            this.Receive.Location = new System.Drawing.Point(335, 85);
            this.Receive.Multiline = true;
            this.Receive.Name = "Receive";
            this.Receive.Size = new System.Drawing.Size(127, 20);
            this.Receive.TabIndex = 2;
            // 
            // status
            // 
            this.status.AutoSize = true;
            this.status.Location = new System.Drawing.Point(171, 117);
            this.status.Name = "status";
            this.status.Size = new System.Drawing.Size(0, 12);
            this.status.TabIndex = 3;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(90, 112);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "연결";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Connect_Click);
            // 
            // ssss
            // 
            this.ssss.AutoSize = true;
            this.ssss.Location = new System.Drawing.Point(238, 259);
            this.ssss.Name = "ssss";
            this.ssss.Size = new System.Drawing.Size(65, 12);
            this.ssss.TabIndex = 5;
            this.ssss.Text = "칩임감지중";
            this.ssss.Click += new System.EventHandler(this.label2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(547, 450);
            this.Controls.Add(this.ssss);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.status);
            this.Controls.Add(this.Receive);
            this.Controls.Add(this.PortList);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox PortList;
        private System.Windows.Forms.TextBox Receive;
        private System.Windows.Forms.Label status;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label ssss;
        private System.IO.Ports.SerialPort serialPort1;
    }
}


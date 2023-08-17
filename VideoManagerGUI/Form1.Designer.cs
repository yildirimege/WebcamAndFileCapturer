namespace VideoManagerGUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pb_frame = new System.Windows.Forms.PictureBox();
            this.btn_CaptureFromWebcam = new System.Windows.Forms.Button();
            this.btn_CaptureFromFile = new System.Windows.Forms.Button();
            this.btn_Stop = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pb_frame)).BeginInit();
            this.SuspendLayout();
            // 
            // pb_frame
            // 
            this.pb_frame.Location = new System.Drawing.Point(137, 12);
            this.pb_frame.Name = "pb_frame";
            this.pb_frame.Size = new System.Drawing.Size(503, 286);
            this.pb_frame.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pb_frame.TabIndex = 0;
            this.pb_frame.TabStop = false;
            // 
            // btn_CaptureFromWebcam
            // 
            this.btn_CaptureFromWebcam.AccessibleName = "btn_captureFromWebcam";
            this.btn_CaptureFromWebcam.Location = new System.Drawing.Point(137, 325);
            this.btn_CaptureFromWebcam.Name = "btn_CaptureFromWebcam";
            this.btn_CaptureFromWebcam.Size = new System.Drawing.Size(151, 52);
            this.btn_CaptureFromWebcam.TabIndex = 1;
            this.btn_CaptureFromWebcam.Text = "Capture from Webcam";
            this.btn_CaptureFromWebcam.UseVisualStyleBackColor = true;
            this.btn_CaptureFromWebcam.Click += new System.EventHandler(this.btn_CaptureFromWebcam_Click);
            // 
            // btn_CaptureFromFile
            // 
            this.btn_CaptureFromFile.AccessibleName = "btn_CaptureFromFile";
            this.btn_CaptureFromFile.Location = new System.Drawing.Point(314, 325);
            this.btn_CaptureFromFile.Name = "btn_CaptureFromFile";
            this.btn_CaptureFromFile.Size = new System.Drawing.Size(151, 52);
            this.btn_CaptureFromFile.TabIndex = 2;
            this.btn_CaptureFromFile.Text = "Capture from File";
            this.btn_CaptureFromFile.UseVisualStyleBackColor = true;
            this.btn_CaptureFromFile.Click += new System.EventHandler(this.btn_CaptureFromFile_Click);
            // 
            // btn_Stop
            // 
            this.btn_Stop.AccessibleName = "btn_Stop";
            this.btn_Stop.Location = new System.Drawing.Point(489, 325);
            this.btn_Stop.Name = "btn_Stop";
            this.btn_Stop.Size = new System.Drawing.Size(151, 52);
            this.btn_Stop.TabIndex = 3;
            this.btn_Stop.Text = "Stop";
            this.btn_Stop.UseVisualStyleBackColor = true;
            this.btn_Stop.Click += new System.EventHandler(this.btn_Stop_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 426);
            this.Controls.Add(this.btn_Stop);
            this.Controls.Add(this.btn_CaptureFromFile);
            this.Controls.Add(this.btn_CaptureFromWebcam);
            this.Controls.Add(this.pb_frame);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.pb_frame)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pb_frame;
        private System.Windows.Forms.Button btn_CaptureFromWebcam;
        private System.Windows.Forms.Button btn_CaptureFromFile;
        private System.Windows.Forms.Button btn_Stop;
    }
}


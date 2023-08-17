using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using VideoManagerWrapper;

namespace VideoManagerGUI
{
    /**
     * <summary> Main Form class </summary>
     */
    public partial class Form1 : Form
    {
        VideoManagerInterface videoManager = new VideoManagerInterface(); // Instance of the Managed VideoManagerInterface library.

        public Form1()
        {
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false; // Enabling cross thread calls.

            videoManager.InitEngine(); // Initializing Engine (Which will also create required objects in its constructor.)

            InitializeComponent(); // Initializes UI Components.

            videoManager.GetOwnerShipControl(pb_frame); // Giving ownership of Picture Box to VideoManager interface, to make it able to draw on the picturebox.
            videoManager.InitEnvents(); // Initializing Events and subscribing to event changes (Button clicks)
        }

        /**
         * <summary> Event when Start Capture From Webcam button is clicked. </summary>
         * 
         * <remarks> Sets Engine State to READ_FILE </remarks>
         */
        private void btn_CaptureFromWebcam_Click(object sender, EventArgs e)
        {
            videoManager.OpenCamera();
            videoManager.SetEngineState(EngineState.READ_WEBCAM);
        }

        /**
        * <summary> Event when Start Capture From File button is clicked. </summary>
        * 
        * <remarks> Sets Engine State to READ_FILE </remarks>
        */
        private void btn_CaptureFromFile_Click(object sender, EventArgs e)
        {
            String filePath = SelectFile();
            if(filePath.Length <= 0)
            {
                MessageBox.Show("No file selected.", "ERROR", MessageBoxButtons.OK);
                return; 
            }

            else
            {
                videoManager.OpenFile(filePath);
                videoManager.SetEngineState(EngineState.READ_FILE);
            }

        }

        /**
        * <summary> Event when Stop button is clicked. </summary>
        * 
        * <remarks> Sets Engine State to STOP </remarks>
        */
        private void btn_Stop_Click(object sender, EventArgs e)
        {
            if(videoManager.GetEngineState()  == EngineState.READ_WEBCAM) // If Engine were reading from webcam before stopping;
            {
                videoManager.CloseCamera(); // Unset the webcam device. (Close)
            }
            videoManager.SetEngineState(EngineState.STOP);
        }

        /**
        * <summary> Event when From is closed. </summary>
        * 
        * <remarks> Sets Engine State to RELEASE, which stops all threads to avoid crash on exit. (Otherwise threads will continue to run even after From is closed.) </remarks>
        */
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            videoManager.SetEngineState(EngineState.RELEASE);
        }

        private String SelectFile()
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = "c:\\";
                openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    return openFileDialog.FileName;
                }
                return "";
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace VideoManagerGUI
{
    internal static class Program
    {
        /**
         * <brief> Entry point of the application. </brief>
         * <brief> STA (Single Threaded Apartment) is required to interact with COM objects. </brief> 
         */
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1()); // Run the main GUI
        }
    }
}


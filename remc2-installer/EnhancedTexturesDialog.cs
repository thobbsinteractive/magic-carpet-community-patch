using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using WixSharp;
using WixSharp.UI.Forms;

namespace WixSharpSetup
{
    public partial class EnhancedDataDialog : ManagedForm, IManagedDialog
    {
        public EnhancedDataDialog()
        {
            //NOTE: If this assembly is compiled for v4.0.30319 runtime, it may not be compatible with the MSI hosted CLR.
            //The incompatibility is particularly possible for the Embedded UI scenarios.
            //The safest way to avoid the problem is to compile the assembly for v3.5 Target Framework.remc2_installer
            InitializeComponent();

            this.chkInstallTextures.Checked = true;
        }

        private bool ValidateGameDataLocation(string path)
        {
            bool valid = false;

            if (Directory.Exists(path))
            {
                string[] files = Directory.GetFiles(path);
                valid = true;
            }
            else
            {
                MessageBox.Show($"This {path} directory does not exist found", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            return valid;
        }

        void dialog_Load(object sender, EventArgs e)
        {
            banner.Image = Runtime.Session.GetResourceBitmap("WixUI_Bmp_Banner");
            Text = "[ProductName] Setup";

            //resolve all Control.Text cases with embedded MSI properties (e.g. 'ProductName') and *.wxl file entries
            base.Localize();
        }

        void back_Click(object sender, EventArgs e)
        {
            Shell.GoPrev();
        }

        void next_Click(object sender, EventArgs e)
        {
            Shell.GoNext();
        }

        void cancel_Click(object sender, EventArgs e)
        {
            Shell.Cancel();
        }
    }
}
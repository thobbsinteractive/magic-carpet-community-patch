using System;
using System.IO;
using System.Windows.Forms;
using WixSharp;
using WixSharp.UI.Forms;

namespace WixSharpSetup
{
    public partial class GameDataDialog : ManagedForm, IManagedDialog
    {
        public string Path = "";

        public GameDataDialog()
        {
            //NOTE: If this assembly is compiled for v4.0.30319 runtime, it may not be compatible with the MSI hosted CLR.
            //The incompatibility is particularly possible for the Embedded UI scenarios.
            //The safest way to avoid the problem is to compile the assembly for v3.5 Target Framework.remc2_installer
            InitializeComponent();

            this.cboInstallLocation.SelectedIndex = 0;
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
            if (ValidateGameDataLocation(this.txtPath.Text))
            {
                Path = this.txtPath.Text;
                Shell.GoNext();
            }
        }

        void cancel_Click(object sender, EventArgs e)
        {
            Shell.Cancel();
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            using (var fbd = new FolderBrowserDialog())
            {
                DialogResult result = fbd.ShowDialog();

                if (result == DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
                {
                    this.txtPath.Text = fbd.SelectedPath;
                }
            }
        }

        private void cboInstallLocation_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.cboInstallLocation.SelectedIndex == 0) { 
                this.txtPath.Text = "C:\\Program Files (x86)\\GOG Galaxy\\Games\\Magic Carpet 2";
            }
        }
    }
}
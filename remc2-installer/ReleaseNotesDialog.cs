using System;
using System.IO;
using System.Windows.Forms;
using WixSharp;
using WixSharp.UI.Forms;

namespace WixSharpSetup
{
	public partial class ReleaseNotesDialog : ManagedForm, IManagedDialog
    {
        public ReleaseNotesDialog()
        {
            //NOTE: If this assembly is compiled for v4.0.30319 runtime, it may not be compatible with the MSI hosted CLR.
            //The incompatibility is particularly possible for the Embedded UI scenarios.
            //The safest way to avoid the problem is to compile the assembly for v3.5 Target Framework.remc2_installer
            InitializeComponent();

            this.Shown += ReleaseNotesDialog_Shown;
            this.FormClosing += ReleaseNotesDialog_FormClosing;
        }

        private void ReleaseNotesDialog_Shown(object sender, EventArgs e)
        {
			this.lblHeaderText.Text = $"Release Notes for version {Runtime.ProductVersion}";

			string path = Path.Combine(Runtime.InstallDir, @"release_notes.rtf");

			if (System.IO.File.Exists(path))
			{
				this.rtbReleaseNotes.LoadFile(path);
			}
        }

        private void ReleaseNotesDialog_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Shown -= ReleaseNotesDialog_Shown;
        }

        private void dialog_Load(object sender, EventArgs e)
        {
            banner.Image = Runtime.Session.GetResourceBitmap("WixUI_Bmp_Banner");
            Text = "[ProductName] Setup";
            base.Localize();
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
			Shell.GoNext();
		}
	}
}
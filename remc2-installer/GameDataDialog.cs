using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using WixSharp;
using WixSharp.UI.Forms;

namespace WixSharpSetup
{
    public partial class GameDataDialog : ManagedForm, IManagedDialog
    {
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

                bool foundGameIns = false;

                if (this.cboInstallLocation.SelectedIndex == 0)
                {
                    foreach (string file in files)
                    {
                        if (file.PathGetFileName().Equals("game.ins", StringComparison.InvariantCultureIgnoreCase))
                        {
                            foundGameIns = true;
                            break;
                        }
                    }
                }
                else
                {
                    foundGameIns = true;
                }

                bool foundGameData = false;
                bool foundNetherw = false;
                bool foundCData = false;
                bool foundCLevels = false;
                bool foundSound = false;

                string[] directories = Directory.GetDirectories(path);

                foreach (string directory in directories)
                {
                    if (HasGameDir(directories))
                    {
                        string[] gameDirectories = Directory.GetDirectories(directory);
                        foundGameData = true;
                        foreach (string gameDirectory in gameDirectories)
                        {
                            if (HasNetherwDir(gameDirectories))
                            {
                                foundNetherw = true;
                                string[] netherwDirectories = Directory.GetDirectories(gameDirectory);
                                foundCData = HasCDataDir(netherwDirectories);
                                foundCLevels = HasCLevelsDir(netherwDirectories);
                                foundSound = HasSoundDir(netherwDirectories);
                                break;
                            }
                        }
                    }
                }

                valid = foundGameIns && foundGameData && foundNetherw && foundCData && foundCLevels && foundSound;

                if (!foundGameIns)
                    MessageBox.Show($"game.ins not found", "No game.ins", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                else if (!foundGameData)
                    MessageBox.Show($"GAME data directory not found", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                else if (!foundNetherw)
                    MessageBox.Show($"NETHERW data directory not found", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                else if (!foundCData)
                    MessageBox.Show($"CDATA directory not found", "No CDATA", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                else if (!foundCLevels)
                    MessageBox.Show($"CLEVELS directory not found", "No CLEVELS", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                else if (!foundSound)
                    MessageBox.Show($"SOUND directory not found", "No SOUND", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else
            {
                MessageBox.Show($"This {path} directory does not exist", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            return valid;
        }

        public bool MoveGameData(string gamePath)
        {
            string path = Runtime.InstallDir;

            try
            {
                if (Directory.Exists(Path.Combine(gamePath, "GAME")) && !Directory.Exists(Path.Combine(path, "GAME")))
                {
                    Utils.CopyDirectory(Path.Combine(gamePath, "GAME"), Path.Combine(path, "GAME"), true);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error moving game data files: {ex.Message}");
                return false;
            }

            return true;
        }

        public bool CopyExtractFolder(string gamePath)
        {
            string path = Runtime.InstallDir;

            try
            {
                if (Directory.Exists(Path.Combine(path, "Extract")))
                {
                    if (!Directory.Exists(Path.Combine(gamePath, "Extract")))
                    {
                        Utils.CopyDirectory(Path.Combine(path, "Extract"), Path.Combine(gamePath, "Extract"), true);
                    }
                }
                else
                {
                    MessageBox.Show($"Error copying extract folder not present in: {Path.Combine(path, "Extract")}");
                    return false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error copying extract folder: {ex.Message}");
                return false;
            }

            return true;
        }

        private bool ExtractCDFiles(string gamePath)
        {
            try
            {
                if (Directory.Exists(Path.Combine(gamePath, "CD_Files")))
                {
                    Directory.Delete(Path.Combine(gamePath, "CD_Files"), true);
                }

                if (Directory.Exists(Path.Combine(gamePath, "Extract")))
                {
                    ProcessStartInfo processStartInfo = new ProcessStartInfo(Path.Combine(gamePath, @"DOSBOX\dosbox.exe"), "-conf \"Extract\\dosboxExtract-GOG-CD.conf\" -c exit");
                    processStartInfo.WorkingDirectory = gamePath;
                    processStartInfo.UseShellExecute = false;
                    processStartInfo.ErrorDialog = true;
                    Process.Start(processStartInfo).Wait();
                }
            }
            catch (Exception ex)
            {
                if (MessageBox.Show($"Error Extracting CD Files: {ex.Message}\nWould you like to continue the Installation?", "CD File Extraction Error", MessageBoxButtons.YesNo, MessageBoxIcon.Error) == DialogResult.Yes)
                {
                    return true;
                }
                return false;
            }
            return true;
        }

        private bool MoveCDFiles(string gamePath)
        {
            try
            {
                if (Directory.Exists(Path.Combine(gamePath, "CD_Files")))
                {
                    Utils.CopyDirectory(Path.Combine(gamePath, "CD_Files"), Path.Combine(Runtime.InstallDir, "CD_Files"), true);
                }
            }
            catch (Exception ex)
            {
                if (MessageBox.Show($"Error Moving CD Files: {ex.Message}\nWould you like to continue the Installation?", "CD File Extraction Error", MessageBoxButtons.YesNo, MessageBoxIcon.Error) == DialogResult.Yes)
                {
                    return true;
                }
                return false;
            }
            return true;
        }

        private string GetDirectoryName(string path)
        {
            DirectoryInfo directoryInfo = new DirectoryInfo(path);
            return directoryInfo.Name;
        }

        private bool HasGameDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("game", StringComparison.InvariantCultureIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        private bool HasNetherwDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("netherw", StringComparison.InvariantCultureIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        private bool HasCDataDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("cdata", StringComparison.InvariantCultureIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        private bool HasCLevelsDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("clevels", StringComparison.InvariantCultureIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        private bool HasSoundDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("sound", StringComparison.InvariantCultureIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        void dialog_Load(object sender, EventArgs e)
        {
            banner.Image = Runtime.Session.GetResourceBitmap("WixUI_Bmp_Banner");
            Text = "[ProductName] Setup";
            this.txtPath.Text = @"C:\Program Files (x86)\GOG Galaxy\Games\Magic Carpet 2";
            //resolve all Control.Text cases with embedded MSI properties (e.g. 'ProductName') and *.wxl file entries
            base.Localize();
        }

        void btnNext_Click(object sender, EventArgs e)
        {
            btnBrowse.Enabled = false;
            btnNext.Enabled = false;
            btnCancel.Enabled = false;

            if (ValidateGameDataLocation(this.txtPath.Text) && 
                MoveGameData(this.txtPath.Text) &&
                CopyExtractFolder(this.txtPath.Text) &&
                ExtractCDFiles(this.txtPath.Text) && 
                MoveCDFiles(this.txtPath.Text))
            {
                Shell.GoNext();
            }

            btnBrowse.Enabled = true;
            btnNext.Enabled = true;
            btnCancel.Enabled = true;
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            using (var fbd = new FolderBrowserDialog())
            {
                fbd.SelectedPath = this.txtPath.Text;
                DialogResult result = fbd.ShowDialog();

                if (result == DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
                {
                    this.txtPath.Text = fbd.SelectedPath;
                }
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Shell.Exit();
        }
    }
}
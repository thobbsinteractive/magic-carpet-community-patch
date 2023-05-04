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

            this.Shown += GameDataDialog_Shown;
            this.FormClosing += GameDataDialog_FormClosing;
            this.cboInstallLocation.SelectedIndexChanged += CboInstallLocation_SelectedIndexChanged;
            this.cboInstallLocation.SelectedIndex = 0;
        }

        private string GetGoGInstructions()
        {
            string installPath = "INSTALL DIR";
            try
            {
                if (Runtime != null)
                    installPath = Runtime.InstallDir;
            }
            catch { };

            return $"The installer will now atempt to copy the NETHEW directory from: '{Path.Combine(this.txtPath.Text,"GAME")}' to: '{Path.Combine(installPath, "GAME")}'.\n" +
                $"It will then extract the CD Files to: '{Path.Combine(this.txtPath.Text, "CD_Files")}' and copy them to: '{Path.Combine(installPath, "CD_Files")}'.\n\n" +
                $"If this extract fails you can run '{Path.Combine(this.txtPath.Text, "Extract.bat")}' to extract the files and manually copy them to '{Path.Combine(installPath, "CD_Files")}'.\n\n" +
                "Click [Next] to continue";
        }

        private string GetDosInstructions()
        {
            string installPath = "INSTALL DIR";
            try
            {
                if (Runtime != null)
                    installPath = Runtime.InstallDir;
            }
            catch { };

            return $"You must install the DOS/Original version of Magic Carpet 2 first. The installer will now attempt to copy the contents of NETHEW directory from: '{this.txtPath.Text}' to: '{Path.Combine(installPath, @"GAME\NETHEW")}'.\n" +
                $"It will then copy the CD Files from: '{this.txtCDPath.Text}' and copy them to: '{Path.Combine(installPath, "CD_Files")}'.\n\n" +
                "Click [Next] to continue";
        }

        private bool ValidateGoGGameDataLocation(string path)
        {
            bool valid = false;

            if (Directory.Exists(path))
            {
                string[] files = Directory.GetFiles(path);

                bool foundGameIns = false;

                foreach (string file in files)
                {
                    if (file.PathGetFileName().Equals("game.ins", StringComparison.InvariantCultureIgnoreCase))
                    {
                        foundGameIns = true;
                        break;
                    }
                }

                bool foundGameData = false;
                bool foundNetherw = false;

                string[] directories = Directory.GetDirectories(path);

                if (HasGameDir(directories))
                {
                    foreach (string directory in directories)
                    {
                        if (IsGameDir(directory))
                        {
                            foundGameData = true;
                            string[] gameDirectories = Directory.GetDirectories(directory);
                            if (HasNetherwDir(gameDirectories))
                            {
                                foreach (string gameDirectory in gameDirectories)
                                {
                                    if (IsNetherwDir(gameDirectory))
                                    {
                                        foundNetherw = ValidateNetherwContent(gameDirectory);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }

                valid = foundGameIns && foundGameData && foundNetherw;

                if (!foundGameIns)
                    MessageBox.Show($"game.ins not found", "No game.ins", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                else if (!foundGameData)
                    MessageBox.Show($"GAME data directory not found", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else
            {
                MessageBox.Show($"This {path} directory does not exist", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            return valid;
        }

        private bool ValidateDosGameDataLocation(string path, string cdPath)
        {
            bool validNetherw = false;
            bool validCD = false;

            if (Directory.Exists(path))
            {
                validNetherw = ValidateNetherwContent(path);

                if (Directory.Exists(cdPath))
                {
                    validCD = ValidateCDContent(cdPath);
                }
                else
                {
                    MessageBox.Show($"This {cdPath} directory does not exist", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
            else
            {
                MessageBox.Show($"This {path} directory does not exist", "Invalid Directory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            return validNetherw && validCD;
        }

        public bool ValidateNetherwContent(string gameDirectory)
        {
            string[] netherwDirectories = Directory.GetDirectories(gameDirectory);
            bool foundCData = HasCDataDir(netherwDirectories);
            bool foundCLevels = HasCLevelsDir(netherwDirectories);
            bool foundSound = HasSoundDir(netherwDirectories);

            if (!foundCData)
                MessageBox.Show($"CDATA directory not found", "No CDATA", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else if (!foundCLevels)
                MessageBox.Show($"CLEVELS directory not found", "No CLEVELS", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else if (!foundSound)
                MessageBox.Show($"SOUND directory not found", "No SOUND", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

            return foundCData && foundCLevels && foundSound;
        }

        public bool ValidateCDContent(string cdDirectory)
        {
            string[] cdDirectories = Directory.GetDirectories(cdDirectory);
            bool foundData = HasDataDir(cdDirectories);
            bool foundIntro = HasIntroDir(cdDirectories);
            bool foundLanguage = HasLanguageDir(cdDirectories);
            bool foundLevels = HasLevelsDir(cdDirectories);
            bool foundSound = HasSoundDir(cdDirectories);

            if (!foundData)
                MessageBox.Show($"DATA directory not found", "No DATA", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else if (!foundIntro)
                MessageBox.Show($"Intro directory not found", "No INTRO", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else if (!foundLanguage)
                MessageBox.Show($"Language directory not found", "No LANGUAGE", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else if (!foundLevels)
                MessageBox.Show($"Levels directory not found", "No LEVELS", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else if (!foundSound)
                MessageBox.Show($"SOUND directory not found", "No SOUND", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

            return foundData && foundIntro && foundLanguage && foundLevels && foundSound;
        }

        public bool CopyExtractBatchFile(string gamePath)
        {
            if (System.IO.File.Exists(Path.Combine(Runtime.InstallDir, @"Extract.bat")))
            {
                System.IO.File.Copy(Path.Combine(Runtime.InstallDir, @"Extract.bat"), Path.Combine(gamePath, @"Extract.bat"), true);
            }
            return true;
        }

        public bool MoveGameData(string gamePath)
        {
            try
            {
                if (Directory.Exists(gamePath))
                {
                    Utils.CopyDirectory(gamePath, Path.Combine(Runtime.InstallDir, @"GAME"), true);
                }
                else
                {
                    if (MessageBox.Show($"Error finding directory {gamePath}\nWould you like to continue the Installation?", "CD File Extraction Error", MessageBoxButtons.YesNo, MessageBoxIcon.Error) == DialogResult.Yes)
                    {
                        return true;
                    }
                    return false;
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

        private bool MoveCDFiles(string cdPath)
        {
            try
            {
                if (Directory.Exists(cdPath))
                {
                    Utils.CopyDirectory(cdPath, Path.Combine(Runtime.InstallDir, "CD_Files"), true);
                }
                else
                {
                    if (MessageBox.Show($"Error finding directory {cdPath}\nWould you like to continue the Installation?", "CD File Extraction Error", MessageBoxButtons.YesNo, MessageBoxIcon.Error) == DialogResult.Yes)
                    {
                        return true;
                    }
                    return false;
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
                if (IsGameDir(directory))
                {
                    return true;
                }
            }
            return false;
        }

        private bool IsGameDir(string directory)
        {
            if (GetDirectoryName(directory).Equals("game", StringComparison.InvariantCultureIgnoreCase))
            {
                return true;
            }
            return false;
        }

        private bool HasNetherwDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (IsNetherwDir(directory))
                {
                    return true;
                }
            }
            return false;
        }

        private bool IsNetherwDir(string directory)
        {
            if (GetDirectoryName(directory).Equals("netherw", StringComparison.InvariantCultureIgnoreCase))
            {
                return true;
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

        private bool HasDataDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("data", StringComparison.InvariantCultureIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        private bool HasIntroDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("intro", StringComparison.InvariantCultureIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        private bool HasLanguageDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("language", StringComparison.InvariantCultureIgnoreCase))
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

        private bool HasLevelsDir(string[] directories)
        {
            foreach (string directory in directories)
            {
                if (GetDirectoryName(directory).Equals("levels", StringComparison.InvariantCultureIgnoreCase))
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

        private void SetGoGInstall()
        {
            this.txtPath.Text = @"C:\Program Files (x86)\GOG Galaxy\Games\Magic Carpet 2";
            this.txtCDPath.Text = @"";
            this.txtCDPath.Visible = false;
            this.lblCDData.Visible = false;
            this.btnBrowseCDFiles.Visible = false;
        }

        private void SetDosInstall()
        {
            this.txtPath.Text = @"C:\NETHERW";
            this.txtCDPath.Text = @"D:\";
            this.txtCDPath.Visible = true;
            this.lblCDData.Visible = true;
            this.btnBrowseCDFiles.Visible = true;
        }

        private string GetInstructions()
        {
            if (this.cboInstallLocation.SelectedIndex == 0)
            {
                return this.GetGoGInstructions();
            }
            else if (this.cboInstallLocation.SelectedIndex == 1)
            {
                return this.GetDosInstructions();
            }
            return string.Empty;
        }

        private void GameDataDialog_Shown(object sender, EventArgs e)
        {
            this.txtInstructions.Text = GetInstructions();
        }

        private void GameDataDialog_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Shown -= GameDataDialog_Shown;
        }

        private void dialog_Load(object sender, EventArgs e)
        {
            banner.Image = Runtime.Session.GetResourceBitmap("WixUI_Bmp_Banner");
            Text = "[ProductName] Setup";
            base.Localize();
        }

        private void CboInstallLocation_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.cboInstallLocation.SelectedIndex == 0)
            {
                SetGoGInstall();
            }
            else if (this.cboInstallLocation.SelectedIndex == 1)
            {
                SetDosInstall();
            }
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            btnBrowse.Enabled = false;
            btnBrowseCDFiles.Enabled = false;
            btnNext.Enabled = false;
            btnCancel.Enabled = false;
            txtPath.Enabled = false;
            txtCDPath.Enabled = false;

            if (this.cboInstallLocation.SelectedIndex == 0)
            {
                //GOG
                if (ValidateGoGGameDataLocation(this.txtPath.Text) &&
                CopyExtractBatchFile(this.txtPath.Text) &&
                MoveGameData(Path.Combine(this.txtPath.Text, "GAME")) &&
                CopyExtractFolder(this.txtPath.Text) &&
                ExtractCDFiles(this.txtPath.Text) &&
                MoveCDFiles(Path.Combine(this.txtPath.Text, "CD_Files")))
                {
                    Shell.GoNext();
                }
            }
            else if (this.cboInstallLocation.SelectedIndex == 1)
            {
                //DOS
                if (ValidateDosGameDataLocation(this.txtPath.Text, this.txtCDPath.Text) &&
                MoveGameData(Path.Combine(this.txtPath.Text, "NETHEW")) &&
                MoveCDFiles(this.txtCDPath.Text))
                {
                    Shell.GoNext();
                }
            }

            btnBrowse.Enabled = true;
            btnBrowseCDFiles.Enabled = true;
            btnNext.Enabled = true;
            btnCancel.Enabled = true;
            txtPath.Enabled = true;
            txtCDPath.Enabled = true;
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

        private void btnBrowseCDFiles_Click(object sender, EventArgs e)
        {
            using (var fbd = new FolderBrowserDialog())
            {
                fbd.SelectedPath = this.txtCDPath.Text;
                DialogResult result = fbd.ShowDialog();

                if (result == DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
                {
                    this.txtCDPath.Text = fbd.SelectedPath;
                }
            }
        }

        private void Path_TextChanged(object sender, EventArgs e)
        {
            this.txtInstructions.Text = GetInstructions();
        }
    }
}
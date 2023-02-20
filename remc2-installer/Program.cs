using System;
using System.Windows.Forms;
using WixSharp;
using WixSharp.Forms;
using WixSharpSetup;

namespace remc2_installer
{
    internal class Program
    {
        static void Main()
        {
            var project = new ManagedProject("Magic Carpet 2 HD",
                             new Dir(@"%ProgramFiles%\Remc\Magic Carpet 2 HD",
                                 new File(@"..\Release\remc2.exe"),
                                 new File(@"..\Release\config.ini"),
                                 new File(@"..\Release\SDL2.dll"),
                                 new Dir(@"font",
                                    new Files(@"..\Release\font\*.*")),
                                 new Dir(@"music-ogg",
                                    new Files(@"..\Release\music-ogg\*.*")
                             //new Property("INSTALL_TYPE", "x64"),
                             //new ManagedAction(CustomActions.ExtractData)
                             )));

            project.GUID = new Guid("d945f1c4-cbe4-445c-9674-07de64692857");

            //project.ManagedUI = ManagedUI.Empty;    //no standard UI dialogs
            //project.ManagedUI = ManagedUI.Default;  //all standard UI dialogs

            //custom set of standard UI dialogs
            project.ManagedUI = new ManagedUI();
            project.ManagedUI.InstallDialogs.Add(Dialogs.Welcome)
                                            .Add(Dialogs.Licence)
                                            .Add<InstallTypeDialog>()
                                            .Add<GameDataDialog>()
                                            .Add<EnhancedDataDialog>()
                                            .Add(Dialogs.Progress)
                                            .Add(Dialogs.Exit);

            project.ManagedUI.ModifyDialogs.Add(Dialogs.MaintenanceType)
                                           .Add(Dialogs.Features)
                                           .Add(Dialogs.Progress)
                                           .Add(Dialogs.Exit);

            project.Load += Msi_Load;
            project.BeforeInstall += Msi_BeforeInstall;
            project.AfterInstall += Msi_AfterInstall;

            //project.SourceBaseDir = "<input dir path>";
            //project.OutDir = "<output dir path>";

            ValidateAssemblyCompatibility();

            project.BuildMsi();
        }

        static void Msi_Load(SetupEventArgs e)
        {
            if (!e.IsUninstalling)
                MessageBox.Show(e.ToString(), "Load");
        }

        static void Msi_BeforeInstall(SetupEventArgs e)
        {
            if (!e.IsUninstalling)
                MessageBox.Show(e.ToString(), "BeforeInstall");
        }

        static void Msi_AfterInstall(SetupEventArgs e)
        {
            if (!e.IsUISupressed && !e.IsUninstalling)
                MessageBox.Show(e.ToString(), "AfterExecute");
        }

        static void ValidateAssemblyCompatibility()
        {
            var assembly = System.Reflection.Assembly.GetExecutingAssembly();

            if (!assembly.ImageRuntimeVersion.StartsWith("v2."))
            {
                Console.WriteLine("Warning: assembly '{0}' is compiled for {1} runtime, which may not be compatible with the CLR version hosted by MSI. " +
                                  "The incompatibility is particularly possible for the EmbeddedUI scenarios. " +
                                   "The safest way to solve the problem is to compile the assembly for v3.5 Target Framework.",
                                   assembly.GetName().Name, assembly.ImageRuntimeVersion);
            }
        }
    }
}
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
#if WIN64
                                 new File(@"..\x64\Release\remc2.exe")      
#else
                                 new File(@"..\Release\remc2.exe")
#endif
                                 {
                                    Permissions = new[] {
                                        new FilePermission("Everyone", GenericPermission.All) { Execute = true },
                                        new FilePermission("Users", GenericPermission.All) { Execute = true },
                                        new FilePermission("AuthenticatedUser", GenericPermission.All) { Execute = true },
                                        new FilePermission("CREATOR OWNER", GenericPermission.All)  { Execute = true },
                                        new FilePermission("ALL APPLICATION PACKAGES", GenericPermission.All)  { Execute = true }
                                    }
                                 },
                                 new File(@"..\Release\config.ini")
                                 {
                                     Permissions = new[] {
                                    new FilePermission("Everyone", GenericPermission.All) { ChangePermission = true },
                                    new FilePermission("Users", GenericPermission.All) { ChangePermission = true },
                                    new FilePermission("AuthenticatedUser", GenericPermission.All) { ChangePermission = true },
                                    new FilePermission("CREATOR OWNER", GenericPermission.All)  { ChangePermission = true },
                                    new FilePermission("ALL APPLICATION PACKAGES", GenericPermission.All)  { ChangePermission = true }
                                    }
                                 },
                                 new File(@"..\Release\SDL2.dll"),
                                 new Dir(@"font",
                                    new Files(@"..\Release\font\*.*")),
                                 new Dir(@"biggraphics",
                                    new Files(@"..\enhancedassets\biggraphics\*.*")),
                                 new Dir(@"music-ogg",
                                    new Files(@"..\enhancedassets\music-ogg\*.*"))),

                            new Property("GAMEDATAPATH", @"C:\Program Files (x86)\GOG Galaxy\Games\Magic Carpet 2"),
                            new Property("HIGHTEX", "y"),
                            new ManagedAction(CustomActions.ExtractData, Return.check, When.After, Step.InstallFiles, Condition.NOT_Installed));

#if WIN64
            project.Platform = Platform.x64;
#endif
            project.GUID = new Guid("d945f1c4-cbe4-445c-9674-07de64692857");

            //project.ManagedUI = ManagedUI.Empty;    //no standard UI dialogs
            //project.ManagedUI = ManagedUI.Default;  //all standard UI dialogs

            //custom set of standard UI dialogs
            project.ManagedUI = new ManagedUI();
            project.ManagedUI.InstallDialogs.Add(Dialogs.Welcome)
                                            .Add(Dialogs.Licence)
                                            .Add<GameDataDialog>()
                                            .Add<EnhancedDataDialog>()
                                            .Add(Dialogs.InstallDir)
                                            .Add(Dialogs.Progress)
                                            .Add(Dialogs.Exit);

            project.ManagedUI.ModifyDialogs.Add(Dialogs.MaintenanceType)
                                           .Add<EnhancedDataDialog>()
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
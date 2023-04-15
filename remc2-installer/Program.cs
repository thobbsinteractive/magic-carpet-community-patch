using System;
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
                             new Dir(@"%ProgramFiles%\ReMC\Magic Carpet 2 HD",
                                 new DirPermission("Everyone", GenericPermission.All),
#if WIN64
                                 new WixSharp.File(@"..\x64\Release\remc2.exe", new FileShortcut("Magic Carpet 2 HD", @"%ProgramMenu%\ReMC\Magic Carpet 2 HD"))
                                 {
                                     IconFile = "Resources/app.ico"
                                 })
#else
                                 new WixSharp.File(@"..\Release\remc2.exe", new FileShortcut("Magic Carpet 2 HD", @"%ProgramMenu%\ReMC\Magic Carpet 2 HD")
                                 {
                                     IconFile = "Resources/app.ico"
                                 })
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
                                 new WixSharp.File(@"..\Release\config.ini")
                                 {
                                     Permissions = new[] {
                                        new FilePermission("Everyone", GenericPermission.All) { ChangePermission = true },
                                        new FilePermission("Users", GenericPermission.All) { ChangePermission = true },
                                        new FilePermission("AuthenticatedUser", GenericPermission.All) { ChangePermission = true },
                                        new FilePermission("CREATOR OWNER", GenericPermission.All)  { ChangePermission = true },
                                        new FilePermission("ALL APPLICATION PACKAGES", GenericPermission.All)  { ChangePermission = true }
                                    }
                                 },
#if WIN64
                                 new WixSharp.File(@"..\x64\Release\SDL2.dll"),
#else
                                 new WixSharp.File(@"..\Release\SDL2.dll"),
#endif
                                 new Dir(@"font",
                                    new Files(@"..\Release\font\*.*")),
                                 new Dir(@"biggraphics",
                                    new Files(@"..\enhancedassets\biggraphics\*.*")
                                    {
                                        ComponentCondition = "HIGHTEX=\"yes\""
                                    }),
                                 new Dir(@"music-ogg",
                                    new Files(@"..\enhancedassets\music-ogg\*.*")),
                                 new Dir(@"Extract",
                                    new Files(@"Extract\*.*"))),

                            new Property("GAMEDATAPATH", @"C:\Program Files (x86)\GOG Galaxy\Games\Magic Carpet 2"),
                            new Property("HIGHTEX", "yes"),
                            new ManagedAction(CustomActions.MoveGameData, Return.check, When.After, Step.InstallFinalize, Condition.NOT_Installed),
                            //new ManagedAction(CustomActions.CopyExtractFolder, Return.check, When.After, new Step("MoveGameData"), Condition.NOT_Installed),
                            //new ManagedAction(CustomActions.ExtractCDFiles, Return.check, When.After, new Step("CopyExtractFolder"), Condition.NOT_Installed),
                            //new ManagedAction(CustomActions.MoveCDFiles, Return.check, When.After, new Step("ExtractCDFiles"), Condition.NOT_Installed),
                            new ManagedAction(CustomActions.SetEnhancedTextures, Return.check, When.After, Step.InstallFinalize, Condition.NOT_Installed));

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

            project.ControlPanelInfo.ProductIcon = "Resources/app.ico";
            project.LicenceFile = "Resources/MagicCarpet2HD.licence.rtf";
            project.BackgroundImage = "Resources/MagicCarpet2HD.dialog_bmp.png";
            project.BannerImage = "Resources/MagicCarpet2HD.dialog_banner.png";

            //project.SourceBaseDir = "<input dir path>";
            //project.OutDir = "<output dir path>";

            project.InstallPrivileges = InstallPrivileges.elevated;

            ValidateAssemblyCompatibility();

            project.BuildMsi();
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
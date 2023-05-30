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

#if WIN64
            var project = new ManagedProject("Magic Carpet 2 HD x64",
#else
            var project = new ManagedProject("Magic Carpet 2 HD x86",
#endif
                             new Dir(@"%ProgramFiles%\ReMC\Magic Carpet 2 HD",
                                 new DirPermission("Everyone", GenericPermission.All),
#if WIN64
                                 new File(@"..\x64\Release\remc2.exe", new FileShortcut("Magic Carpet 2 HD", @"%ProgramMenu%\ReMC\Magic Carpet 2 HD")
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
#if WIN64
								 new File(@"..\x64\Release\remc2-editor.exe", new FileShortcut("Editor", @"%ProgramMenu%\ReMC\Magic Carpet 2 HD")
								 {
									 IconFile = "Resources/app.ico"
								 })
#else
                                 new WixSharp.File(@"..\Release\remc2-editor.exe", new FileShortcut("Editor", @"%ProgramMenu%\ReMC\Magic Carpet 2 HD")
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
#if WIN64
								 new File(@"..\x64\Release\libfreetype-6.dll"),
								 new File(@"..\x64\Release\SDL2.dll"),
								 new File(@"..\x64\Release\SDL2_image.dll"),
								 new File(@"..\x64\Release\SDL2_ttf.dll"),
								 new File(@"..\x64\Release\zlib1.dll"),
#else
                                 new File(@"..\Release\libfreetype-6.dll"),
								 new File(@"..\Release\SDL2.dll"),
								 new File(@"..\Release\SDL2_image.dll"),
								 new File(@"..\Release\SDL2_ttf.dll"),
								 new File(@"..\Release\zlib1.dll"),
#endif
								 new File(@"Extract.bat"),
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
                                    new File(@"Extract\dosboxExtract-GOG-CD.conf"),
                                    new File(@"Extract\XXCOPY16.EXE"))),
                            new Property("HIGHTEX", "yes"),
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
                                            .Add(Dialogs.InstallDir)
                                            .Add<EnhancedDataDialog>()
                                            .Add(Dialogs.Progress)
                                            .Add<GameDataDialog>()
                                            .Add(Dialogs.Exit);

            project.ManagedUI.ModifyDialogs.Add(Dialogs.MaintenanceType)
                                           .Add<EnhancedDataDialog>()
                                           .Add(Dialogs.Progress)
                                           .Add(Dialogs.Exit);

            project.ControlPanelInfo.ProductIcon = @"Resources\app.ico";
            project.ControlPanelInfo.Comments = "Enhanced Edition of Magic Carpet 2";
            project.ControlPanelInfo.UrlInfoAbout = "https://github.com/thobbsinteractive/magic-carpet-2-hd";
            project.ControlPanelInfo.Contact = "Magic Carpet 2 HD";
            project.ControlPanelInfo.Manufacturer = "Magic Carpet 2 HD";

            project.LicenceFile = @"Resources\MagicCarpet2HD.licence.rtf";
            project.BackgroundImage = @"Resources\MagicCarpet2HD.dialog_bmp.png";
            project.BannerImage = @"Resources\MagicCarpet2HD.dialog_banner.png";
            project.InstallPrivileges = InstallPrivileges.elevated;
            ValidateAssemblyCompatibility();
            project.AfterInstall += OnAfterInstall;
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

        public static void OnAfterInstall(SetupEventArgs e)
        {
            if (e.IsUninstalling)
            {
                e.InstallDir.DeleteIfExists();
            }
        }
    }
}
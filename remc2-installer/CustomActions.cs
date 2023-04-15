using Microsoft.Deployment.WindowsInstaller;
using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using WixSharp;

public class CustomActions
{
    [CustomAction]
    public static ActionResult SetEnhancedTextures(Session session)
    {
        bool enhancedTextures = false;
            
        if (!string.IsNullOrWhiteSpace(session["HIGHTEX"]) && session["HIGHTEX"].Equals("yes", System.StringComparison.InvariantCultureIgnoreCase))
        {
            enhancedTextures = true;
        }

        if (enhancedTextures)
        {
            session.Log($"Installing Enhanced Textures...");

            string path = session["INSTALLDIR"];

            string configFilePath = Path.Combine(path, "config.ini");

            session.Log($"Setting config.ini file: {configFilePath}");
            if (System.IO.File.Exists(configFilePath))
            {
                session.Log($"Updating Ini File: {configFilePath}");
                IniFile iniFile = new IniFile();
                iniFile.Load(configFilePath);
                iniFile["graphics"]["useEnhancedGraphics"] = "true ; if set to true, bigGraphicsFolder must be set as well";
                iniFile.Save(configFilePath);
                return ActionResult.Success;
            }
            else
            {
                return ActionResult.Failure;
            }
        }
        else
        {
            session.Log($"User selected to not install Enchanced Textures");
            return ActionResult.Success;
        }
    }

    [CustomAction]
    public static ActionResult CopyExtractFolder(Session session)
    {
        session.Log("CopyExtractFolder");

        string path = session["INSTALLDIR"];
        string gamePath = session["GAMEDATAPATH"];
        session.Log($"Game Data Path: {gamePath}");

        try
        {
            if (Directory.Exists(Path.Combine(path, "Extract")))
            {
                if (!Directory.Exists(Path.Combine(gamePath, "Extract")))
                {
                    CopyDirectory(Path.Combine(path, "Extract"), Path.Combine(gamePath, "Extract"), true);
                    session.Log($"Copied extract tools to: {Path.Combine(gamePath, "Extract")}");
                }
                else
                {
                    session.Log($"Extract tools already copied");
                }
            }
            else
            {
                session.Log($"Error copying extract folder not present in: {Path.Combine(path, "Extract")}");
                return ActionResult.Failure;
            }
        }
        catch (Exception ex)
        {
            session.Log($"Error copying extract folder: {ex.Message}");
            return ActionResult.Failure;
        }

        return ActionResult.Success;
    }

    [CustomAction]
    public static ActionResult MoveGameData(Session session)
    {
        session.Log("MoveGameData");

        string path = session["INSTALLDIR"];
        string gamePath = session["GAMEDATAPATH"];
        session.Log($"Game Data Path: {gamePath}");

        try
        {
            if (Directory.Exists(Path.Combine(gamePath, "GAME")) && !Directory.Exists(Path.Combine(path, "GAME")))
            {
                CopyDirectory(Path.Combine(gamePath, "GAME"), Path.Combine(path, "GAME"), true);
                session.Log($"Copied 'GAME' directory from: {Path.Combine(gamePath, "GAME")} to: {Path.Combine(path, "GAME")}");
            }
            else
            {
                session.Log($"'GAME' directory already copied");
            }
        }
        catch (Exception ex)
        {
            session.Log($"Error moving game data files: {ex.Message}");
            return ActionResult.Failure;
        }

        return ActionResult.Success;
    }

    public static ActionResult ExtractCDFiles(Session session)
    {
        session.Log("ExtractCDData");
        string gamePath = session["GAMEDATAPATH"];
        session.Log($"Game Data Path: {gamePath}");

        //string gamePath = "C:\\Program Files (x86)\\GOG Galaxy\\Games\\Magic Carpet 2";//session["GAMEDATAPATH"];

        try
        {
            if (Directory.Exists(Path.Combine(gamePath, "CD_Files")))
            {
                Directory.Delete(Path.Combine(gamePath, "CD_Files"), true);
            }
            session.Log($"Calling: {Path.Combine(gamePath, @"..\DOSBOX\dosbox.exe")}");
            ProcessStartInfo processStartInfo = new ProcessStartInfo(Path.Combine(gamePath, @"DOSBOX\dosbox.exe"), "-conf \"Extract\\dosboxExtract-GOG-CD.conf\" -c exit");
            processStartInfo.WorkingDirectory = gamePath;
            processStartInfo.UseShellExecute = false;
            processStartInfo.ErrorDialog = true;
            Process.Start(processStartInfo).Wait();
            session.Log($"Extracted CD_Files");
        }
        catch (Exception ex)
        {
            session.Log($"Error Extracting CD data: {ex.Message}");
            return ActionResult.Failure;
        }

        return ActionResult.Success;
    }

    public static ActionResult MoveCDFiles(Session session)
    {
        session.Log("MoveCDFiles");

        string path = session["INSTALLDIR"];
        string gamePath = session["GAMEDATAPATH"];
        session.Log($"Game Data Path: {gamePath}");

        try
        {
            if (Directory.Exists(Path.Combine(gamePath, "CD_Files")) && !Directory.Exists(Path.Combine(path, "CD_Files")))
            {
                CopyDirectory(Path.Combine(gamePath, "CD_Files"), Path.Combine(path, "CD_Files"), true);
                session.Log($"Copied 'CD_Files' directory from: {Path.Combine(gamePath, "CD_Files")} to: {Path.Combine(path, "CD_Files")}");
            }
            else
            {
                session.Log($"'CD_Files' directory already copied");
            }
        }
        catch (Exception ex)
        {
            session.Log($"Error moving CD_Files: {ex.Message}");
            return ActionResult.Failure;
        }

        return ActionResult.Success;
    }

    private static void CopyDirectory(string sourceDir, string destinationDir, bool recursive)
    {
        // Get information about the source directory
        var dir = new DirectoryInfo(sourceDir);

        // Check if the source directory exists
        if (!dir.Exists)
            throw new DirectoryNotFoundException($"Source directory not found: {dir.FullName}");

        // Cache directories before we start copying
        DirectoryInfo[] dirs = dir.GetDirectories();

        // Create the destination directory
        Directory.CreateDirectory(destinationDir);

        // Get the files in the source directory and copy to the destination directory
        foreach (FileInfo file in dir.GetFiles())
        {
            string targetFilePath = Path.Combine(destinationDir, file.Name);
            file.CopyTo(targetFilePath);
        }

        // If recursive and copying subdirectories, recursively call this method
        if (recursive)
        {
            foreach (DirectoryInfo subDir in dirs)
            {
                string newDestinationDir = Path.Combine(destinationDir, subDir.Name);
                CopyDirectory(subDir.FullName, newDestinationDir, true);
            }
        }
    }
}


using Microsoft.Deployment.WindowsInstaller;
using System.IO;
using System.Windows.Forms;

public class CustomActions
{
    [CustomAction]
    public static ActionResult SetEnhancedTextures(Session session)
    {
        bool enhancedTextures = false;
            
        if (!string.IsNullOrWhiteSpace(session["HIGHTEX"]) && session["HIGHTEX"].Equals("y", System.StringComparison.InvariantCultureIgnoreCase))
        {
            enhancedTextures = true;
        }

        if (enhancedTextures)
        {
            session.Log($"Setting Enhanced Textures to: {enhancedTextures}");

            string path = session["INSTALLDIR"];

            string configFilePath = Path.Combine(path, "config.ini");

            session.Log($"Setting config.ini file: {configFilePath}");

            if (File.Exists(configFilePath))
            {
                session.Log($"Setting Enhanced Textures to: {path}");
                Ini iniFile = new Ini(Path.Combine(path, "config.ini"));
                iniFile.WriteValue("useEnhancedGraphics", "graphics", enhancedTextures.ToString());
                iniFile.Save();
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
    public static ActionResult ExtractData(Session session)
    {
        session.Log("Begin Extract Data");

        string path = session["GAMEDATAPATH"];
        session.Log($"Game Data Path: {path}");

        return ActionResult.Success;
    }

}


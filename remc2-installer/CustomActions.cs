using Microsoft.Deployment.WindowsInstaller;
using System.IO;
using System.Windows.Forms;

public class CustomActions
{
    [CustomAction]
    public static ActionResult SetEnhancedTextures(Session session)
    {
        bool enhancedTextures = false;
            
        if (!string.IsNullOrWhiteSpace(session["HIGHTEX"]) && string.Compare(session["HIGHTEX"], "y", System.StringComparison.InvariantCultureIgnoreCase) == 0)
        {
            enhancedTextures = true;
        }

        session.Log($"Setting Enhanced Textures to: {enhancedTextures}");

        string path = session["INSTALLDIR"];

        if (Directory.Exists(path) && System.IO.File.Exists(Path.Combine(path, "config.ini")))
        {
            Ini iniFile = new Ini(Path.Combine(path, "config.ini"));
            iniFile.Save();
            return ActionResult.Success;
        }
        else
        {
            return ActionResult.Failure;
        }
    }

    [CustomAction]
    public static ActionResult ExtractData(Session session)
    {
        session.Log("Begin Extract Data");

        string path = session["GAMEDATAPATH"];
        MessageBox.Show(path);
        session.Log(path);

        return ActionResult.Success;
    }

}


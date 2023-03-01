using Microsoft.Deployment.WindowsInstaller;
using System.Windows.Forms;

public class CustomActions
{
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


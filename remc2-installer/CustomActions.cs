using Microsoft.Deployment.WindowsInstaller;

public class CustomActions
{
    [CustomAction]
    public static ActionResult ExtractData(Session session)
    {
        session.Log("Begin Extract Data");



        return ActionResult.Success;
    }

}

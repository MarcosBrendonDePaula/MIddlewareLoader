using System.Collections.Generic;
using MiddlewareLoader;
using MiddlewareLoader.Async;


namespace Teste
{
    class SendModule : MiddlewareModule
    {
        public override void Main(Dictionary<string, object> args)
        {
            base.Main(args);
            MiddlewareLoader.Buffer bf = (MiddlewareLoader.Buffer)args["Buffer"];
            if (args["Client"].GetType() == typeof(AsyncClientTcp))
            {
                var cli = (AsyncClientTcp)args["Client"];
                bf.SetString(bf + " " + "Aloha");
            }
            else
            {
                ServerClientTcp client = (ServerClientTcp)args["Client"];
                bf.SetString(bf + " " + "Aloha");
            }
           
            
        }
    }
}

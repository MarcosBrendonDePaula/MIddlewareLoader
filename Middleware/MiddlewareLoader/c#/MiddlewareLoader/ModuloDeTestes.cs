using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MiddlewareLoader.Async;

namespace MiddlewareLoader
{
    class ModuloDeTestes : MiddlewareModule
    {
        public override void Main(Dictionary<string, object> args)
        {
            ServerClientTcp cli = (ServerClientTcp)args["Client"];
            cli.SendBuffer(new Buffer("Bem vindo"));
        }
    }
}

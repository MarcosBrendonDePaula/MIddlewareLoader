using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MiddlewareLoader;
using MiddlewareLoader.Async;

namespace Teste
{
    class ModuloDeTestes : MiddlewareModule
    {
        public override void Main(Dictionary<string, object> args)
        {
            ServerClientTcp cli = (ServerClientTcp)args["Client"];
            cli.SendBuffer(new MiddlewareLoader.Buffer("Bem vindo"));
        }
    }
}

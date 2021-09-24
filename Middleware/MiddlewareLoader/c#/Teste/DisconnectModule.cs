using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MiddlewareLoader;
using MiddlewareLoader.Async;

namespace Teste
{
    class DisconnectModule : MiddlewareModule
    {
        public override void Main(Dictionary<string, object> args)
        {
            if (args["Client"].GetType() == typeof(AsyncClientTcp))
            {
                Console.WriteLine("O cliente foi desconectado!");
            }
            else
            {
                var client = (ServerClientTcp)args["Client"];
                Console.WriteLine("O cliente:" + client.Id + " foi desconectado!");
            }
            base.Main(args);
        }
    }
}

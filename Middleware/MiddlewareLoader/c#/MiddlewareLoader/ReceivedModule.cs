using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MiddlewareLoader.Async;

namespace MiddlewareLoader
{
    class ReceivedModule : MiddlewareModule
    {
        public override void Main(Dictionary<string, object> args)
        {
            Buffer bf = (Buffer) args["Buffer"];
            ServerClientTcp client = (ServerClientTcp) args["Client"];
            Console.WriteLine("Recebi:" + bf + " de "+client.Id);
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MiddlewareLoader;
using MiddlewareLoader.Async;

namespace Teste
{
    class ReceivedModule : MiddlewareModule 
    {
        public override void Main(Dictionary<string, object> args)
        {
            var bf     = (MiddlewareLoader.Buffer) args["Buffer"];
            var client = (ServerClientTcp) args["Client"];
            bf.SetString(bf + " Eu modifiquei o texto");
            Console.WriteLine("Recebi:" + bf + " de "+client.Id);
            
        }
    }
}

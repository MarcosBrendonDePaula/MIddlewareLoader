using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MiddlewareLoader;
using MiddlewareLoader.Async;

namespace Teste
{
    class Program
    {
        static void Main(string[] args)
        {
            var m1 = new ModuloDeTestes();
            var Rm = new ReceivedModule();
            var Sm = new SendModule();
            var Dm = new DisconnectModule();

            var  s = new ServerTcp();
            s.Use(m1,EventType.Connected);
            s.Use(Rm, EventType.Received);
            s.Use(Sm,EventType.Sended);
            s.Use(Dm,EventType.Disconnected);

            s.Start(21,1500);
            s.TaskAcceptLoop.Wait();
        }
    }
}

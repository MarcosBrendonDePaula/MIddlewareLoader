using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiddlewareLoader
{
    namespace Async
    {
        class ServerTcp : Socket
        {
            public int MaxBuffer;
            public int Port;
            public Task TaskAcceptLoop;

            public Dictionary<int, ServerClientTcp> Clients;
            public List<List<MiddlewareModule>> Events;

            private int IdCounter { get; set; }


            public ServerTcp()
            {
                IdCounter = 0;
                Clients = new Dictionary<int, ServerClientTcp>();
                Events = new List<List<MiddlewareModule>>() {
                    new List<MiddlewareModule>(),
                    new List<MiddlewareModule>(),
                    new List<MiddlewareModule>(),
                    new List<MiddlewareModule>(),
                    new List<MiddlewareModule>(),
                    new List<MiddlewareModule>(),
                    new List<MiddlewareModule>(),
                };
            }

            public void Start(int port = 25565, int maxBuffer = 1500)
            {
                this.MaxBuffer = maxBuffer;
                this.Port      = port;
                this.Listen("127.0.0.1", port, 10);
                this.TaskAcceptLoop = Task.Run(() =>
                {
                    AcceptLoop(this);
                });
            }

            public void Use(MiddlewareModule module, EventType ev)
            {
                this.Events[(int)ev].Add(module);
                this.Events[(int)ev].Sort();
            }

            private void AcceptLoop(ServerTcp Server)
            {
                while (Server.Listening)
                {
                    ServerClientTcp client = new ServerClientTcp(Server.IdCounter, this)
                    {
                        Socket_ = Server.AcceptConnection(), Events = Server.Events
                    };

                    Dictionary<string, Object> args = new Dictionary<string, object>();

                    ErrorMesage Err = new ErrorMesage {code = (int) EventType.Connected, description = "OK"};

                    args.Add("Server", this);
                    args.Add("Client", client);
                    args.Add("ErrorMessage", Err);

                    foreach (var module in Events[(int)EventType.Connected])
                    {
                        Console.WriteLine(module.GetType().Name);
                        module.Main(args);
                    }

                    Clients.Add(Server.IdCounter,client);
                    client.InitCommunication();
                    Server.IdCounter      += 1;
                    
                }

            }
        }
    }
}

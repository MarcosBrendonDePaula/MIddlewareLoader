using System;
using System.Collections.Generic;
using MiddlewareLoader;
using MiddlewareLoader.Async;

namespace Teste
{
    class ConnectModule : MiddlewareModule
    {
        public override void Main(Dictionary<string, object> args)
        {
            var err = (ErrorMesage) args["ErrorMessage"];
            
            if (args["Client"].GetType() == typeof(AsyncClientTcp))
            {
                var cli = (AsyncClientTcp)args["Client"];
                if (err.code==-1)
                {
                    Console.WriteLine("Erro ao conectar, tentando nova conexão");
                    Console.WriteLine(cli.Ip+" "+cli.Port);

                    cli.Connect(cli.Ip, cli.Port);
                }
                
                cli.SendBuffer(new MiddlewareLoader.Buffer("Me conectei em voce monstro"));
            }
            else
            {
                ServerClientTcp cli = (ServerClientTcp)args["Client"];
                cli.SendBuffer(new MiddlewareLoader.Buffer("Bem vindo"));
            }
            
        }
    }
}

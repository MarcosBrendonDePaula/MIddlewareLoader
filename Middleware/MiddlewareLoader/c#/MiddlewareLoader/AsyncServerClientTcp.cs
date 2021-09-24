﻿using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace MiddlewareLoader
{

    namespace Async
    {
        class ServerClientTcp : Socket
        {
            /// <summary>
            /// le o Servidor
            /// </summary>
            public ServerTcp Servidor { get; }
            
            /// <summary>
            /// le a Id do cliente
            /// </summary>
            public int Id { get; }

            /// <summary>
            /// thread do loop de recebimento.
            /// </summary>
            private Task TsakRecvLoop;

            /// <summary>
            /// Lista de eventos a serem executadas.
            /// </summary>
            public List<List<MiddlewareModule>> Events;
            
            /// <summary>
            /// metodo construtor do cliente
            /// </summary>
            /// <param name="id"></param>
            /// <param name="sv"></param>
            public ServerClientTcp(int id,ServerTcp sv)
            {
                this.Id = id;
                this.Servidor = sv;
            }
            
            /// <summary>
            /// Envia o Buff ao alvo.
            /// </summary>
            /// <param name="buff"></param>
            /// <returns></returns>
            public override bool SendBuffer(Buffer buff)
            {
                Dictionary<string, object> args = new Dictionary<string, object>();
                var err = new ErrorMesage { code = (int)EventType.Sended, description = "OK" };

                args.Add("Server", this.Servidor);
                args.Add("Client", this);
                args.Add("ErrorMessage", err);
                args.Add("Buffer", buff);

                foreach (var module in Events[(int)EventType.Sended])
                {
                    module.Main(args);
                }

                return base.SendBuffer(buff); ;
            }

            /// <summary>
            /// Inicia a thread de comunicação entre os pontos
            /// </summary>
            public void InitCommunication()
            {
                this.TsakRecvLoop = Task.Run(() =>
                {
                    RecvLoop(this);
                });
            }


            /// <summary>
            /// Função asincrona para ficar recebendo mensagens.
            /// </summary>
            /// <param name="client"></param>
            private void RecvLoop(ServerClientTcp client)
            {
                Dictionary<string, object> args;
                ErrorMesage err;
                while (client.Connected)
                {
                    var novo = client.GetBuffer();
                    if (!client.Connected)
                    {
                        break;
                    }

                    args = new Dictionary<string, object>();

                    err = new ErrorMesage {code = (int) EventType.Received, description = "OK"};

                    args.Add("Server", client.Servidor);
                    args.Add("Client", client);
                    args.Add("ErrorMessage", err);
                    args.Add("Buffer", novo);

                    foreach (var module in Events[(int)EventType.Received])
                    {
                        module.Main(args);
                    }
                }

                args = new Dictionary<string, object>();

                err = new ErrorMesage {code = (int) EventType.Disconnected, description = "Disconnected"};

                args.Add("Server", client.Servidor);
                args.Add("Client", client);
                args.Add("ErrorMessage", err);

                foreach (var module in Events[(int)EventType.Disconnected])
                {
                    module.Main(args);
                }

                client.Servidor.Clients.Remove(client.Id);

            }
        }
    }
}

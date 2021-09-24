using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace MiddlewareLoader
{
    class Socket
    {
        public bool Connected
        {
            get
            {
                bool part1 = this.Socket_.Poll(1000, SelectMode.SelectRead);
                bool part2 = (this.Socket_.Available == 0);
                if (part1 && part2)
                    return false;
                else
                    return true;
            }
        }

        public  System.Net.Sockets.Socket Socket_ { get; set; }
        public  System.Net.IPHostEntry    SockIPHostEntry { get; set; }
        public  IPAddress                 SockIPAddress { get; set; }
        public  IPEndPoint                SockIPEndPoint { get; set; }

        public  bool                      Listening { get; set; }  
        private int                       Port;
        private string                    Ip;


        /// <summary>
        /// Retorna Um Buffer ao receber os dados;
        /// </summary>
        /// <param name="maxBuffer"></param>
        /// <returns>retorna um objeto do tipo Buffer contendo os dados recebidos, caso esteja desconectado retorna null</returns>
        public virtual Buffer GetBuffer(int maxBuffer = 1500)
        {
            if (this.Socket_.Connected)
            {
                Byte[] bytes = new Byte[maxBuffer];
                int n_bytes = this.Socket_.Receive(bytes, maxBuffer, SocketFlags.None);
                return new Buffer(bytes, n_bytes, maxBuffer);
            }
            else
            {

                return null;
            }
        }

        public virtual bool SendBuffer(Buffer buff)
        {
            if (!Socket_.Connected)
            {
                return false;
            }
            this.Socket_.Send(buff.Data, 0, buff.ActualBuffer, SocketFlags.None);
            return true;
        }

        public virtual bool Connect(string ip, int port)
        {
            this.Ip = ip;
            this.Port = port;
            this.SockIPHostEntry = Dns.GetHostEntry(ip);

            foreach (IPAddress address in this.SockIPHostEntry.AddressList)
            {
                this.SockIPEndPoint = new IPEndPoint(address, port);
                this.Socket_        = new System.Net.Sockets.Socket(this.SockIPEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                this.SockIPAddress  = address;
                this.Socket_.Connect(this.SockIPEndPoint);
                if (this.Socket_.Connected)
                {
                    break;
                }
            }
            return true;
        }

        public virtual bool Disconnect()
        {
            this.Socket_.Disconnect(false);
            return true;
        }

        public virtual bool Listen(string ip = "127.0.0.1", int port = 25565, int backLog = 10)
        {
            this.Ip   = ip;
            this.Port = port;

            this.SockIPHostEntry = Dns.GetHostEntry(this.Ip);
            this.SockIPAddress   = this.SockIPHostEntry.AddressList[0];
            this.SockIPEndPoint  = new IPEndPoint(this.SockIPAddress, this.Port);
            this.Socket_         = new System.Net.Sockets.Socket(this.SockIPAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            this.Socket_.Bind(this.SockIPEndPoint);
            
            this.Socket_.Listen(backLog);
            
            this.Listening       = true;
            return true;
        }

        public virtual System.Net.Sockets.Socket AcceptConnection()
        {
            return this.Socket_.Accept();
        }
    }
}

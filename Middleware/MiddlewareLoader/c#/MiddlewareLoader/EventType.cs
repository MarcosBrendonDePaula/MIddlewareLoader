using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiddlewareLoader
{
    public enum EventType
    {
        Connected     = 0,
        Disconnected  = 1,
        Sended        = 2,
        Received      = 3,
        ServerStarted = 4,
        ClientStarted = 5,
    }
}

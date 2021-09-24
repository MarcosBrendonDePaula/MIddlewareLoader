﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MiddlewareLoader.Async;

namespace MiddlewareLoader
{
    class SendModule : MiddlewareModule
    {
        public override void Main(Dictionary<string, object> args)
        {
            base.Main(args);
            Buffer bf = (Buffer)args["Buffer"];
            ServerClientTcp client = (ServerClientTcp)args["Client"];
            bf.SetString(bf+" "+"Aloha");
        }
    }
}

﻿using System;
using System.Collections.Generic;
using MiddlewareLoader;
using MiddlewareLoader.Async;

namespace Teste
{
    class ReceivedModule : MiddlewareModule 
    {
        public override void Main(Dictionary<string, object> args)
        {
            var bf = (MiddlewareLoader.Buffer)args["Buffer"];
            if (args["Client"].GetType() == typeof(AsyncClientTcp))
            {
                Console.WriteLine("Recebi:" + bf);
            }
            else
            {
               
                var client = (ServerClientTcp)args["Client"];
                bf.SetString(bf + " Eu modifiquei o texto");
                Console.WriteLine("Recebi:" + bf + " de " + client.Id);
            }
            


            
        }
    }
}

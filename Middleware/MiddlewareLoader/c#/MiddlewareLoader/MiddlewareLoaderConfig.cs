using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiddlewareLoader
{
    class MiddlewareLoaderConfig
    {
        public static bool DebugMode = true;

        public static void CallEvents(Dictionary<string, Object> args , List<List<MiddlewareModule>> Events, EventType ev)
        {
            foreach (var module in Events[(int)ev])
            {
                if (MiddlewareLoaderConfig.DebugMode) Console.WriteLine("Call: " + module.GetType().Name + ".Main");
                module.Main(args);
            }
        }
    }
}

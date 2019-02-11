using System;

namespace cs
{

    class CefEngine
    {
	public void Shutdown()
	{
            Console.WriteLine("Shutdown()");
	    GC.Collect();
	    GC.WaitForPendingFinalizers();
	}
    }

    class Config
    {
	CefEngine engine = new CefEngine();

	~Config()
	{
	    engine.Shutdown();
            Console.WriteLine("after Shutdown");
	}
    }

    class Program
    {
        static void Main(string[] args)
        {
	    Config c;
            Console.WriteLine("Hello World!");
	    for (var i = 0; i < 100; ++i) {
		c = new Config();
	    }
	    // c = null;
	    // GC.Collect();
            Console.WriteLine("DONE!");
        }
    }
}

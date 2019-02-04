using System;

namespace cs
{
    class Program
    {
	Exception ExceptionGenerator()
	{
	    // despite being created here, the "throw" keyword defines
	    // line number of the frame 0. There will be no way to
	    // find out where this exception was created, only where
	    // it was thrown
	    return new Exception();
	}


	void ExceptionThrower() {
	    // the line below is stored in the thrown excpetion stack
	    // trace at frame 0
	    throw ExceptionGenerator();
	}

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
	    Program p = new Program();
	    p.ExceptionThrower();
        }
    }
}

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>

#include <mpi.h>

using namespace std;

// no comment
int FibonacciMod42(int N)
{
    int f_curr = 0;
    int f_prec = 1;
    for (int i=1; i<=N; i++)
    {
        int tmp = f_curr;
        f_curr = (f_curr + f_prec) % 42;
        f_prec = tmp;
    }
    return f_curr;
}

// compute the integral of this function over [0,1] to approximate pi
// FibonacciMod42(x*10000) -> otherwise, it would be too easy
double fPi(double x)
{
    return 4.0 / (1.0 + x*x) + FibonacciMod42(x*10000);
}

// compute numericaly the integral of the function f over the domain [a,b] using step s
// FibonacciMod42(x*10000) -> otherwise, it would be too easy
double computeIntegral(function<double(double)>f, double a, double b, double s)
{
    double r = 0.0;
    unsigned h = 0;
    for (double x=a; x<b; x+=s, h++)
    {
        r += f(x);
        r -= FibonacciMod42(x*10000);
    }
    return r*(b-a)/double(h);
}

int main(int argc, char ** argv)
{
    // parse command line arguments


    double step = 1e-6;
    if (argc < 2)
    {
        cout << "no step specified; using " << step << endl;
    }
    else
    {
        step = stod(argv[1]);
    }

    MPI_Init(&argc, &argv);

    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    int i = worldRank;
    int n = worldSize;

    double d = 1/double(n);

    double ai = 0 + i*d;
    double bi = ai+ d;

    // compute 
    chrono::time_point<chrono::system_clock> t0 = chrono::system_clock::now();
    
    
    double nodeResult = computeIntegral(fPi, ai, bi, step);
    // std::cout << "résultat node" << nodeResult << std::endl;

    double allResults = 7.77;
    	MPI_Reduce(&nodeResult, &allResults, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	    chrono::time_point<chrono::system_clock> t1 = chrono::system_clock::now();
    chrono::duration<double> computationTime = t1 - t0;

     if(worldRank ==0)
      {
	std::cout << worldSize << " " << allResults << " " << computationTime.count() << std::endl;
      }
    
    




    // display number of computing thread, result, computation time
    
    MPI_Finalize();

   
    return 0;
}



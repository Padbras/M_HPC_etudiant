
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

// calcule le Nieme terme de la suite de "Fibonacci modulo 42"
// precondition : N >= 0



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

void CalculTab(std::vector<int>& tab, int debutSeg, int finSeg)
{
  for(int i = debutSeg; i < finSeg; i++)
    tab[i] = FibonacciMod42(i);
}

int main(int argc, char ** argv)
{
    // verifie les arguments de la ligne de commande
    if (argc != 2)
    {
        std::cout << "usage: " << argv[0] << " <nbData>" << std::endl;
        return -1;
    }

    // cree le tableau de donnees a calculer
    int nbData = std::stoi(argv[1]);
    std::vector<int> data(nbData); 

    std::thread thread1(CalculTab, std::ref(data), 0, nbData/2);
    std::thread thread2(CalculTab, std::ref(data), nbData/2, nbData);
    // calcule le tableau de donnees 
    // CalculTab(data, nbData);
    thread1.join();
    thread2.join();
    // ecrit les donnees calculees dans un fichier
    std::ofstream ofs("output.txt");
    for (int x : data)
    {
        ofs << x << ' ';
    }

    return 0;
}


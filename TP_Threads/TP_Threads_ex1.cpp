
#include <iostream>
#include <thread>

// fonction qui affiche l'id du thread qui l'execute
void noyauCalcul() 
{
    std::thread::id idThread = std::this_thread::get_id();
    std::cout << "Bonjour, je suis le thread " << idThread << std::endl;
}

int main(int , char ** )
{
    std::thread thread1(noyauCalcul);
    std::thread thread2(noyauCalcul);
    // affiche l'id du thread principal
    // noyauCalcul();

    // TODO cree deux threads qui affiche leur id
    thread1.join();
    thread2.join();
    // TODO attend la fin de l'execution des threads

    return 0;
}


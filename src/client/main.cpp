#include <iostream>
#include <cstring>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <state.h>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML 





using namespace std;
using namespace state;


int main(int argc, char *argv[]) {
    
    if (argc >= 2) {
       
        if (std::strcmp(argv[1], "hello") == 0) { //comparaison of strings
           std::cout << "hello my dear" << std::endl;

        } else {
            // error if wrong command
            std::cout << "Wrong command. the correct command is  ../bin/client hello" << std::endl;
        }
    } else {
        // error if no argument
        std::cout << "Wrong command. the correct command is  ../bin/client hello" << std::endl;
    }

    return 0;
}



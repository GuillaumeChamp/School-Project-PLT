#include <iostream>
#include <cstring>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML 

#include <state.h>




using namespace std;
using namespace state;


int main(int argc, char *argv[]) {
    
    if (argc >= 2) {
       
        if (std::strcmp(argv[1], "hello") == 0) { //comparaisons des string
           std::cout << "Coucou mon petit " << std::endl;

        } else {
            // erreur si mauvaise commande
            std::cout << "Commande invalide. La seule commande est  ./bin/client hello" << std::endl;
        }
    } else {
        // Si aucun argument n'est fourni, affichez un message d'erreur
        std::cout << "Commande invalide. La seule commande est  ./bin/client hello" << std::endl;
    }

    return 0;
}


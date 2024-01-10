#include <boost/test/unit_test.hpp>
#include <chrono>
#include <thread> 
#include "../../PLT/src/server/server/Client.h"
#include <SFML/System/Thread.hpp>


using namespace server;
using namespace std::chrono;


BOOST_AUTO_TEST_CASE(TestClientConstructor)
{
    // Test du constructeur de la classe Client
    state::PlayerId playerId = state::PLAYER_A;
    std::string clientName = "John";
    Client client(clientName, playerId);

    // Vérifier que les attributs sont correctement initialisés
    BOOST_CHECK_EQUAL(client.getClientName(), clientName);
   
}

BOOST_AUTO_TEST_CASE(TestUpdateTimestamp)
{
    // Test de la fonction updateTimestamp de la classe Client
    state::PlayerId playerId = state::PLAYER_A;
    std::string clientName = "John";
    Client client(clientName, playerId);

    // Attente de 1 seconde
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Mise à jour du timestamp
    auto newTimestamp = high_resolution_clock::now();
    client.updateTimestamp(newTimestamp);

    // Vérifier que le timestamp a été correctement mis à jour
    BOOST_CHECK(client.getLastUpdate() == newTimestamp);
}

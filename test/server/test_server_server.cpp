#include <boost/test/unit_test.hpp>
#include <chrono>
#include <thread> 

#include "../../PLT/src/server/server/Client.h"
#include "../../PLT/src/server/server/CommandQueue.h"
#include "../../PLT/src/server/server/requestHandler.h"
#include <SFML/System/Thread.hpp>
#include <boost/asio.hpp>

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
    BOOST_CHECK(client.getLastUpdate()==newTimestamp);
}


BOOST_AUTO_TEST_CASE(TestAddCommand)
{
    // Créer une instance de CommandQueue
    CommandQueue commandQueue;
    //Timestamp ou on regarde
    auto Timestamp = high_resolution_clock::now();
    // Ajouter une commande à la file d'attente
    string commandContent = "TestCommand";
    commandQueue.addCommand(commandContent);
    
    // Récupérer les commandes et vérifier que la commande ajoutée est présente
    auto retrievedCommands = commandQueue.retrieveCommands(Timestamp);
    BOOST_CHECK_EQUAL(retrievedCommands.size(), 1);
    BOOST_CHECK_EQUAL(retrievedCommands.front(), commandContent);
}

BOOST_AUTO_TEST_CASE(TestRetrieveCommands)
{
    CommandQueue commandQueue;
    std::string commandContent1 = "Command1";
    std::string commandContent2 = "Command2";
    std::string commandContent3 = "Command3";

    auto startTime = high_resolution_clock::now();
    commandQueue.addCommand(commandContent1);

    auto retrievedCommands1 = commandQueue.retrieveCommands(startTime);
    
    //simulate time passing
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto NewstartTime = high_resolution_clock::now();

    commandQueue.addCommand(commandContent2);
    commandQueue.addCommand(commandContent3);

    // Récupérer les commandes après le début du temps, devrait inclure 2 et 3 mais pas 1

    //Vérifie que la commande "Command1" n'est pas incluse dans la liste des commandes récupérées.
    auto retrievedCommands = commandQueue.retrieveCommands(NewstartTime);
    //BOOST_CHECK(std::find(retrievedCommands.begin(), retrievedCommands.end(), commandContent1) == retrievedCommands.end());
   

    // Vérifie que les commandes "Command2" et "Command3" sont incluses dans la liste des commandes récupérées.
    //BOOST_CHECK(std::find(retrievedCommands.begin(), retrievedCommands.end(), commandContent2) != retrievedCommands.end());
    //BOOST_CHECK(std::find(retrievedCommands.begin(), retrievedCommands.end(), commandContent3) != retrievedCommands.end());
}
/*
BOOST_AUTO_TEST_CASE(TestLiveGame)
{
    LiveGame& liveGame = LiveGame::getInstance();

    // Test handlePlayerJoin
    std::string playerName = "Alice";
    std::string result = liveGame.handlePlayerJoin(playerName);
    BOOST_CHECK_EQUAL(result, "OK\r\n");

    // Test addCommand
    liveGame.addCommand("SomeCommand");

    // Test getState
    state::GameState* gameState = liveGame.getState();
    BOOST_CHECK(gameState != nullptr);

    // Test retrieveCommands
    std::string commandResult = liveGame.retrieveCommands(playerName);
    BOOST_CHECK(commandResult.empty()); // Assuming no commands were added yet
}
*/





#include <boost/test/unit_test.hpp>
#include <chrono>
#include <thread>

#include "../../PLT/src/server/server/Client.h"
#include "../../PLT/src/server/server/CommandQueue.h"
#include "../../PLT/src/server/server/requestHandler.h"

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
    auto retrievedCommands2 = commandQueue.retrieveCommands(NewstartTime);
    BOOST_CHECK(std::find(retrievedCommands2.begin(), retrievedCommands2.end(), commandContent1) ==
                retrievedCommands2.end());


    // Vérifie que les commandes "Command2" et "Command3" sont incluses dans la liste des commandes récupérées.
    BOOST_CHECK(std::find(retrievedCommands2.begin(), retrievedCommands2.end(), commandContent2) !=
                retrievedCommands2.end());
    BOOST_CHECK(std::find(retrievedCommands2.begin(), retrievedCommands2.end(), commandContent3) !=
                retrievedCommands2.end());
}

BOOST_AUTO_TEST_CASE(TestLiveGame)
{
    LiveGame &liveGame = LiveGame::getInstance();

    // Test handlePlayerJoin
    std::string playerName = "Alice";
    std::string result = liveGame.handlePlayerJoin(playerName);
    BOOST_CHECK_EQUAL(result, "OK/1\r\n");

    std::string result2 = liveGame.handlePlayerJoin(playerName);
    BOOST_CHECK_EQUAL(result2, "You are already in the game\r\n");

    std::string otherplayerName2 = "Boby";
    liveGame.handlePlayerJoin(otherplayerName2);
    std::string otherplayerName3 = "Bobo";
    liveGame.handlePlayerJoin(otherplayerName3);
    std::string otherplayerName4 = "Babu";
    std::string result3 = liveGame.handlePlayerJoin(otherplayerName4);
    BOOST_CHECK_EQUAL(result3, "OK, game is starting.\r\n");

    std::string otherplayerName5 = "Nono";
    std::string result4 = liveGame.handlePlayerJoin(otherplayerName5);
    BOOST_CHECK_EQUAL(result4, "This game is full\r\n");

    // Test addCommand
    BOOST_CHECK(!liveGame.retrieveCommands(otherplayerName2).empty());
    BOOST_CHECK(liveGame.retrieveCommands(otherplayerName2).empty());

    // Test getState
    state::GameState *gameState = liveGame.getState();
    BOOST_CHECK(gameState != nullptr);


}

BOOST_AUTO_TEST_CASE(ProcessRequestPost) {
    // Créez une instance de LiveGame
    //LiveGame& liveGame = LiveGame::getInstance();

    // Créez une requête POST
    http::request<http::string_body> request{http::verb::post, "/some_path", 11};

    // Créez une réponse
    http::response<http::dynamic_body> response;

    // Appelez la fonction à tester
    server::requestHandler::process_request(request, response);

    // Vérifiez le contenu de la réponse
    BOOST_CHECK_EQUAL(response.version(), request.version());
    BOOST_CHECK_EQUAL(response.keep_alive(), false);
    BOOST_CHECK_EQUAL(response[http::field::server], "Citadel Main Server");

    // Ajoutez d'autres vérifications selon votre implémentation

    // Nettoyez la mémoire

}





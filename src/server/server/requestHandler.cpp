//
// Created by guillaume on 12/31/23.
//

#include "requestHandler.h"

using namespace server;

void
requestHandler::handlePost(http::request<http::string_body> &request, http::response<http::dynamic_body> &response) {
    std::string requestTarget = (string) request.target();
    response.set(http::field::content_type, "text/plain");
    if (requestTarget == "/command") {
        if (LiveGame::getInstance().getState() == nullptr) {
            beast::ostream(response.body()) << "Game is not started yet\r\n";
            return;
        }
        string content = request.body();
        LiveGame::getInstance().addCommand(content);
        beast::ostream(response.body()) << "Command registered\r\n";
        return;
    }
    if (requestTarget == "/player") {
        std::string playerName = request.body();
        beast::ostream(response.body()) << LiveGame::getInstance().handlePlayerJoin(playerName);
        return;
    }
    response.result(http::status::not_found);
    beast::ostream(response.body()) << "File not found\r\n";
}

// Determine what needs to be done with the request message.
void requestHandler::process_request(http::request<http::string_body> &request,
                                     http::response<http::dynamic_body> &response) {
    response.version(request.version());
    response.keep_alive(false);
    switch (request.method()) {
        case http::verb::get:
            response.result(http::status::ok);
            response.set(http::field::server, "Beast");
            requestHandler::handleGet(request, response);
            break;
        case http::verb::post:
            response.result(http::status::ok);
            response.set(http::field::server, "Beast");
            requestHandler::handlePost(request, response);
            break;
        default:
            // We return responses indicating an error if
            // we do not recognize the request method.
            response.result(http::status::bad_request);
            response.set(http::field::content_type, "text/plain");
            beast::ostream(response.body())
                    << "Invalid request-method '"
                    << std::string(request.method_string())
                    << "'";
            break;
    }
}

// Construct a response message based on the program state.
void
requestHandler::handleGet(http::request<http::string_body> &request, http::response<http::dynamic_body> &response) {
    auto pos = request.target().find('#');
    std::string requestTarget = (string) request.target();
    std::string primaryTarget = requestTarget.substr(0, pos);

    if (primaryTarget == "/state") {
        response.set(http::field::content_type, "application/json");
        auto state1 = LiveGame::getInstance().getState();
        if (state1 == nullptr) {
            beast::ostream(response.body()) << "Game is not started yet \r\n";
            return;
        }
        beast::ostream(response.body()) << state::StateSerializer::serialize(*state1);
        return;
    }
    if (primaryTarget == "/command") {
        std::string playerName = requestTarget.substr(pos, requestTarget.size());
        auto strings = LiveGame::getInstance().retrieveCommands(playerName);
        beast::ostream(response.body()) << strings;
        return;
    }
    response.result(http::status::not_found);
    response.set(http::field::content_type, "text/plain");
    beast::ostream(response.body()) << "File not found\r\n";

}

state::GameState requestHandler::generateSampleState() {
    state::Player playerA{"player1", state::PlayerId::PLAYER_A};
    state::Player playerB{"player2", state::PlayerId::PLAYER_B};
    state::Player playerC{"player3", state::PlayerId::PLAYER_C};
    state::Player playerD{"player4", state::PlayerId::PLAYER_D};

    state::Card card1{"1", state::CardType::COMMERCIAL, 2};
    state::Card card2{"2", state::CardType::COMMERCIAL, 2};
    state::Card card3{"25", state::CardType::COMMERCIAL, 2};


    playerA.setCharacter(state::CharacterType::WARLORD);
    playerB.setCharacter(state::CharacterType::BISHOP);
    playerC.setCharacter(state::CharacterType::MERCHANT);
    playerD.setCharacter(state::CharacterType::KING);

    std::vector<state::Card> playerABoard{card1};
    std::vector<state::Card> playerBBoard{card2};
    std::vector<state::Card> playerCBoard{card2, card1, card3};
    std::vector<state::Card> playerDBoard{card1, card2};

    playerA.setBoardOfPlayer(playerABoard);
    playerB.setBoardOfPlayer(playerBBoard);
    playerC.setBoardOfPlayer(playerCBoard);
    playerD.setBoardOfPlayer(playerDBoard);

    state::GameState gameState{std::vector<state::Player>{playerA, playerB, playerC, playerD}};
    return gameState;
}
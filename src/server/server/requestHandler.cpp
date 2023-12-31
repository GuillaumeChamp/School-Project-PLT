//
// Created by guillaume on 12/31/23.
//

#include "requestHandler.h"


void requestHandler::log_command(http::request<http::string_body> &request,http::response<http::dynamic_body> &response) {
    response.set(http::field::content_type, "text/plain");
    if (request.target() == "/command") {
        std::string content = request.body();
        //parsing
        auto pos = content.find(',');
        std::string token1 = content.substr(0, pos);
        content.erase(0, pos + 1);
        pos = content.find(',');
        std::string token2 = content.substr(0, pos);
        content.erase(0, pos + 1);
        pos = content.find(',');
        std::string token3 = content.substr(0, pos);
        content.erase(0, pos + 1);
        std::cout << "source : " << token1 << " object : " << token2 << " target : " << token3 << std::endl;
        beast::ostream(response.body()) << "Command registered\r\n";
    } else {
        response.result(http::status::not_found);
        beast::ostream(response.body()) << "File not found\r\n";
    }
}

// Determine what needs to be done with the request message.
void requestHandler::process_request(http::request<http::string_body> &request,http::response<http::dynamic_body> &response) {
    response.version(request.version());
    response.keep_alive(false);
    switch (request.method()) {
        case http::verb::get:
            response.result(http::status::ok);
            response.set(http::field::server, "Beast");
            requestHandler::create_response(request,response);
            break;
        case http::verb::post:
            response.result(http::status::ok);
            response.set(http::field::server, "Beast");
            requestHandler::log_command(request,response);
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
void requestHandler::create_response(http::request<http::string_body> &request,http::response<http::dynamic_body> &response) {
    if (request.target() == "/state") {
        response.set(http::field::content_type, "application/json");
        state::GameState state1 = requestHandler::generateSampleState();
        beast::ostream(response.body()) << state::StateSerializer::serialize(state1);
    } else {
        response.result(http::status::not_found);
        response.set(http::field::content_type, "text/plain");
        beast::ostream(response.body()) << "File not found\r\n";
    }
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
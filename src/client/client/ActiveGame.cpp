//
// Created by guillaume on 1/10/24.
//

#include "ActiveGame.h"

ActiveGame::ActiveGame(state::PlayerId playerId, const std::string& name, bool &notif) {
    this->myId = playerId;
    this->myName = name;
    switch (playerId) {
        case state::PLAYER_A:
            this->game = std::make_shared<state::GameState>(name, "chicken", "bean", "car");
            break;
        case state::PLAYER_B:
            this->game = std::make_shared<state::GameState>("raptor", name, "bean", "car");
            break;
        case state::PLAYER_C:
            this->game = std::make_shared<state::GameState>("raptor", "chicken", name, "car");
            break;
        default:
            this->game = std::make_shared<state::GameState>("raptor", "chicken", "bean", name);
            break;
    }
    engine::Engine::init(*this->game);
    std::thread t3(networkLookup, std::ref(notif), myName,myId);
    t3.detach();
}

ActiveGame::~ActiveGame() = default;

void ActiveGame::networkLookup(bool &notif, const std::string& name,const state::PlayerId myId) {
    while (true) {
        if (notif) {
            notif = false;
            std::string content;
            std::ifstream answerFile;
            answerFile.open(IHM_TEMP_FILE);
            if (!answerFile.is_open()) {
                return;
            }
            while (answerFile) {
                answerFile >> content;
            }
            ApiManager::sendMessage("POST", "/command", std::to_string(myId)+","+content);
        }
        ApiManager::sendMessage("GET", "/command", name);
        std::string answer = ApiManager::readAnswer();
        if (!answer.empty() && answer !=" ") {
            std::istringstream iss(answer);
            std::string token;

            // Tokenize the input string based on commas
            while (std::getline(iss, token, ';')) {
                auto newCommand = engine::CommandCreator::createCommand(token);
                if (newCommand!= nullptr) { engine::Engine::getInstance().addCommand(newCommand); }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

std::shared_ptr<state::GameState> ActiveGame::getGame() const {
    return game;
}

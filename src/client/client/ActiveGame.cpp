//
// Created by guillaume on 1/10/24.
//

#include "ActiveGame.h"

ActiveGame::ActiveGame(state::PlayerId playerId, std::string name, bool &notif) {
    myId = playerId;
    myName = name;
    switch (playerId) {
        case state::PLAYER_A:
            this->game = new state::GameState(name, "chicken", "bean", "car");
            break;
        case state::PLAYER_B:
            this->game = new state::GameState("raptor", name, "bean", "car");
            break;
        case state::PLAYER_C:
            this->game = new state::GameState("raptor", "chicken", name, "car");
            break;
        default:
            this->game = new state::GameState("raptor", "chicken", "bean", name);
            break;
    }
    std::thread t3(networkLookup, std::ref(notif), myName);
    t3.detach();
}

ActiveGame::~ActiveGame() {

}

void ActiveGame::networkLookup(bool &notif, std::string name) {
    while (1) {
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
        if (!answer.empty()) {
            //TODO parse command
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

state::GameState *ActiveGame::getGame() const {
    return game;
}

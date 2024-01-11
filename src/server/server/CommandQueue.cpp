//
// Created by guillaume on 12/31/23.
//

#include "CommandQueue.h"

using namespace server;

CommandQueue::CommandQueue() = default;

CommandQueue::~CommandQueue() {
    commandList.clear();
}

void CommandQueue::addCommand(const std::string &commandContent) {
    if (commandList.size() > 20) {
        commandList.pop_back();
    }
    this->commandList.emplace_front(commandContent, std::chrono::high_resolution_clock::now());
}

std::vector<std::string> CommandQueue::retrieveCommands(std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate) {
    std::vector<std::string> output;
    int i;
    for (i = 0; i < (int) commandList.size(); i++) {
        if (commandList[i].second > lastUpdate) {
            break;
        }
    }
    for (; i < (int) commandList.size(); i++) {
        output.emplace_back(commandList[i].first);
    }
    return output;
}
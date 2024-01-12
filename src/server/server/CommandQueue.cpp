//
// Created by guillaume on 12/31/23.
//

#include "CommandQueue.h"

using namespace server;

CommandQueue::CommandQueue() = default;

CommandQueue::~CommandQueue() {
    commandList.clear();
}

void CommandQueue::addCommand(const string &commandContent) {
    if (commandList.size() > 20) {
        commandList.pop_back();
    }
    this->commandList.emplace_back(commandContent, high_resolution_clock::now());
}

vector<string> CommandQueue::retrieveCommands(time_point<high_resolution_clock> lastUpdate) {
    vector<string> output;
    int i;
    for (i = 0; i < (int) commandList.size(); i++) {
        if (commandList[i].second.time_since_epoch().count() - lastUpdate.time_since_epoch().count()>0) {
            break;
        }
    }
    for (; i < (int) commandList.size(); i++) {
        output.emplace_back(commandList[i].first);
    }
    return output;
}
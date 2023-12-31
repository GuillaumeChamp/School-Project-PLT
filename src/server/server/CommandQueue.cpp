//
// Created by guillaume on 12/31/23.
//

#include "CommandQueue.h"

using namespace server;

CommandQueue::CommandQueue() {}

CommandQueue::~CommandQueue() {
    commandList.clear();
}

void CommandQueue::addCommand(string commandContent){
    if (commandList.size()>20){
        commandList.pop_back();
    }
    this->commandList.emplace_front(commandContent,high_resolution_clock::now());
}

vector<string> CommandQueue::retrieveCommands(time_point<high_resolution_clock> lastUpdate){
    vector<string> output;
    int i;
    for (i=0;i<commandList.size();i++){
        if(commandList[i].second>lastUpdate){
            break;
        }
    }
    for(;i<commandList.size();i++){
        output.emplace_back(commandList[i].first);
    }
    return output;
}
//
// Created by guillaume on 12/31/23.
//

#ifndef PLT_COMMANDQUEUE_H
#define PLT_COMMANDQUEUE_H

#include <deque>
#include "vector"
#include "chrono"
#include "string"

using namespace std;
using namespace std::chrono;

namespace server {
    class CommandQueue {
    private:
        deque<pair<string, time_point<high_resolution_clock>>> commandList;
    public:
        CommandQueue();

        ~CommandQueue();

        /**
         *  Add a command in the commandQueue
         */
        void addCommand(const string&);
        /**
         * allow to retrieve new command
         * @param lastUpdate last command update
         * @return a vector containing the new commands
         */
        vector<string> retrieveCommands(time_point<high_resolution_clock> lastUpdate);
    };
}

#endif
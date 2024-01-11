#ifndef PLT__CLIENT__H
#define PLT__CLIENT__H

#include <string>
#include "vector"

#include "state/PlayerId.h"
#include <chrono>

using namespace std::chrono;
namespace server {

    /// class Client -
    class Client {
    private:
        std::string clientName;
        state::PlayerId playerId;
        time_point<high_resolution_clock> lastUpdate;
    public:
        Client(std::string name, state::PlayerId);
        ~Client();
        // update the lastUpdate timestamp
        void updateTimestamp(const time_point<high_resolution_clock> &lastUpdate);

        // Getters
        const std::string &getClientName() const;

        const time_point<high_resolution_clock> &getLastUpdate() const;

    };

}

#endif
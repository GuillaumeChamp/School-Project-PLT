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
        // Attributes
    private:
        std::string clientName;
        state::PlayerId playerId;
        time_point<high_resolution_clock> lastUpdate;
        // Operations
    public:
        Client(std::string name, state::PlayerId);

        const std::string &getClientName() const;

        const time_point<high_resolution_clock> &getLastUpdate() const;

        void updateTimestamp(const time_point<high_resolution_clock> &lastUpdate);
    };

}

#endif

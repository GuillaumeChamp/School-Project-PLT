//
// Created by guillaume on 1/9/24.
//

#ifndef PLT_APIMANAGER_H
#define PLT_APIMANAGER_H

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "httpClient.h"

class ApiManager {
private:
    static const char * host;
    static const char * port;
    const static int version = 11;
public:
    static void initNetwork(const char * hostName,const char * portString);
    static std::string sendMessage(const std::string& target,const std::string& content);
};


#endif //PLT_APIMANAGER_H

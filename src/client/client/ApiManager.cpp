//
// Created by guillaume on 1/9/24.
//

#include "ApiManager.h"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

const char * ApiManager::host = nullptr;
const char * ApiManager::port = nullptr;
void ApiManager::initNetwork(const char * hostName,const char * portString) {
    ApiManager::host = hostName;
    ApiManager::port = portString;
}
// Performs an HTTP GET and prints the response
std::string ApiManager::sendMessage(const std::string& target,const std::string& content) {
    if (ApiManager::host==nullptr){
        return {"WARNING : network is not initialized"};
    }
    // The io_context is required for all I/O
    net::io_context ioc;
    std::make_shared<session>(ioc)->run(host,port, target, content, version);
    ioc.run();
    return {};
}
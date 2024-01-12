//
// Created by guillaume on 1/9/24.
//
#include "ApiManager.h"

#define DEMO true
#define TEMP_DEST "/tmp/cit_api.txt"

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
void ApiManager::sendMessage(const std::string& requestType, const std::string& target,const std::string& content) {
    if (ApiManager::host==nullptr){
        return;
    }
    if (DEMO){
        std::string cmd = "curl -X " + requestType + " ";
        cmd.append(host);
        cmd +=':';
        cmd.append(port).append(target);
        if (!content.empty()){
            cmd.append(" -d ").append(content);
        }
        cmd.append(" > ").append(TEMP_DEST);
        system(cmd.c_str());
    } else{
        net::io_context ioc;
        std::make_shared<session>(ioc)->run(host,port, target, content, version);
        ioc.run();
    }
}

std::string ApiManager::readAnswer() {
    std::ifstream answerFile;
    answerFile.open(TEMP_DEST);
    std::string ans{};
    if (!answerFile.is_open()) {
        return "ERROR";
    }
    answerFile >> ans;
    return ans;
}

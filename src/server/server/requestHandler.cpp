//
// Created by guillaume on 12/31/23.
//

#include "requestHandler.h"
#include "iostream"

using namespace server;

void
requestHandler::handlePost(http::request<http::string_body> &request, http::response<http::dynamic_body> &response) {
    std::string requestTarget = (string) request.target();
    response.set(http::field::content_type, "text/plain");
    if (requestTarget == "/command") {
        if (LiveGame::getInstance().getState() == nullptr) {
            beast::ostream(response.body()) << "Game is not started yet\r\n";
            return;
        }
        string content = request.body();
        LiveGame::getInstance().addCommand(content);
        beast::ostream(response.body()) << "Command registered\r\n";
        return;
    }
    if (requestTarget == "/player") {
        std::string playerName = request.body();
        beast::ostream(response.body()) << LiveGame::getInstance().handlePlayerJoin(playerName);
        return;
    }
    response.result(http::status::not_found);
    beast::ostream(response.body()) << "File not found\r\n";
}

// Determine what needs to be done with the request message.
void requestHandler::process_request(http::request<http::string_body> &request,
                                     http::response<http::dynamic_body> &response) {
    response.version(request.version());
    response.keep_alive(false);
    response.set(http::field::server, "Citadel Main Server");
    switch (request.method()) {
        case http::verb::get:
            response.result(http::status::ok);
            requestHandler::handleGet(request, response);
            break;
        case http::verb::post:
            response.result(http::status::ok);
            std::cout<< request.body() <<std::endl;
            requestHandler::handlePost(request, response);
            break;
        default:
            // We return responses indicating an error if
            // we do not recognize the request method.
            response.result(http::status::bad_request);
            response.set(http::field::content_type, "text/plain");
            beast::ostream(response.body())
                    << "Invalid request-method '"
                    << std::string(request.method_string())
                    << "'";
            break;
    }
}

// Construct a response message based on the program state.
void
requestHandler::handleGet(http::request<http::string_body> &request, http::response<http::dynamic_body> &response) {
    if (request.body().empty()){
        beast::ostream(response.body()) << "No content ! Did you forget to include playerName ? \r\n";
        return;
    }
    std::string requestTarget = (string) request.target();
    if (LiveGame::getInstance().getState() == nullptr) {
        //beast::ostream(response.body()) << "Game is not started yet \r\n"; Empty body else the process will fail in client
        return;
    }
    if (requestTarget == "/state") {
        response.set(http::field::content_type, "application/json");
        beast::ostream(response.body()) << state::StateSerializer::serialize(*LiveGame::getInstance().getState());
        return;
    }
    if (requestTarget == "/command") {
        std::string playerName = request.body();
        auto strings = LiveGame::getInstance().retrieveCommands(playerName);
        beast::ostream(response.body()) << strings;
        return;
    }
    response.result(http::status::not_found);
    response.set(http::field::content_type, "text/plain");
    beast::ostream(response.body()) << "Invalid endpoint \r\n";
}

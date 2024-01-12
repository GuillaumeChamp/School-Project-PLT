//
// Created by guillaume on 12/31/23.
//

#include "requestHandler.h"
#include "../../shared/state/StateSerializer.h"
using namespace server;

void
requestHandler::handlePost(boost::beast::http::request<boost::beast::http::string_body> &request, boost::beast::http::response<boost::beast::http::dynamic_body> &response) {
    std::string requestTarget = (std::string) request.target();
    response.set(boost::beast::http::field::content_type, "text/plain");
    if (requestTarget == "/command") {
        if (LiveGame::getInstance().getState() == nullptr) {
            boost::beast::ostream(response.body()) << "Game is not started yet\r\n";
            return;
        }
        std::string content = request.body();
        LiveGame::getInstance().addCommand(content);
        boost::beast::ostream(response.body()) << "Command registered\r\n";
        return;
    }
    if (requestTarget == "/player") {
        std::string playerName = request.body();
        boost::beast::ostream(response.body()) << LiveGame::getInstance().handlePlayerJoin(playerName);
        return;
    }
    response.result(boost::beast::http::status::not_found);
    boost::beast::ostream(response.body()) << "File not found\r\n";
}

// Determine what needs to be done with the request message.
void requestHandler::process_request(boost::beast::http::request<boost::beast::http::string_body> &request,
                                     boost::beast::http::response<boost::beast::http::dynamic_body> &response) {
    response.version(request.version());
    response.keep_alive(false);
    response.set(boost::beast::http::field::server, "Citadel Main Server");
    switch (request.method()) {
        case boost::beast::http::verb::get:
            response.result(boost::beast::http::status::ok);
            requestHandler::handleGet(request, response);
            break;
        case boost::beast::http::verb::post:
            response.result(boost::beast::http::status::ok);
            requestHandler::handlePost(request, response);
            break;
        default:
            // We return responses indicating an error if
            // we do not recognize the request method.
            response.result(boost::beast::http::status::bad_request);
            response.set(boost::beast::http::field::content_type, "text/plain");
            boost::beast::ostream(response.body())
                    << "Invalid request-method '"
                    << std::string(request.method_string())
                    << "'";
            break;
    }
}

// Construct a response message based on the program state.
void
requestHandler::handleGet(boost::beast::http::request<boost::beast::http::string_body> &request, boost::beast::http::response<boost::beast::http::dynamic_body> &response) {
    if (request.body().empty()){
        boost::beast::ostream(response.body()) << "No content ! Did you forget to include playerName ? \r\n";
        return;
    }
    std::string requestTarget = (std::string) request.target();
    if (LiveGame::getInstance().getState() == nullptr) {
        boost::beast::ostream(response.body()) << "Game is not started yet \r\n";
        return;
    }
    if (requestTarget == "/state") {
        response.set(boost::beast::http::field::content_type, "application/json");
        boost::beast::ostream(response.body()) << state::StateSerializer::serialize(*LiveGame::getInstance().getState());
        return;
    }
    if (requestTarget == "/command") {
        std::string playerName = request.body();
        auto strings = LiveGame::getInstance().retrieveCommands(playerName);
        boost::beast::ostream(response.body()) << strings;
        return;
    }
    response.result(boost::beast::http::status::not_found);
    response.set(boost::beast::http::field::content_type, "text/plain");
    boost::beast::ostream(response.body()) << "Invalid endpoint \r\n";
}

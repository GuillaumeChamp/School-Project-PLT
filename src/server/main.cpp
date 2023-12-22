//
// Copyright (c) 2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, small
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <state.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

state::GameState generateSampleState();

state::GameState sample = generateSampleState();

class http_connection : public std::enable_shared_from_this<http_connection> {
public:
    explicit http_connection(tcp::socket socket) : socket_(std::move(socket)) {
    }

    // Initiate the asynchronous operations associated with the connection.
    void start() {
        read_request();
        check_deadline();
    }

private:
    // The socket for the currently connected client.
    tcp::socket socket_;

    // The buffer for performing reads.
    beast::flat_buffer buffer_{8192};

    // The request message.
    http::request<http::string_body> request_;

    // The response message.
    http::response<http::dynamic_body> response_;

    // The timer for putting a deadline on connection processing.
    net::steady_timer deadline_{socket_.get_executor(), std::chrono::seconds(60)};

    // Asynchronously receive a complete request message.
    void read_request() {
        auto self = shared_from_this();

        http::async_read(
                socket_,
                buffer_,
                request_,
                [self](beast::error_code ec,
                       std::size_t bytes_transferred) {
                    boost::ignore_unused(bytes_transferred);
                    if (!ec)
                        self->process_request();
                });
    }

    void log_command() {
        response_.set(http::field::content_type, "text/plain");
        if (request_.target() == "/command") {
            std::string content =request_.body();
            //parsing
            auto pos = content.find(',');
            std::string token1 = content.substr(0, pos);
            content.erase(0, pos + 1);
            pos = content.find(',');
            std::string token2 = content.substr(0, pos);
            content.erase(0, pos + 1);
            pos = content.find(',');
            std::string token3 = content.substr(0, pos);
            content.erase(0, pos + 1);
            std::cout << "source : " << token1 << " object : " << token2 << " target : " << token3 << std::endl;
            beast::ostream(response_.body()) << "Command registered\r\n";
        } else {
            response_.result(http::status::not_found);
            beast::ostream(response_.body()) << "File not found\r\n";
        }
    }

// Determine what needs to be done with the request message.
    void process_request() {
        response_.version(request_.version());
        response_.keep_alive(false);
        switch (request_.method()) {
            case http::verb::get:
                response_.result(http::status::ok);
                response_.set(http::field::server, "Beast");
                create_response();
                break;
            case http::verb::post:
                response_.result(http::status::ok);
                response_.set(http::field::server, "Beast");
                log_command();
                break;
            default:
                // We return responses indicating an error if
                // we do not recognize the request method.
                response_.result(http::status::bad_request);
                response_.set(http::field::content_type, "text/plain");
                beast::ostream(response_.body())
                        << "Invalid request-method '"
                        << std::string(request_.method_string())
                        << "'";
                break;
        }

        write_response();
    }

    // Construct a response message based on the program state.
    void create_response() {
        if (request_.target() == "/state") {
            response_.set(http::field::content_type, "application/json");
            beast::ostream(response_.body())
                    << state::StateSerializer::serialize(sample);
        } else {
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "File not found\r\n";
        }
    }

    // Asynchronously transmit the response message.
    void write_response() {
        auto self = shared_from_this();

        response_.set(http::field::content_length, std::to_string(response_.body().size()));

        http::async_write(
                socket_,
                response_,
                [self](beast::error_code ec, std::size_t) {
                    self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                    self->deadline_.cancel();
                });
    }

    // Check whether we have spent enough time on this connection.
    void check_deadline() {
        auto self = shared_from_this();

        deadline_.async_wait(
                [self](beast::error_code ec) {
                    if (!ec) {
                        // Close socket to cancel any outstanding operation.
                        self->socket_.close(ec);
                    }
                });
    }
};

// "Loop" forever accepting new connections.
void http_server(tcp::acceptor &acceptor, tcp::socket &socket) {
    acceptor.async_accept(socket,
                          [&](beast::error_code ec) {
                              if (!ec) {
                                  std::make_shared<http_connection>(std::move(socket))->start();
                              }
                              http_server(acceptor, socket);
                          });
}

int main(int argc, char *argv[]) {

    try {
        // Check command line arguments.
        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80\n";
            return EXIT_FAILURE;
        }

        auto const address = net::ip::make_address(argv[1]);
        auto port = static_cast<unsigned short>(std::atoi(argv[2]));

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        tcp::socket socket{ioc};
        http_server(acceptor, socket);

        ioc.run();
    }
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

state::GameState generateSampleState() {
    state::Player playerA{"player1", state::PlayerId::PLAYER_A};
    state::Player playerB{"player2", state::PlayerId::PLAYER_B};
    state::Player playerC{"player3", state::PlayerId::PLAYER_C};
    state::Player playerD{"player4", state::PlayerId::PLAYER_D};

    state::Card card1{"1", state::CardType::COMMERCIAL, 2};
    state::Card card2{"2", state::CardType::COMMERCIAL, 2};
    state::Card card3{"25", state::CardType::COMMERCIAL, 2};


    playerA.setCharacter(state::CharacterType::WARLORD);
    playerB.setCharacter(state::CharacterType::BISHOP);
    playerC.setCharacter(state::CharacterType::MERCHANT);
    playerD.setCharacter(state::CharacterType::KING);

    std::vector<state::Card> playerABoard{card1};
    std::vector<state::Card> playerBBoard{card2};
    std::vector<state::Card> playerCBoard{card2, card1, card3};
    std::vector<state::Card> playerDBoard{card1, card2};

    playerA.setBoardOfPlayer(playerABoard);
    playerB.setBoardOfPlayer(playerBBoard);
    playerC.setBoardOfPlayer(playerCBoard);
    playerD.setBoardOfPlayer(playerDBoard);

    state::GameState gameState{std::vector<state::Player>{playerA, playerB, playerC, playerD}};
    return gameState;
}
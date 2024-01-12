#include "requestHandler.h"

#ifndef PLT_HTTP_CONNECTION_H
#define PLT_HTTP_CONNECTION_H

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace server {

    class http_connection : public std::enable_shared_from_this<http_connection> {

    public:
        explicit http_connection(tcp::socket socket);

        // Initiate the asynchronous operations associated with the connection.
        void start();

    private:
        // The socket for the currently connected client.
        tcp::socket socket_;

        // The buffer for performing reads.
        beast::flat_buffer buffer_{8192};

        // The request message.
        http::request <http::string_body> request_;

        // The response message.
        http::response <http::dynamic_body> response_;

        // The timer for putting a deadline on connection processing.
        net::steady_timer deadline_{socket_.get_executor(), std::chrono::seconds(60)};

        // Asynchronously receive a complete request message.
        void read_request();

        // Check whether we have spent enough time on this connection.
        void check_deadline();

        // Asynchronously transmit the response message.
        void write_response();
    };
}

#endif //PLT_HTTP_CONNECTION_H
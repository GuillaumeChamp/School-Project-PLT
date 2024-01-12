#include <iostream>
#include "http_connection.h"

using namespace server;

void http_connection::start() {
    read_request();
    check_deadline();
}

void http_connection::read_request() {
    auto self = shared_from_this();
    http::async_read(socket_, buffer_, request_,
                     [self](beast::error_code ec, std::size_t bytes_transferred) {
                         boost::ignore_unused(bytes_transferred);
                         if (!ec)
                             requestHandler::process_request(self->request_, self->response_);
                         self->write_response();
                     });
}


void http_connection::write_response() {
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

void http_connection::check_deadline() {
    auto self = shared_from_this();

    deadline_.async_wait(
            [self](beast::error_code ec) {
                if (!ec) {
                    // Close socket to cancel any outstanding operation.
                    self->socket_.close(ec);
                }
            });
}

http_connection::http_connection(tcp::socket socket) : socket_(std::move(socket)) {
}

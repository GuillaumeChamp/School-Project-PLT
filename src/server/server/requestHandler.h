#ifndef PLT_REQUESTHANDLER_H
#define PLT_REQUESTHANDLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include "server/LiveGame.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

namespace server {
    class requestHandler {
    public:
        // handle request and dispense
        static void
        process_request(http::request <http::string_body> &request, http::response <http::dynamic_body> &response);
    private:
        // handle all post type request
        static void
        handlePost(http::request <http::string_body> &request, http::response <http::dynamic_body> &response);
        // handle all get request
        static void
        handleGet(http::request <http::string_body> &request, http::response <http::dynamic_body> &response);
    };
}

#endif //PLT_REQUESTHANDLER_H

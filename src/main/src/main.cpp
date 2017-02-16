#include <iostream>

#include "pi_websocket_server.h"
#include "pi_osc_handler.h"
#include "osc_listener.h"

int main() {
    auto s = std::make_shared<pi_ws_server>(9162);
    s->start_server();

    auto handler = std::make_unique<pi_osc_handler>(s);
    osc_listener listener(std::move(handler), 4558);

    listener.start();
}

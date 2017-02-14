#include <iostream>

#include "pi_websocket_server.h"

int main() {
    pi_ws_server server(9162);

    server.start_server();
    server.join();
}

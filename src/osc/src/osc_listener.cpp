#include <iostream>

#include "osc_listener.h"

osc_listener::osc_listener(std::unique_ptr<osc_handler> handler_ptr, int port) :
    handler(std::move(handler_ptr)),
    incoming_port_open(false),
    stop_server(false),
    port(port)
{
}

// Ad-hoc partial order of
// handler->server_started > handler->signal_server_stop > stop_server
// TODO: make this harder to get wrong

bool osc_listener::is_incoming_port_open() {
    return incoming_port_open;
}

bool osc_listener::wait_for_server() {
    return !handler->server_started && continue_listening();
}

bool osc_listener::is_server_started() {
    return handler->server_started;
}

bool osc_listener::continue_listening() {
    return !handler->signal_server_stop && !stop_server;
}

void osc_listener::stop() {
    std::cout << "Stopping UDP Server...\n";
    stop_server = true;
}

void osc_listener::start() {
    std::cout << "Starting UDP OSC Server on port " << port << "...\n" <<
        std::flush;
    oscpkt::UdpSocket sock;
    sock.bindTo(port);
    if (!sock.isOk()) {
        std::cout << "Unable to listen to UDP sockets on port " << port
            << "\n" << std::flush;
        // TODO: raise some sort of higher level exception
        return;
    }

    std::cout << "UDP Server ready and listening\n" << std::flush;
    incoming_port_open = true;

    while (sock.isOk() && continue_listening()) {
        if (sock.receiveNextPacket(LISTEN_TIMEOUT)) {
            handler->handle_message(sock.buffer);
            std::vector<char>().swap(sock.buffer);
        }
    }

    std::cout << "UDP OSC Server no longer listening\n" << std::flush;
    incoming_port_open = false;
}


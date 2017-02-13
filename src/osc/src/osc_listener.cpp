#include <iostream>

#include "osc_listener.h"

OSCListener::OSCListener(std::unique_ptr<OSCHandler> handler_ptr, int port) :
    handler(std::move(handler_ptr)),
    incoming_port_open(false),
    stop_server(false),
    port(port)
{
}

// Ad-hoc partial order of
// handler->server_started > handler->signal_server_stop > stop_server
// TODO: make this harder to get wrong

bool OSCListener::IsIncomingPortOpen() {
    return incoming_port_open;
}

bool OSCListener::waitForServer() {
    return !handler->server_started && continueListening();
}

bool OSCListener::isServerStarted() {
    return handler->server_started;
}

bool OSCListener::continueListening() {
    return !handler->signal_server_stop && !stop_server;
}

void OSCListener::stop() {
    std::cout << "Stopping UDP Server...\n";
    stop_server = true;
}

void OSCListener::start() {
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

    while (sock.isOk() && continueListening()) {
        if (sock.receiveNextPacket(LISTEN_TIMEOUT)) {
            handler->handleMessage(sock.buffer);
            std::vector<char>().swap(sock.buffer);
        }
    }

    std::cout << "UDP OSC Server no longer listening\n" << std::flush;
    incoming_port_open = false;
}


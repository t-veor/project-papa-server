#include <iostream>

#include "server.h"

server::server(int port) {
    wss.config.port = port;

    ws_server::Endpoint& default_endpoint = wss.endpoint["^/$"];
    default_endpoint.on_message = [this] (auto conn, auto msg) {
        this->on_message(conn, msg);
    };
}

server::~server() {
    stop_server();
    join();
}

void server::start_server() {
    server_thread = std::thread( [this] () {
        this->wss.start();
    });
    std::cout << "Server started on port " << wss.config.port << "\n";
}

void server::stop_server() {
    wss.stop();
}

void server::join() {
    server_thread.join();
}

void server::on_message(connection conn, message msg) {
    std::string message_str = msg->string();
    std::cout << message_str << "\n";
    auto send_stream = std::make_shared<ws_server::SendStream>();
    *send_stream << message_str;
    wss.send(conn, send_stream);
}

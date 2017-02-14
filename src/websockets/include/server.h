#ifndef SERVER_H
#define SERVER_H

#include "server_ws.hpp"

typedef SimpleWeb::SocketServer<SimpleWeb::WS> ws_server;
typedef std::shared_ptr<ws_server::Connection> connection;
typedef std::shared_ptr<ws_server::Message> message;

class server {
    public:
        server(int port);
        ~server();

        void start_server();
        void stop_server();

        void join();

    protected:
        virtual void on_message(connection conn, message msg);

        ws_server wss;

    private:
        std::thread server_thread;
};

#endif

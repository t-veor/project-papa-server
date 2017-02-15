#include "osc_handler.h"

osc_handler::osc_handler() :
    signal_server_stop(false),
    server_started(true)
{
}

void osc_handler::handle_message(std::vector<char> buffer) {
    pr.init(buffer.data(), buffer.size());

    oscpkt::Message* msg;
    while (pr.isOk() && (msg = pr.popMessage()) != 0) {
        handle(msg);
    }
}

bool osc_handler::handle(oscpkt::Message* msg) {
    if (msg->match("/exited")) {
        signal_server_stop = true;
    }
    else if (msg->match("/exited-with-boot-error")) {
        signal_server_stop = true;
    }
    else if (msg->match("/ack")) {
        server_started = true;
    }
    else {
        return false;
    }
    return true;
}

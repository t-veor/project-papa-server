#include <chrono>
#include <memory>
#include <thread>

#include "catch.hpp"

#include "oscpkt.hh"

#include "osc_handler.h"
#include "osc_listener.h"
#include "osc_sender.h"

TEST_CASE( "basic sending and receiving" ) {
    // setup
    int port = 9612;
    osc_sender sender(port);
    std::unique_ptr<osc_handler> handler(new osc_handler());
    osc_listener listener(std::move(handler), port);

    // start the listener running
    std::thread t(&osc_listener::start, &listener);

    SECTION( "listen for an /ack message" ) {
        oscpkt::Message msg("/ack");
        sender.send_osc(msg);

        std::this_thread::sleep_for(std::chrono::milliseconds(75));

        REQUIRE( listener.is_incoming_port_open() );
    }

    listener.stop();
    t.join();
}

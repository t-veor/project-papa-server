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
    OSCSender sender(port);
    std::unique_ptr<OSCHandler> handler(new OSCHandler());
    OSCListener listener(std::move(handler), port);

    // start the listener running
    std::thread t(&OSCListener::start, &listener);

    SECTION( "listen for an /ack message" ) {
        oscpkt::Message msg("/ack");
        sender.sendOSC(msg);

        std::this_thread::sleep_for(std::chrono::milliseconds(75));

        REQUIRE( listener.IsIncomingPortOpen() );
    }

    listener.stop();
    t.join();
}

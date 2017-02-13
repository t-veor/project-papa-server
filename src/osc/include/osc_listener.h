#ifndef OSC_LISTENER_H
#define OSC_LISTENER_H

#include "osc_handler.h"
#include "udp.hh"

#include <atomic>
#include <memory>

#define LISTEN_TIMEOUT 30

/**
 * A server listening to OSC messages.
 * Listens to UDP OSC messages on the specified port and handles them with the
 * OSCHandler object provided.
 */
class OSCListener {
    public:
        /**
         * Constructs an OSCListener.
         * @param handler_ptr A unique_ptr to the handler you wish this
         *                    OSCListener to handle messages with. Note that to
         *                    pass it to the constructor you will need to first
         *                    create a unique_ptr and then use std::move to
         *                    pass it in.
         * @param port the port you want the listener to listen on
         */
        OSCListener(std::unique_ptr<OSCHandler>handler_ptr, int port);

        /**
         * Returns true if the OSCListener is currently listening for UDP OSC
         * messages.
         * @return see description
         */
        bool IsIncomingPortOpen();

        /**
         * Returns true if the Sonic Pi server listening to has not started,
         * and the listener is still running.
         * @return see description
         */
        bool waitForServer();

        /**
         * Returns true if the Sonic Pi server has started.
         * @return see description
         */
        bool isServerStarted();

        /**
         * Signals to the listener thread if one exists that it should stop at
         * the next opportunity. Note that this does not stop the thread
         * instantaneously.
         */
        void stop();

        /**
         * Start the listener's read-loop. This method should be started on a
         * separate thread.
         */
        void start();

    private:
        std::unique_ptr<OSCHandler> handler;
        std::atomic<bool> incoming_port_open;
        std::atomic<bool> stop_server;
        int port;
        bool continueListening();
};

#endif

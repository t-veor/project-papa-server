#ifndef OSC_HANDLER_H
#define OSC_HANDLER_H

#include "oscpkt.hh"

#include <atomic>
#include <vector>

/**
 * A OSC message handler class.
 * It decodes OSC messages and acts appropriately with their contents.
 */
class OSCHandler {
    public:
        /**
         * Constructs an OSCHandler.
         */
        OSCHandler();

        /**
         * Given a char buffer, decodes all possible messages in the buffer and
         * handles each one accordingly.
         * @param buffer Character buffer, which should be obtained from
         *               oscpkt::UupSocket#buffer
         */
        void handleMessage(std::vector<char> buffer);

        /**
         * Boolean flag to indicate if the stop signal from the server has been
         * received.
         */
        std::atomic<bool> signal_server_stop;

        /**
         * Boolean flag to indicate if an acknowledgement packet has been so
         * far received.
         */
        std::atomic<bool> server_started;
    private:
        oscpkt::PacketReader pr;
};

#endif

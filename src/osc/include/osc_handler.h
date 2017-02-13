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
        virtual ~OSCHandler() {}

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

    protected:
        /**
         * Handles message objects.  This is the function that handleMessage
         * actually calls to act upon every message it decodes.  You can
         * override it in subclasses to provide different behavior.
         * @param msg pointer to message object
         */
        virtual void handle(oscpkt::Message* msg);

    private:
        oscpkt::PacketReader pr;
};

#endif

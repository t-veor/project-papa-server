#ifndef OSC_HANDLER_H
#define OSC_HANDLER_H

#include "oscpkt.hh"

#include <atomic>
#include <vector>

/**
 * An OSC message handler class.
 * It decodes OSC messages and acts appropriately with their contents.
 */
class osc_handler {
    public:
        /**
         * Constructs an osc_handler.
         */
        osc_handler();
        virtual ~osc_handler() {}

        /**
         * Given a char buffer, decodes all possible messages in the buffer and
         * handles each one accordingly.
         * @param buffer Character buffer, which should be obtained from
         *               oscpkt::UdpSocket#buffer
         */
        void handle_message(std::vector<char> buffer);

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
         * Handles message objects.  This is the function that handle_message
         * actually calls to act upon every message it decodes.  You can
         * override it in subclasses to provide different behavior.
         * @param msg pointer to message object
         */
        virtual void handle(oscpkt::Message* msg);

    private:
        oscpkt::PacketReader pr;
};

#endif

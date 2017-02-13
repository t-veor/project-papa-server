#ifndef OSC_SENDER_H
#define OSC_SENDER_H

#include "oscpkt.hh"

/**
 * A class for sending OSC messages.
 * Simple wrapper around the oscpkt UDP library to send OSC messages using UDP.
 */
class OSCSender {
    public:
        /**
         * Constructs an OSCSender.
         * @param port the port to send outgoing messages on
         */
        OSCSender(int port);

        /**
         * Send a OSC message.
         * @param m the oscpkt::Message you wish to send
         */
        void sendOSC(oscpkt::Message m);

    private:
        int port;
};

#endif

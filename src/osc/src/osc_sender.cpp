#include "osc_sender.h"
#include "udp.hh"

#include <iostream>

OSCSender::OSCSender(int port) : port(port) {
}

void OSCSender::sendOSC(oscpkt::Message m) {
    oscpkt::UdpSocket sock;
    sock.connectTo("127.0.0.1", port);
    if (!sock.isOk()) {
        std::cerr << "OSC Sender - Error connecting to port" << port << ": "
            << sock.errorMessage() << "\n";
        // TODO: raise some higher exception
    } else {
        oscpkt::PacketWriter pw;
        pw.addMessage(m);
        sock.sendPacket(pw.packetData(), pw.packetSize());
    }
}

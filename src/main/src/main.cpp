#include <iostream>

#include "osc_sender.h"
#include "oscpkt.hh"

int main() {
    OSCSender sender(4557);
    oscpkt::Message m("/run-code");
    m.pushStr("PROJECT_PAPA");
    m.pushStr("live_loop :test do\nplay :c\nsleep 1\nend");
    sender.sendOSC(m);
}

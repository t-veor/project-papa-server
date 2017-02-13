#include <iostream>

#include "osc_sender.h"
#include "oscpkt.hh"

int main() {
    osc_sender sender(4557);
    oscpkt::Message m("/run-code");
    m.pushStr("PROJECT_PAPA");
    m.pushStr("live_loop :test do\nplay :c\nsleep 1\nend");
    sender.send_osc(m);
}

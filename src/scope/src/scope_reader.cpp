#include "scope_reader.h"

scope_reader::scope_reader(int port) : port(port) {
    reconnect();
}

scope_reader::~scope_reader() {
}

void scope_reader::reconnect() {
    shm_client.reset(new server_shared_memory_client(port));
}

stereo_data scope_reader::read_scope(unsigned int scope_num) {
    unsigned int frames;
    scope_buffer_reader reader =
        shm_client->get_scope_buffer_reader(scope_num);

    stereo_data result;
    if (reader.valid()) {
        reader.pull(frames);

        float* data = reader.data();

        for (unsigned int i = 0; i < 2; i++) {
            std::vector<double> channel;

            unsigned int offset = reader.max_frames() * i;
            frames = frames < reader.max_frames() ?
                frames : reader.max_frames();

            for (unsigned j = 0; j < frames; j++) {
                channel.push_back(data[offset+j]);
            }

            result.push_back(channel);
        }
    }

    return result;
}

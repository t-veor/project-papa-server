#ifndef SCOPE_HEADER_H
#define SCOPE_HEADER_H

#include <vector>

#include <server_shm.hpp>

typedef std::vector<std::vector<double> > stereo_data;

class scope_reader {
    public:
        scope_reader(int port = 4556);
        ~scope_reader();

        void reconnect();
        stereo_data read_scope(unsigned int scope_num);

    private:
        std::unique_ptr<server_shared_memory_client> shm_client;
        int port;
};

#endif

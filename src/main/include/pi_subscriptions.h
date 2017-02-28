#ifndef PI_SUBSCRIPTIONS_H
#define PI_SUBSCRIPTIONS_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <atomic>
#include <mutex>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "scope_reader.h"
#include "server.h"

class pi_subscriptions {
    public:
        pi_subscriptions(server* ws, int shm_port=4556) : ws(ws) {
            reader.reset(new scope_reader(shm_port));
        }

        ~pi_subscriptions() {
            stop = true;
            join();
        }

        void update_scopes(std::vector<unsigned int>& new_scopes) {
            scope_mutex.lock();
            scopes = new_scopes;
            scope_mutex.unlock();
        }

        void run() {
            thread = std::thread([this] () {
                while (!stop) {
                    int delay = 16;

                    Document d;
                    d.SetObject();
                    auto& alloc = d.GetAllocator();

                    d.AddMember("message_type", "scope/amp", alloc);

                    Value a;
                    a.SetObject();

                    this->scope_mutex.lock();

                    for (int i = 0; i < scopes.length; i++) {
                        stereo_data data = this->reader->read_scope(scopes[i]);

                        float acc = 0;
                        if (data.size() > 0) {
                            for (size_t j = 0; j < data[0].size(); j++) {
                                acc += data[0][j] * data[0][j];
                            }

                            acc /= data[0].size();
                            acc = sqrt(acc);
                        }

                        a.AddMember(std::to_string(i), acc, alloc);
                    }

                    d.AddMember("data", a, alloc);

                    this->scope_mutex.unlock();

                    StringBuffer buffer;
                    Writer<StringBuffer> writer(buffer);
                    d.Accept(writer);

                    std::string json_string(buffer.GetString());
                    ws->broadcast_message(json_string);

                    #ifdef _WIN32
                    Sleep(delay);
                    #else
                    usleep(delay*1000);
                    #endif
                }
            });
        }

        void join() {
            thread.join();
        }
    private:
        std::atomic<bool> stop;
        std::thread thread;

        std::unique_ptr<scope_reader> reader;
        std::vector<unsigned int> scopes;
        std::mutex scope_mutex;

        server* ws;
}

#endif

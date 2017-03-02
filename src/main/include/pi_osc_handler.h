#ifndef PI_OSC_HANDLER_H
#define PI_OSC_HANDLER_H

#include "osc_handler.h"
#include "server.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

class pi_osc_handler : public osc_handler {
    public:
        pi_osc_handler(std::shared_ptr<server> ws) : ws(ws) {}
        ~pi_osc_handler() {}

    protected:
        bool handle(oscpkt::Message* msg) {
            // call base handler 
            if (osc_handler::handle(msg)) {
                // base handler handled successfull
                // no-op
            }
            else if (msg->match("/log/multi_message")) {
                // Holy cow
                // JSON in C++ is awful
                // TODO: make these messages structs and make serialisation
                // functions for them
                int job_id;
                std::string thread_name;
                std::string runtime;
                int msg_count;

                auto reader = msg->arg();
                reader
                    .popInt32(job_id)
                    .popStr(thread_name)
                    .popStr(runtime)
                    .popInt32(msg_count);

                Document d;
                d.SetObject();
                auto& alloc = d.GetAllocator();

                d.AddMember("message_type", "log/multi_message", alloc);

                Value m;
                m.SetObject();

                m.AddMember("job_id", job_id, alloc);
                m.AddMember("thread_name",
                        Value(thread_name.c_str(), alloc).Move(), alloc);
                m.AddMember("runtime",
                        Value(runtime.c_str(), alloc).Move(), alloc);

                Value json_messages;
                json_messages.SetArray();

                for (int i = 0; i < msg_count; i++) { 
                    Value json_message;
                    json_message.SetObject();
                    int message_type;
                    std::string message_body;
                    reader
                        .popInt32(message_type)
                        .popStr(message_body);

                    json_message.AddMember("type", message_type, alloc);
                    json_message.AddMember("body", 
                            Value(message_body.c_str(), alloc).Move(), alloc);

                    json_messages.PushBack(json_message, alloc);
                }

                m.AddMember("messages", json_messages, alloc);
                d.AddMember("message", m, alloc);

                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                d.Accept(writer);

                std::string json_string(buffer.GetString());
                ws->broadcast_message(json_string);
            }
            else if (msg->match("/log/info")) {
                int style;
                std::string s;
                msg->arg().popInt32(style).popStr(s);

                Document d;
                d.SetObject();
                auto& alloc = d.GetAllocator();

                d.AddMember("message_type", "log/info", alloc);

                Value m;
                m.SetObject();

                m.AddMember("style", style, alloc);
                m.AddMember("body",
                        Value(s.c_str(), alloc).Move(), alloc);

                d.AddMember("message", m, alloc);

                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                d.Accept(writer);

                std::string json_string(buffer.GetString());
                ws->broadcast_message(json_string);
            }
            else if (msg->match("/error")) {
                int job_id;
                int line;
                std::string desc;
                std::string backtrace;

                msg->arg()
                    .popInt32(job_id)
                    .popStr(desc)
                    .popStr(backtrace)
                    .popInt32(line);

                Document d;
                d.SetObject();
                auto& alloc = d.GetAllocator();

                d.AddMember("message_type", "error", alloc);

                Value m;
                m.SetObject();

                m.AddMember("job_id", job_id, alloc);
                m.AddMember("desc",
                        Value(desc.c_str(), alloc).Move(), alloc);
                m.AddMember("backtrace",
                        Value(backtrace.c_str(), alloc).Move(), alloc);
                m.AddMember("line", line, alloc);

                d.AddMember("message", m, alloc);

                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                d.Accept(writer);

                std::string json_string(buffer.GetString());
                ws->broadcast_message(json_string);
            }
            else if (msg->match("/syntax_error")) {
                int job_id;
                int line;
                std::string desc;
                std::string error_line;
                std::string line_num_s;

                msg->arg()
                    .popInt32(job_id)
                    .popStr(desc)
                    .popStr(error_line)
                    .popInt32(line)
                    .popStr(line_num_s);

                Document d;
                d.SetObject();
                auto& alloc = d.GetAllocator();

                d.AddMember("message_type", "syntax_error", alloc);

                Value m;
                m.SetObject();

                m.AddMember("job_id", job_id, alloc);
                m.AddMember("desc",
                        Value(desc.c_str(), alloc).Move(), alloc);
                m.AddMember("error_line",
                        Value(error_line.c_str(), alloc).Move(), alloc);
                m.AddMember("line", line, alloc);
                m.AddMember("line_num_s",
                        Value(line_num_s.c_str(), alloc).Move(), alloc);

                d.AddMember("message", m, alloc);

                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                d.Accept(writer);

                std::string json_string(buffer.GetString());
                ws->broadcast_message(json_string);
            }
            else {
                return false;
            }
            
            return true;
        }

    private:
        std::shared_ptr<server> ws;
};

#endif

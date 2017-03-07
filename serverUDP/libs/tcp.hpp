#ifndef __TCP__HPP__
#define __TCP__HPP__

//Librerias de IncludeOS
#include <os>
#include <net/inet4>

//Mis Librerias
#include "net.hpp"
#include "init.hpp"

using Connection_ptr = net::tcp::Connection_ptr;
using Disconnect = net::tcp::Connection::Disconnect;

namespace octopus{


    class octoTCPserver : public octoNet{
    private:
        server_t* server;

    public:
        octoTCPserver (uint16_t port = 5050, new_configIPv4_t* nw = defaultNetConfig()){

            this->changeNetConfig(nw);

            auto& tmp = this->inet->tcp().bind(port);

            server = &tmp;
            printf("Server listening: %s \n", this->server->local().to_string().c_str());

        }


        void connect(){

            net::Inet<net::IP4>* tmp = this->inet;

            server->on_connect(
            [tmp] (Connection_ptr client) {
                  printf("Connected [Client]: %s\n", client->to_string().c_str());

                  client->on_read(1024, [client](auto buf, size_t n) {
                      std::string data{ (char*)buf.get(), n };


                      client->write(data + "#");
                  });

                  client->on_disconnect([client](Connection_ptr, Disconnect reason) {
                      printf("Disconnected [Client]: %s\n", reason.to_string().c_str());
                  });

            });

        }


        virtual ~octoTCPserver (){}
    };







    class octoTCPclient {
    private:
        /* data */

    public:
        octoTCPclient (){}
        virtual ~octoTCPclient (){}
    };

}


#endif

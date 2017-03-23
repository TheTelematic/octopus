#ifndef __TCP__HPP__
#define __TCP__HPP__

//Librerias de IncludeOS
#include <os>
#include <net/inet4>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//Mis Librerias
#include "net.hpp"
#include "init.hpp"

using Connection_ptr = net::tcp::Connection_ptr;
using Disconnect = net::tcp::Connection::Disconnect;

namespace octopus{


    class octoTCPserver : public octoNet{
    private:
        TCPserver_t* server;

    public:
        octoTCPserver (uint16_t port = 5050, new_configIPv4_t* nw = defaultNetConfig()) : octoNet(nw){

            //this->changeNetConfig(nw);

            auto& tmp = this->inet->tcp().bind(port);

            server = &tmp;
            printf("Server listening: %s \n", this->server->local().to_string().c_str());

        }


        void wait_connections(){

            net::Inet<net::IP4>* tmp = this->inet;

            server->on_connect(
            [tmp] (Connection_ptr client) {
                  printf("Connected [Client]: %s\n", client->to_string().c_str());

                  net::tcp::Socket destination{ { 10,0,0,3 } , 5051};

                  auto socket = tmp->tcp().connect(destination);
                  socket->on_connect(
                      [client] (Connection_ptr dest) {
                          printf("Connected [Socket]: %s\n", dest->to_string().c_str());

                          dest->on_read(1024, [client](auto buf, size_t n) {
                              std::string data{ (char*)buf.get(), n };
                              printf("Recibido del socket TCP dest -> %s\n", data.c_str());

                              client->write(data + "> ");
                            });

                          client->on_read(1024, [dest](auto buf, size_t n) {
                              std::string data{ (char*)buf.get(), n };

                              printf("Recibido del socket TCP cliente -> %s\n", data.c_str());
                              dest->write(data + "#");
                          });

                          client->on_disconnect([client](Connection_ptr, Disconnect reason) {
                              printf("Disconnected [Client]: %s\n", reason.to_string().c_str());
                          });

                          dest->on_disconnect([dest](Connection_ptr, Disconnect reason) {
                              printf("Disconnected [Dest]: %s\n", reason.to_string().c_str());
                          });
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

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
        TCPserver_t* server;

    public:
        octoTCPserver (uint16_t port = 5050, new_configIPv4_t* nw = defaultNetConfig()) : octoNet(nw){

            //this->changeNetConfig(nw);

            auto& tmp = this->inet->tcp().bind(port);

            server = &tmp;
            printf("Server listening: %s \n", this->server->local().to_string().c_str());

        }

        TCPserver_t* getSocket(){
            return server;
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

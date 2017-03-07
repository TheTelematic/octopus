#ifndef __UDP__HPP__
#define __UDP__HPP__

//Librerias de IncludeOS
#include <os>
#include <list>
#include <net/inet4>
#include <timers>

//Mis Librerias
#include "net.hpp"
#include "init.hpp"


namespace octopus{

    class octoUDPserver : public octoNet{

    public:
        octoUDPserver (new_configIPv4_t* nw = defaultNetConfig()) : octoNet(nw){

            //this->changeNetConfig(nw);

            auto& tmp = this->inet->udp().bind(DISCOVER_PORT);

            discoverSock = &tmp;
            printf("Server listening on discover port %d \n", DISCOVER_PORT);

            auto& tmp2 = this->inet->udp().bind(PUBLISHER_PORT);

            publisherSock = &tmp2;
            printf("Server listening on publisher port %d \n", PUBLISHER_PORT);

            auto& tmp3 = this->inet->udp().bind(SUSCRIBER_PORT);

            suscriberSock = &tmp3;
            printf("Server listening on suscriber port %d \n", SUSCRIBER_PORT);

        }

        void run(){

            trumpetServer();

            discoverSock.on_read(
              [&sock](
                UDP::addr_t addr,
                UDP::port_t port,
                const char* data,
                size_t len
              )
              {
                 std::string strdata(data, len);
                 CHECK(1, "Getting UDP data from %s:  %d -> %s",
                       addr.str().c_str(), port, strdata.c_str());
               }


        }


        virtual ~octoUDPserver (){

        }

    private:
        UDPserver_t* discoverSock;
        UDPserver_t* publisherSock;
        UDPserver_t* suscriberSock;


        void trumpetServer(){

            auto myIP = this->getIP();
            auto broadcast = this->getBROADCAST();

            size_t myIP_l = std::strlen(myIP);

            discoverSock->sendto(broadcast, DISCOVER_PORT, myIP, myIP_l);
        }

    };


}




#endif

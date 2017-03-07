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
    private:
        UDPserver_t* discoverSock;
        UDPserver_t* publisherSock;
        UDPserver_t* suscriberSock;

    public:
        octoUDPserver (new_configIPv4_t* nw = defaultNetConfig()) : octoNet(nw){

            //this->changeNetConfig(nw);

            auto& tmp = this->inet->udp().bind(5085);

            discoverSock = &tmp;
            printf("Server listening on discover port 5085 \n");

            auto& tmp2 = this->inet->udp().bind(5065);

            publisherSock = &tmp2;
            printf("Server listening on publisher port 5065 \n");

            auto& tmp3 = this->inet->udp().bind(5075);

            suscriberSock = &tmp3;
            printf("Server listening on suscriber port 5075 \n");

        }




        virtual ~octoUDPserver (){

        }
    };


}




#endif

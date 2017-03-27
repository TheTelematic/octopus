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
#include "constans.hpp"


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



        void trumpetServer(){

            IPv4_t myIP;
            this->getIP(myIP);

            broadcast_t broadcast;
            this->getBROADCAST(broadcast);

            //size_t myIP_l = sizeof(myIP);

            printf("Sending discovering to: %d.%d.%d.%d:%d\n", broadcast[0], broadcast[1], broadcast[2], broadcast[3], DISCOVER_PORT);

            std::string ip = "";

            ip += std::to_string(myIP[0]) + ".";
            ip += std::to_string(myIP[1]) + ".";
            ip += std::to_string(myIP[2]) + ".";
            ip += std::to_string(myIP[3]);

            discoverSock->sendto({broadcast[0], broadcast[1], broadcast[2], broadcast[3]}, DISCOVER_PORT, ip.c_str(), sizeof(ip));
        }

        virtual ~octoUDPserver (){

        }

        UDPserver_t* getDS(){
            return this->discoverSock;
        }
        UDPserver_t* getPS(){
            return this->publisherSock;
        }
        UDPserver_t* getSS(){
            return this->suscriberSock;
        }

    private:
        UDPserver_t* discoverSock;
        UDPserver_t* publisherSock;
        UDPserver_t* suscriberSock;




    };


}




#endif

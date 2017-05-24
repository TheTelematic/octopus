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

#include <cassert>


namespace octopus{

    class octoUDPserver : public octoNet{

    public:
        /*octoUDPserver (new_configIPv4_t* nw = defaultNetConfig()) : octoNet(nw){


            auto& tmp = this->inet->udp().bind(DISCOVER_PORT);

            discoverSock = &tmp;
            printf("Server listening on discover port %d \n", DISCOVER_PORT);

            auto& tmp2 = this->inet->udp().bind(PUBLISHER_PORT);

            publisherSock = &tmp2;
            printf("Server listening on publisher port %d \n", PUBLISHER_PORT);

            auto& tmp3 = this->inet->udp().bind(SUSCRIBER_PORT);

            suscriberSock = &tmp3;
            printf("Server listening on suscriber port %d \n", SUSCRIBER_PORT);

        }*/

        octoUDPserver () : octoNet(){

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


        void announceServer(){
            if( !octopus::networkConfigured ){

                std::cout << "-*Can't announce server because the network isn't configured*-" << '\n';

            }else{
                assert(discoverSock != nullptr);
                //printf("Announcing the server...\n");
                ip4_t myIP = discoverSock->local_addr();

                broadcast_t broadcast;
                broadcast[0] = 255;
                broadcast[1] = 255;
                broadcast[2] = 255;
                broadcast[3] = 255;
                //this->getBROADCAST(broadcast);

                //size_t myIP_l = sizeof(myIP);

                printf("Sending discovering to: %d.%d.%d.%d:%d (%s)\n", broadcast[0], broadcast[1], broadcast[2], broadcast[3], DISCOVER_PORT, myIP.to_string().c_str());
                fflush(stdout);

                //std::string ip = "";

                /*ip += std::to_string(myIP[0]) + ".";
                ip += std::to_string(myIP[1]) + ".";
                ip += std::to_string(myIP[2]) + ".";
                ip += std::to_string(myIP[3]);
                ip += "\0";*/

                std::string buffer = myIP.to_string();

                discoverSock->sendto({broadcast[0], broadcast[1], broadcast[2], broadcast[3]}, DISCOVER_PORT, buffer.c_str(), buffer.size());
            }

        }

        virtual ~octoUDPserver (){

        }

        UDPserver_t* getDS(){
            assert(discoverSock != nullptr);

            return this->discoverSock;
        }
        UDPserver_t* getPS(){
            assert(publisherSock != nullptr);

            return this->publisherSock;
        }
        UDPserver_t* getSS(){
            assert(suscriberSock != nullptr);

            return this->suscriberSock;
        }

    private:
        UDPserver_t* discoverSock;
        UDPserver_t* publisherSock;
        UDPserver_t* suscriberSock;




    };


}




#endif

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
    private:
        UDPserver_t* discoverSock;
        UDPserver_t* publisherSock;
        UDPserver_t* suscriberSock;

        discovered_servers_t discovered_servers;

        static octoUDPserver *singleton_instance;

    protected:
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

    public:

        static octoUDPserver* getInstance(){

            if(singleton_instance == nullptr) singleton_instance = new octoUDPserver;

            return singleton_instance;

        }


        bool announceServer(){
            if( !octopus::networkConfigured ){

                std::cout << "-*Can't announce server because the network isn't configured*-" << '\n';
                return false;

            }else{
                assert(discoverSock != nullptr);
                //printf("Announcing the server...\n");
                ip4_t myIP = discoverSock->local_addr();

                broadcast_t broadcast;
                broadcast[0] = BROADCAST_ADDRESS[0];
                broadcast[1] = BROADCAST_ADDRESS[1];
                broadcast[2] = BROADCAST_ADDRESS[2];
                broadcast[3] = BROADCAST_ADDRESS[3];

                printf("Sending discovering to: %d.%d.%d.%d:%d (%s)\n", broadcast[0], broadcast[1], broadcast[2], broadcast[3], DISCOVER_PORT, myIP.to_string().c_str());
                fflush(stdout);

                std::string buffer = myIP.to_string();

                discoverSock->sendto({broadcast[0], broadcast[1], broadcast[2], broadcast[3]}, DISCOVER_PORT, buffer.c_str(), buffer.size());

                return true;
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


        bool addServerAddr(ds_addrs_t addr){
            if(discovered_servers.empty()){
                discovered_servers.push_back(addr);
                return true;
            }

            for(iterator_ds_t it = discovered_servers.begin(); it != discovered_servers.end(); it++ ){
                if(*it == addr){
                    return false;
                }
            }

            discovered_servers.push_back(addr);
            return true;

        }

        void removeServerAddr(ds_addrs_t addr){

            discovered_servers.remove(addr);
        }

        discovered_servers_t getServerAddresses(){
            return discovered_servers;
        }

        // TODO
        void testAliveServers(){


        }


    };


}




#endif

#ifndef __UDP__HPP__
#define __UDP__HPP__

//Librerias de IncludeOS
#include <os>
#include <list>
#include <net/inet4>
#include <timers>

//Mis Librerias
#include "net.hpp"
#include "servers.hpp"

#include <cassert>


namespace octopus{

    class octoUDPserver : public octoNet{
    private:
        DiscoverServer *discoverer;
        UDPsocket_t* publisherSock;
        SuscriberServer* suscriber;

        static octoUDPserver *singleton_instance;


        std::string getStrIpAddr(const ds_addrs_t addr)const{

            return addr;

        }



    protected:
        octoUDPserver () : octoNet(){

            auto& tmp = this->inet->udp().bind(DISCOVER_PORT);

            discoverer = new DiscoverServer(&tmp);

            printf("Server listening on discover port %d \n", DISCOVER_PORT);


            auto& tmp2 = this->inet->udp().bind(PUBLISHER_PORT);

            publisherSock = &tmp2;
            printf("Server listening on publisher port %d \n", PUBLISHER_PORT);

            auto& tmp3 = this->inet->udp().bind(SUSCRIBER_PORT);

            suscriber = new SuscriberServer(&tmp3);
            printf("Server listening on suscriber port %d \n", SUSCRIBER_PORT);

        }

    public:

        static octoUDPserver* getInstance(){

            if(singleton_instance == nullptr) singleton_instance = new octoUDPserver;

            return singleton_instance;

        }




        virtual ~octoUDPserver (){

        }

        UDPsocket_t* getDS(){
            assert(discoverer != nullptr);

            return discoverer->getSocket();
        }
        UDPsocket_t* getPS(){
            assert(publisherSock != nullptr);

            return this->publisherSock;
        }
        UDPsocket_t* getSS(){
            assert(suscriber != nullptr);

            return suscriber->getSocket();
        }


        bool addServerAddr(ds_addrs_t addr){
            return discoverer->addServerAddr(addr);

        }

        void removeServerAddr(ds_addrs_t addr){

            discoverer->removeServerAddr(addr);
        }

        discovered_servers_t getServerAddresses(){
            return discoverer->getServerAddresses();
        }

        bool announceServer(){
            return discoverer->announceServer();
        }

        // TODO
        void testAliveServers(){


        }

        bool suscribe(topic_t topic){

            return suscriber->suscribe(topic, discoverer->getServerAddresses());

        }


    };


}




#endif

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

    class GenericUDPServer{
    private:
        UDPsocket_t *socket;

    public:
        GenericUDPServer(UDPsocket_t *socket){
            this->socket = socket;
        }

        UDPsocket_t* getSocket(){
            return socket;
        }

        ip4_t getLocalAddr(){
            return socket->local_addr();
        }

        std::string getLocalAddrStr(){
            return getLocalAddr().to_string();
        }

        void sendto(ip4_t dest, uint16_t port, const char *buffer, const int size){

            socket->sendto(dest, port, buffer, size);

        }

    };


    class DiscoverServer : public GenericUDPServer{
    private:

        discovered_servers_t discovered_servers;


    public:
        DiscoverServer(UDPsocket_t *socket) : GenericUDPServer(socket){}

        bool announceServer(){
            if( !octopus::networkConfigured ){

                std::cout << "-*Can't announce server because the network isn't configured*-" << '\n';
                return false;

            }else{
                UDPsocket_t *discoverSock = this->getSocket();
                assert(discoverSock != nullptr);

                ip4_t myIP = this->getLocalAddr();

                printf("Sending discovering - (%s)\n", myIP.to_string().c_str());
                fflush(stdout);

                std::string buffer = myIP.to_string();

                this->sendto(BROADCAST_ADDRESS, DISCOVER_PORT, buffer.c_str(), buffer.size());

                return true;
            }

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


    };




    class octoUDPserver : public octoNet{
    private:
        DiscoverServer *discoverer;
        UDPsocket_t* publisherSock;
        UDPsocket_t* suscriberSock;

        static octoUDPserver *singleton_instance;


        std::string getStrIpAddr(const ds_addrs_t addr)const{

            return addr;

        }

        bool sendSuscription(const char* topic, int length, ds_addrs_t addr){

            ip4_t ip(addr);


            suscriberSock->sendto(ip, SUSCRIBER_PORT, topic, length + 1);

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

            suscriberSock = &tmp3;
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
            assert(suscriberSock != nullptr);

            return this->suscriberSock;
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

        /*
        bool suscribe(const char* topic){
            if( !octopus::networkConfigured ){

                std::cout << "-*Can't suscribe to the topic because the network isn't configured*-" << '\n';
                return false;

            }else{
                int length = strlen(topic);
                assert( length != 0 );

                if(discovered_servers.size() == 0){
                    std::cout << "-*Can't suscribe to the topic because there are no servers to send it*-" << '\n';
                    return false;
                }


                assert(suscriberSock != nullptr);
                for(iterator_ds_t it = discovered_servers.begin(); it != discovered_servers.end(); it++ ){

                    std::string receiver = getStrIpAddr(*it);

                    printf("Sending suscription of %s to %s -> ", topic, receiver.c_str() );

                    if( !sendSuscription(topic, length, receiver)){
                        printf("FAILED\n");

                        //TODO: Return false ?
                    }else{
                        printf("OK\n");
                    }


                }


            }

            return true;

        }

        bool addSuscription(){

        }
        */


    };


}




#endif

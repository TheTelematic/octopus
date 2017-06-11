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
        PublisherServer* publisher;
        SuscriberServer* suscriber;


        std::string getStrIpAddr(const ds_addrs_t addr)const{

            return addr;

        }



    public:
        octoUDPserver () : octoNet(){

            auto& tmp = this->inet->udp().bind(DISCOVER_PORT);

            discoverer = new DiscoverServer(&tmp);

            printf("Server listening on discover port %d \n", DISCOVER_PORT);


            auto& tmp2 = this->inet->udp().bind(PUBLISHER_PORT);

            publisher = new PublisherServer(&tmp2);
            printf("Server listening on publisher port %d \n", PUBLISHER_PORT);

            auto& tmp3 = this->inet->udp().bind(SUSCRIBER_PORT);

            suscriber = new SuscriberServer(&tmp3);
            printf("Server listening on suscriber port %d \n", SUSCRIBER_PORT);

        }




        virtual ~octoUDPserver (){

        }

        UDPsocket_t* getDS(){
            assert(discoverer != nullptr);

            return discoverer->getSocket();
        }
        UDPsocket_t* getPS(){
            assert(publisher != nullptr);

            return publisher->getSocket();
        }
        UDPsocket_t* getSS(){
            assert(suscriber != nullptr);

            return suscriber->getSocket();
        }


        bool addServerAddr(ds_addrs_t addr){
            assert(discoverer != nullptr);
            return discoverer->addServerAddr(addr);

        }

        void removeServerAddr(ds_addrs_t addr){
            assert(discoverer != nullptr);

            discoverer->removeServerAddr(addr);
        }

        discovered_servers_t getServerAddresses(){
            assert(discoverer != nullptr);
            return discoverer->getServerAddresses();
        }

        bool announceServer(){
            assert(discoverer != nullptr);
            return discoverer->announceServer();
        }



        bool suscribe(topic_t topic){
            if(suscriber == nullptr) {
                printf("THAT HAPPENED D:\n" );
                return false;
            }
            assert(suscriber != nullptr);
            //printf("Suscribing/////\n");
            return suscriber->suscribe(topic);
            //return true;
        }

        bool addSuscription(size_t value_hash){
            assert(publisher != nullptr);
            return publisher->addSuscription(value_hash);

        }




        bool publish(topic_t topic, topic_message_t message){


            assert(publisher != nullptr);

            //printf("Publishing the message (%s) of %s\n",message.c_str(), topic.c_str());

            return publisher->publish(topic, message);

        }

        size_t create_topic(topic_t topic){
            assert(publisher != nullptr);

            printf("Creating the topic %s-\n", topic.c_str());

            size_t value_hash = publisher->create_topic(topic);

            if( value_hash == 0) printf("Already exists\n");
            printf("Created. Its hash is:\n");
            printf("%zu\n", value_hash);

            return value_hash;
        }

        void announceTopicCreated(topic_t topic){
            assert(publisher != nullptr);

            //printf("Announcing the topic %s\n",topic.c_str());

            publisher->announceTopicCreated(topic);

        }

        void savePublisher(std::string addr, size_t value_hash){

            assert(suscriber != nullptr);



            if(suscriber->addPublisher(addr, value_hash)) printf("Saved the publisher...\n");
            else {
                //printf("(already exists)\n");
            }
        }


        void processPub(size_t value_hash, topic_message_t message){

            assert(suscriber != nullptr);

            suscriber->processPub(value_hash, message);


        }

    };


}




#endif

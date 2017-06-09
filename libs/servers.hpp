#ifndef __SERVERS__HPP__
#define __SERVERS__HPP__

#include "types.hpp"
#include "constans.hpp"
#include "message.hpp"
#include "protocol_messages.hpp"

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

        std::string getStrIpAddr(const ds_addrs_t addr){

            return addr;

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

    class SuscriberServer : public GenericUDPServer{

    private:



        std::string topic_t2str(const topic_t topic){

            return topic;
        }

        int sizeTopic(topic_t topic){
            return topic.size();
        }

        void sendSuscription(topic_t topic, ds_addrs_t addr){
            //FIXME TO THE NEW PROTOCOL
            /*ip4_t ip(addr);

            this->sendto(ip, SUSCRIBER_PORT, topic_t2str(topic).c_str(), sizeTopic(topic));*/

        }

        void addNewtopic(ds_addrs_t ip_server, topic_t topic){
            //FIXME TO THE NEW PROTOCOL
            /*topic_list_item_t new_topic;

            new_topic.topic = topic;
            new_topic.suscribed_servers.push_back(ip_server);

            topic_list.push_back(new_topic);*/
        }


    public:
        SuscriberServer(UDPsocket_t *socket) : GenericUDPServer(socket){}

        bool suscribe(topic_t topic, discovered_servers_t discovered_servers){
            //FIXME TO THE NEW PROTOCOL
            /*if( !octopus::networkConfigured ){

                std::cout << "-*Can't suscribe to the topic because the network isn't configured*-" << '\n';
                return false;

            }else{

                assert( sizeTopic(topic) != 0 );

                if(discovered_servers.size() == 0){
                    std::cout << "-*Can't suscribe to the topic because there are no servers to send it*-" << '\n';
                    return false;
                }else{
                    std::cout << "Suscribing..." << '\n';
                }

                UDPsocket_t *suscriberSock = this->getSocket();
                assert(suscriberSock != nullptr);
                for(iterator_ds_t it = discovered_servers.begin(); it != discovered_servers.end(); it++ ){

                    std::string receiver = getStrIpAddr(*it);

                    printf("Sending suscription of %s to %s -> ", topic_t2str(topic).c_str(), receiver.c_str() );

                    sendSuscription(topic, receiver);

                    printf("OK\n");


                }


            }*/

            return true;

        }

        bool addSuscription(ds_addrs_t ip_server, topic_t topic){
            //FIXME TO THE NEW PROTOCOL

            /*


            if(topic_list.empty()){
                addNewtopic(ip_server, topic);

                return true;
            }

            for(iterator_tl_t it = topic_list.begin(); it != topic_list.end(); it++ ){
                if(it->topic == topic){

                    return addServer2Topic(&(*it), ip_server);

                }
            }

            addNewtopic(ip_server, topic);
            return true;*/
        }

        topic_list_t getTopicsList(){
            //FIXME TO THE NEW PROTOCOL
            //return topic_list;
        }


        discovered_servers_t getServersOfTopic(topic_t topic){
            //FIXME TO THE NEW PROTOCOL
            /*

            if(topic_list.empty()){
                discovered_servers_t tmp;
                return tmp;
            }

            for(iterator_tl_t it = topic_list.begin(); it != topic_list.end(); it++ ){

                if(it->topic == topic){
                    return it->suscribed_servers;
                }
            }

            std::cout << "AQUI NO DEBERIA LLEGAR" << '\n';

            //assert(1);
            discovered_servers_t tmp;
            return tmp;*/
        }


    };


    class PublisherServer : public GenericUDPServer{
    private:

        topic_list_t created_topics;

        void addNewTopic(topic_t topic){
            topic_list_item_t new_topic;

            new_topic.topic = topic;
            new_topic.any_server_suscribed = false;

            this->created_topics.push_back(new_topic);
        }

    public:
        PublisherServer(UDPsocket_t *socket) : GenericUDPServer(socket){}

        bool publish(topic_t topic, topic_message_t message, discovered_servers_t suscribed_servers){

            if(suscribed_servers.empty()){
                std::cout << "No suscribed servers to publish" << '\n';
                return false;
            }

            for(iterator_ds_t it = suscribed_servers.begin(); it != suscribed_servers.end(); it++ ){

                ip4_t addr(*it);

                Message m(topic, message);

                m.build();

                std::string request = m.getRequest();

                this->sendto(addr, PUBLISHER_PORT, request.c_str(), request.size());

            }

            return true;
            std::cout << "PUBLISHED" << '\n';
        }


        size_t create_topic(topic_t topic){

            if(this->created_topics.empty()){
                addNewTopic(topic);

            }else{
                for(iterator_tl_t it = this->created_topics.begin(); it != this->created_topics.end(); it++ ){
                    if(it->topic == topic){
                        std::cout << "Topic already exists" << '\n';
                        return 0;
                    }

                }

                addNewTopic(topic);
            }






            return doHash(topic);

        }

        void announceTopicCreated(topic_t topic){


            std::string announce = getMessageTopicCreated(topic);

            this->sendto(BROADCAST_ADDRESS, PUBLISHER_PORT, announce.c_str(), announce.size());

        }

    };
}

#endif





















//

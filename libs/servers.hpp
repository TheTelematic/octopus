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
        GenericUDPServer(){socket = nullptr;}

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

        publishers_list_t publishers_list;

        int sizeTopic(topic_t topic){
            return topic.size();
        }

        void sendSuscription(size_t value_hash, std::list<std::string> publishers){

            if(publishers.size() == 0){
                printf("THERE NO ARE PUBLISHERS\n");
                return;
            }
            printf("The hash of the topic for the subscription is %zu\n", value_hash);
            std::string message__ = getMessageSuscription(value_hash);
            printf("Message to send: -%s-\n", message__.c_str());
            for(iterator_string_t it = publishers.begin(); it != publishers.end(); it++){
                printf("it: %d addr: %s-\n",it, (*it).c_str() );
                ip4_t ip(*it);
                printf("IP: %s\nMessage: %s\nSize message: %lu\n",ip.to_string().c_str(), message__.c_str(), message__.size() );

                //if(this == nullptr) printf("WHAT HAPPENED?? D:\n" );
                this->sendto(ip, SUSCRIBER_PORT, message__.c_str() , message__.size());

            }

        }

        void sendUnsuscription(topic_t topic, std::list<std::string> publishers){


            std::string message = getMessageUnsuscription(topic);
            for(iterator_string_t it2 = publishers.begin(); it2 != publishers.end(); it2++){
                ip4_t ip(*it2);

                this->sendto(ip, SUSCRIBER_PORT, message.c_str() , message.size());
            }

        }

        void addNewtopic(std::string addr, size_t value_hash){

            publisher_item_list_t new_item;

            new_item.hash_of_topic = value_hash;

            //std::list<std::string> tmp;
            new_item.addrs_publisher.push_back(addr);
            new_item.suscribed = false;


            publishers_list.push_back(new_item);
        }

        bool savePublisher(std::string addr, size_t value_hash){

            if(publishers_list.empty()){
                addNewtopic(addr, value_hash);

                return true;
            }else{


                for(iterator_publishers_t it = publishers_list.begin(); it != publishers_list.end(); it++ ){
                    if(it->hash_of_topic == value_hash){

                        for(iterator_string_t it2 = it->addrs_publisher.begin(); it2 != it->addrs_publisher.end(); it2++ ){

                            if(*it2 == addr){
                                return false;
                            }

                        }

                        it->addrs_publisher.push_back(addr);
                        if(it->suscribed) sendSuscription(value_hash, it->addrs_publisher);
                        return true;
                    }
                }

                addNewtopic(addr, value_hash);

                return true;
            }

        }

        void processMessage(size_t value_hash, topic_message_t message){

            printf("-Publication processed-\n Message: %s\nTopic (hashed): %zu\n",message.c_str(), value_hash );

        }


    public:

        SuscriberServer(UDPsocket_t *socket) : GenericUDPServer(socket){}

        bool suscribe(topic_t topic){
            if( !octopus::networkConfigured ){

                std::cout << "-*Can't suscribe to the topic because the network isn't configured*-" << '\n';
                return false;

            }else{

                assert( sizeTopic(topic) != 0 );

                if(publishers_list.size() == 0){
                    std::cout << "-*Can't suscribe to the topic because there are no publisher servers to send it*-" << '\n';
                    return false;
                }
                printf("The size of the publishers_list is %lu\n", publishers_list.size());

                size_t value_hash = doHash(topic);
                for(iterator_publishers_t it = publishers_list.begin(); it != publishers_list.end(); it++  ){

                    if(it->hash_of_topic == value_hash){
                        sendSuscription(doHash(topic), it->addrs_publisher);
                        it->suscribed = true;
                        printf("OK\n");
                        return true;
                    }

                }



                printf("There nobody who publish that topic\n");

                return false;
            }
        }





        bool addPublisher(std::string addr, size_t value_hash){

            return savePublisher(addr, value_hash);

        }

        void processPub(size_t value_hash, topic_message_t message){

            for(iterator_publishers_t it = publishers_list.begin(); it != publishers_list.end(); it++  ){
                if(it->hash_of_topic == value_hash){
                    if(it->suscribed){
                        processMessage(value_hash, message);
                    }
                    return;
                }
            }

        }


        void unsuscribe(topic_t topic){

            if(publishers_list.size() == 0){
                std::cout << "-*Can't unsuscribe to the topic because there are no publisher servers to send it*-" << '\n';
                return ;
            }

            size_t value_hash = doHash(topic);
            if(publishers_list.size() == 1){
                std::cout << "Only one publisher" << '\n';


                if(publishers_list.begin()->hash_of_topic == value_hash){
                    publishers_list.begin()->suscribed = false;

                    sendUnsuscription(topic, publishers_list.begin()->addrs_publisher);
                }
            }else{
                std::cout << "More than one publisher - " << publishers_list.size() << '\n';
                for(iterator_publishers_t it = publishers_list.begin(); it != publishers_list.end(); it++  ){

                    if(it->hash_of_topic == value_hash){
                        it->suscribed = false;

                        sendUnsuscription(topic, it->addrs_publisher);
                    }

                }
            }

        }


        void removePublisher(std::string addr, size_t value_hash){
            if(publishers_list.empty()){
                printf("No publishers\n" );
                return;
            }


            for(iterator_publishers_t it = publishers_list.begin(); it != publishers_list.end(); it++ ){
                if(it->hash_of_topic == value_hash){

                    for(iterator_string_t it2 = it->addrs_publisher.begin(); it2 != it->addrs_publisher.end(); it2++ ){

                        if(*it2 == addr){
                            it->addrs_publisher.erase(it2);
                            printf("Publisher removed\n" );
                            return;
                        }

                    }

                    printf("That publisher doesn't exist for this topic\n");
                    return ;
                }
            }

            printf("Anybody publish for this topic\n");

        }


    };


    class PublisherServer : public GenericUDPServer{
    private:

        topic_list_t created_topics;
        struct parameters_to_timer{
            topic_t topic;
            UDPsocket_t* socket;
        };

        void addNewTopic(topic_t topic){
            topic_list_item_t new_topic;

            new_topic.hash_of_topic = doHash(topic);
            new_topic.any_server_suscribed = 0;


            parameters_to_timer params;
            params.topic = topic;
            params.socket = this->getSocket();


            // Publish to the rest that exists that topic with the UUID(hash of the name)
            new_topic.timer_id = Timers::periodic(1s, 5s, [params] (auto) {
                std::string announce = getMessageTopicCreated(params.topic);

                params.socket->sendto(BROADCAST_ADDRESS, PUBLISHER_PORT, announce.c_str(), announce.size());
            });

            this->created_topics.push_back(new_topic);
        }


        void sendTopicRemoved(topic_t topic){

            std::string announce = getMessageTopicRemoved(topic);

            this->sendto(BROADCAST_ADDRESS, PUBLISHER_PORT, announce.c_str(), announce.size());

        }

    public:
        PublisherServer(UDPsocket_t *socket) : GenericUDPServer(socket){}

        bool publish(topic_t topic, topic_message_t message){

            //printf("TOPIC: %s-\n", topic.c_str());
            //printf("MESSAGE: %s-%lu-%lu\n", message.c_str(), message.size(), message.length());
            size_t value_hash = doHash(topic);

            //printf("TARGET hash topic: %zu\n", value_hash);
            for(iterator_tl_t it = this->created_topics.begin(); it != this->created_topics.end(); it++ ){
                //printf("Saved hash topic: %zu\n", it->hash_of_topic);
                if(it->hash_of_topic == value_hash){
                    if(it->any_server_suscribed > 0){

                        std::string message_ = getMessagePublication(topic, message);

                        this->sendto(BROADCAST_ADDRESS, PUBLISHER_PORT, message_.c_str(), message_.size());

                        return true;

                    }else{
                        printf("Any server suscribed to this topic\n" );
                        return false;
                    }
                }
            }
            printf("The topic doesn't exist\n" );
            return false;
        }

        bool addSuscription(size_t value_hash){
            for(iterator_tl_t it = this->created_topics.begin(); it != this->created_topics.end(); it++ ){

                if(it->hash_of_topic == value_hash){
                    it->any_server_suscribed++;
                    return true;
                }

            }


            return false;
        }


        size_t create_topic(topic_t topic){

            if(this->created_topics.empty()){
                addNewTopic(topic);

            }else{
                size_t value_hash = doHash(topic);
                for(iterator_tl_t it = this->created_topics.begin(); it != this->created_topics.end(); it++ ){
                    if(it->hash_of_topic == value_hash){
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




        void remove_topic(topic_t topic){

            if(this->created_topics.empty()) return;

            size_t value_hash = doHash(topic);
            for(iterator_tl_t it = this->created_topics.begin(); it != this->created_topics.end(); it++ ){
                if(it->hash_of_topic == value_hash){
                    Timers::stop(it->timer_id);
                    this->created_topics.erase(it);
                    printf("Topic %s has been removed\n",topic.c_str() );
                    sendTopicRemoved(topic);
                    return;
                }
            }

            printf("Topic %s doesn't exist\n",topic.c_str() );
        }


        void removeSuscription(size_t value_hash){
            for(iterator_tl_t it = this->created_topics.begin(); it != this->created_topics.end(); it++ ){

                if(it->hash_of_topic == value_hash){

                    if(it->any_server_suscribed > 0){
                        it->any_server_suscribed--;
                        printf("Server unsuscribed\n");
                    }
                }

            }
        }

    };
}

#endif





















//

#ifndef __SERVERS__HPP__
#define __SERVERS__HPP__

#include "types.hpp"
#include "constans.hpp"

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

        topic_list_t topic_list;



        const char* topic_t2charptr(const topic_t topic){

            return topic.c_str();
        }

        int sizeTopic(topic_t topic){
            return topic.size();
        }

        void sendSuscription(topic_t topic, ds_addrs_t addr){

            ip4_t ip(addr);

            this->sendto(ip, SUSCRIBER_PORT, topic_t2charptr(topic), sizeTopic(topic));

        }

        void addNewtopic(ds_addrs_t ip_server, topic_t topic){
            topic_list_item_t new_topic;

            new_topic.topic = topic;
            new_topic.suscribed_servers.push_back(ip_server);

            topic_list.push_back(new_topic);
        }

        void addServer2Topic(topic_list_item_t *item, ds_addrs_t ip_server){

            for(iterator_ds_t it = item->suscribed_servers.begin(); it != item->suscribed_servers.end(); it++ ){
                if(*it == ip_server){

                    return;

                }
            }
            item->suscribed_servers.push_back(ip_server);

        }


    public:
        SuscriberServer(UDPsocket_t *socket) : GenericUDPServer(socket){}

        bool suscribe(topic_t topic, discovered_servers_t discovered_servers){
            if( !octopus::networkConfigured ){

                std::cout << "-*Can't suscribe to the topic because the network isn't configured*-" << '\n';
                return false;

            }else{

                assert( sizeTopic(topic) != 0 );

                if(discovered_servers.size() == 0){
                    std::cout << "-*Can't suscribe to the topic because there are no servers to send it*-" << '\n';
                    return false;
                }

                UDPsocket_t *suscriberSock = this->getSocket();
                assert(suscriberSock != nullptr);
                for(iterator_ds_t it = discovered_servers.begin(); it != discovered_servers.end(); it++ ){

                    std::string receiver = getStrIpAddr(*it);

                    printf("Sending suscription of %s to %s -> ", topic_t2charptr(topic), receiver.c_str() );

                    sendSuscription(topic, receiver);

                    printf("OK\n");


                }


            }

            return true;

        }

        bool addSuscription(ds_addrs_t ip_server, topic_t topic){



            if(topic_list.empty()){
                addNewtopic(ip_server, topic);

                return true;
            }

            for(iterator_tl_t it = topic_list.begin(); it != topic_list.end(); it++ ){
                if(it->topic == topic){

                    addServer2Topic(&(*it), ip_server);

                }
            }

            addNewtopic(ip_server, topic);
            return true;
        }


    };
}

#endif
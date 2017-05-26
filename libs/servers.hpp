#ifndef __SERVERS__HPP__
#define __SERVERS__HPP__ value

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

        std::string getStrIpAddr(const ds_addrs_t addr)const{

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

        bool sendSuscription(const char* topic, int length, ds_addrs_t addr){

            ip4_t ip(addr);


            this->sendto(ip, SUSCRIBER_PORT, topic, length + 1);

        }


    public:
        SuscriberServer(UDPsocket_t *socket) : GenericUDPServer(socket){}

        bool suscribe(const char* topic, discovered_servers_t discovered_servers){
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

                UDPsocket_t *suscriberSock = this->getSocket();
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


    };
}

#endif

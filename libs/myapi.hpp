#ifndef __MYAPI__HPP
#define __MYAPI__HPP
#include "types.hpp"
#include "udp.hpp"

namespace octopus{

    bool new_server = false; // Not quite elegant, but it can work


    bool announceServer(){
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);

        return server->announceServer();
    }


    bool addAddrServer(std::string addr){
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);

        return server->addServerAddr(addr);
    }

    void showIpAddr(ds_addrs_t ip){

        std::cout << ip << '\n';

    }



    void handle_discoversocket_receiver(const char *data, size_t len){
        if(octopus::networkConfigured){

            std::string strdata(data,len);

            CHECK(1, "Discovered new server in #%s#", strdata.c_str());

            if(new_server){
                if(addAddrServer(strdata)){
                    announceServer();
                }
            }else{
                new_server = addAddrServer(strdata);
                if(new_server){
                    announceServer();
                }
            }

        }else{
            std::cout << "**Discovery received, but network isn't configured**" << '\n';
        }
    }


    void tryAnnounceServer(){
        if( !announceServer()){

            Timers::oneshot(1s, [] (auto) {
                tryAnnounceServer();
            });

        }
    }

    void showTable(){

        if (new_server) {
            octoUDPserver* server = octoUDPserver::getInstance();
            assert(server != nullptr);
            discovered_servers_t list_of_addresses = server->getServerAddresses();

            std::cout << "IP ADDRESSES TABLE" << '\n';
            std::cout << "--------------------" << '\n';

            for(iterator_ds_t it = list_of_addresses.begin(); it != list_of_addresses.end(); it++ ){

                showIpAddr(*it);

            }
            std::cout << "--------------------" << '\n';

            new_server = false;
        }

    }

}

#endif

#ifndef __MYAPI__HPP
#define __MYAPI__HPP
#include "types.hpp"
#include "udp.hpp"

namespace octopus{

    static bool new_server = false; // Not quite elegant, but it can work
    static bool update_topics = false;


    bool announceServer(){
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);

        return server->announceServer();
    }




    void addSuscription(net::UDP::addr_t addr, std::string topic){

        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);

        if(server->addSuscription(addr, topic)){
            std::cout << "Suscribed!" << '\n';
            update_topics = true;
        }

    }

    bool addAddrServer(std::string addr){
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);

        if( server->addServerAddr(addr)){
            /*net::UDP::addr_t tmp(addr);
            addSuscription(tmp, KEEPALIVE_TOPIC); // This will have two duplicate list of the discovered servers TODO: FIXME */

            return true;
        }else{
            return false;
        }
    }



    void showIpAddr(ds_addrs_t ip){

        std::cout << ip << '\n';

    }


    void handle_suscribe2topic(topic_t topic);

    void retrySuscription(topic_t topic){
        Timers::oneshot(1s, [topic] (auto) {
            handle_suscribe2topic(topic);
        });
    }


    void handle_discoversocket_receiver(const char *data, size_t len){
        if(octopus::networkConfigured){

            std::string strdata(data,len);

            CHECK(1, "Discovered new server in %s", strdata.c_str());

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

    void handle_suscriptionsocket_receiver(net::UDP::addr_t addr, const char* data, size_t len){
        if(octopus::networkConfigured){

            std::string strdata(data,len);

            CHECK(1, "Suscription of topic %s from %s", strdata.c_str(), addr.to_string().c_str());

            addSuscription(addr, strdata);

        }else{
            std::cout << "**Suscription received, but network isn't configured**" << '\n';
        }
    }

    void handle_suscribe2topic(topic_t topic){
        if(octopus::networkConfigured){

            octoUDPserver* server = octoUDPserver::getInstance();
            assert(server != nullptr);

            if( !server->suscribe(topic) ){
                retrySuscription(topic);
            }


        }else{

            std::cout << "-*Cannot suscribe to topic because the network isn't configured yet.*-" << '\n';
            retrySuscription(topic);

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

    void showTopics(){
        if(update_topics){
            octoUDPserver* server = octoUDPserver::getInstance();
            assert(server != nullptr);

            topic_list_t topics_list = server->getTopicsList();

            std::cout << "TOPICS TABLE" << '\n';
            std::cout << "====================" << '\n';
            for(iterator_tl_t it = topics_list.begin(); it != topics_list.end(); it++ ){

                std::cout << it->topic << '\n';
                std::cout << "- - - - - - - - - " << '\n';

                for(iterator_ds_t it_2 = it->suscribed_servers.begin(); it_2 != it->suscribed_servers.end(); it_2++ ){
                    std::cout << *it_2 << '\n';

                }

                std::cout << "- - - - - - - - - " << '\n';


            }
            std::cout << "====================" << '\n';

            update_topics = false;
        }


    }

}

#endif

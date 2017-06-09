#ifndef __MYAPI__HPP
#define __MYAPI__HPP
#include "types.hpp"
#include "udp.hpp"

namespace octopus{

    static bool new_server = false; // Not quite elegant, but it can work
    static bool update_topics = false;
    static octoUDPserver* __octoUDP_server;


    bool announceServer(){
        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        return server->announceServer();
    }




    void addSuscription(ip4_t addr, topic_t topic){

        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        if(server->addSuscription(addr, topic)){
            std::cout << "Suscribed!" << '\n';
            update_topics = true;
        }

    }

    bool addAddrServer(ds_addrs_t addr){
        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        return server->addServerAddr(addr);
    }



    void showIpAddr(ds_addrs_t ip){

        std::cout << ip << '\n';

    }


    void suscribe_to_topic(topic_t topic);

    void retrySuscription(topic_t topic){
        Timers::oneshot(1s, [topic] (auto) {
            suscribe_to_topic(topic);
        });
    }


    void handle_discoversocket_receiver(const char *data, size_t len){
        if(octopus::networkConfigured){

            std::string strdata(data,len);

            CHECK(1, "Discovered new server in %s", strdata.c_str());

            if(new_server){
                if(addAddrServer(strdata)){
                    announceServer();
                    //suscribe_to_topic(KEEPALIVE_TOPIC);
                }
            }else{
                new_server = addAddrServer(strdata);
                if(new_server){
                    announceServer();
                    //suscribe_to_topic(KEEPALIVE_TOPIC);
                }
            }

        }else{
            std::cout << "**Discovery received, but network isn't configured**" << '\n';
        }
    }

    bool forcePublish(topic_t topic, topic_message_t message);

    void handle_suscriptionsocket_receiver(ip4_t addr, const char* data, size_t len){
        if(octopus::networkConfigured){

            std::string strdata(data,len);

            CHECK(1, "Suscription of topic %s from %s", strdata.c_str(), addr.to_string().c_str());

            addSuscription(addr, strdata);

            forcePublish(strdata, "Hello guys!");

        }else{
            std::cout << "**Suscription received, but network isn't configured**" << '\n';
        }
    }



    void handle_publicationsocket_receiver(ip4_t addr, const char* data, size_t len){
        if(octopus::networkConfigured){

            std::string strdata(data,len);
            //CHECK(1, "Received PUBLICATION: %s", strdata.c_str());
            Message m(strdata);

            m.debuild();

            CHECK(1, "Publication of topic %s from %s: %s", m.getTopic().c_str(), addr.to_string().c_str(), m.getMessage().c_str());

            //TODO: Process the publication

        }else{
            std::cout << "**Cannot do a publication, but network isn't configured**" << '\n';
        }
    }

    void suscribe_to_topic(topic_t topic){
        if(octopus::networkConfigured){

            auto &server = octopus::__octoUDP_server;
            assert(server != nullptr);

            if( !server->suscribe(topic) ){
                std::cout << "-*Failed the suscription to "<< topic << " *-" << '\n';

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
            auto &server = octopus::__octoUDP_server;
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
            auto &server = octopus::__octoUDP_server;
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


    bool forcePublish(topic_t topic, topic_message_t message){
        if(octopus::networkConfigured){
            auto &server = octopus::__octoUDP_server;
            assert(server != nullptr);

            std::cout << "Sending publication of "<< topic << " : " << message << '\n';
            // FIXME: THIS CRASH
            if (! server->publish(topic, message)){
                std::cout << "Can't publish" << '\n';
                return false;
            }

        }else{

            std::cout << "Can't publish, network not configured" << '\n';

            return false;
        }

        return true;
    }


    void handle_tcpconnection(net::tcp::Connection_ptr client, const std::string data){

        printf("-> %s\n", data.c_str() );


        client->write("> ");
    }
}

#endif

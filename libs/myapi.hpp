#ifndef __MYAPI__HPP
#define __MYAPI__HPP
#include "types.hpp"
#include "udp.hpp"
#include "commandsTCP.hpp"
#include "protocol_messages.hpp"
#include "utils.hpp"

namespace octopus{

    static bool new_server = false; // Not quite elegant, but it can work
    static bool update_topics = false;
    static octoUDPserver* __octoUDP_server;


    bool announceServer(){
        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        return server->announceServer();
    }




    void addSuscription(size_t value_hash){

        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        if(server->addSuscription(value_hash)){
            std::cout << "Suscribed!" << '\n';
            update_topics = true;
        }

    }

    void removeSuscription(size_t value_hash){

        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        server->removeSuscription(value_hash);

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

            REQUEST_t req = processSuscription(addr.to_string(), strdata);
            if(req.type == SUSCRIBE_TO_TOPIC){
                addSuscription(req.hash_of_topic);
            }else if(req.type == UNSUSCRIBE_TO_TOPIC){
                removeSuscription(req.hash_of_topic);
            }
            else printf("Process of suscription failed\n");

            //forcePublish(strdata, "Hello guys!");

        }else{
            std::cout << "**Suscription received, but network isn't configured**" << '\n';
        }
    }



    void handle_publicationsocket_receiver(ip4_t addr, const char* data, size_t len){
        if(octopus::networkConfigured){

            std::string strdata(data,len);

            REQUEST_t req = processPublication(addr.to_string(), strdata);
            if(req.type == TOPIC_IS_CREATED){
                auto &server = octopus::__octoUDP_server;
                assert(server != nullptr);

                server->savePublisher(addr.to_string(), req.hash_of_topic);
            }else if(req.type == PUBLICATION){

                auto &server = octopus::__octoUDP_server;
                assert(server != nullptr);

                server->processPub(req.hash_of_topic, req.message);
            }else if(req.type == TOPIC_IS_REMOVED){

                auto &server = octopus::__octoUDP_server;
                assert(server != nullptr);

                server->removePublisher(addr.to_string(), req.hash_of_topic);

            }


            else{
                printf("Process of publication failed\n");
            }




        }else{
            std::cout << "**Cannot do a publication, but network isn't configured**" << '\n';
        }
    }

    void suscribe_to_topic(topic_t topic){
        if(octopus::networkConfigured){

            auto &server = octopus::__octoUDP_server;
            assert(server != nullptr);

            printf("Suscribing to the topic: %s -\n", topic.c_str());

            if( !server->suscribe(topic) ){
                std::cout << "-*Failed the suscription to "<< topic << " *-" << '\n';

                //retrySuscription(topic);
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
        //FIXME TO THE NEW PROTOCOL
        /*
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
        }*/


    }


    bool publish_a_message(topic_t topic, topic_message_t message){
        if(octopus::networkConfigured){
            auto &server = octopus::__octoUDP_server;
            assert(server != nullptr);

            std::cout << "Sending publication of "<< topic << " : " << message << '\n';


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

    void announceTopicCreated(topic_t topic){
        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        server->announceTopicCreated(topic);

    }


    void createTopic(topic_t topic){
        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);
        //Create the entry in the table, and put the value "any_server_suscribed" to false
        server->create_topic(topic);

        // Publish to the rest that exists that topic with the UUID(hash of the name)
        Timers::periodic(1s, 5s, [topic] (auto) {
            announceTopicCreated(topic);
        });

        // End
    }


    void remove_created_topic(topic_t topic){
        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        server->remove_topic(topic);
    }

    void unsuscribe_topic(topic_t topic){
        auto &server = octopus::__octoUDP_server;
        assert(server != nullptr);

        server->unsuscribe(topic);
    }


    int process_request(std::string request){

        std::vector<std::string> parameters = split(request, " ");


        if(parameters[0] == CREATE_TOPIC){
            if(parameters.size() != 2){
                return -2;
            }

            topic_t topic = parameters[1].substr(0, parameters[1].size() - 1);

            createTopic(topic);

            return 0;
        }else if(parameters[0] == SUSCRIBE){
            if(parameters.size() != 2){
                return -2;
            }
            //printf("Suscribing/////\n");

            topic_t topic = parameters[1].substr(0, parameters[1].size() - 1);

            suscribe_to_topic(topic);

            //printf("Suscription processed\n");

            return 0;
        }else if(parameters[0] == PUBLISH){

            if(parameters.size() != 3){
                return -2;
            }
            topic_t topic = parameters[2].substr(0, parameters[2].size() - 1);
            topic_message_t message = parameters[1];//.substr(0, parameters[1].size() - 1);

            publish_a_message(topic, message);

            return 0;

        }else if(parameters[0] == UNSUSCRIBE){
            if(parameters.size() != 2){
                return -2;
            }

            topic_t topic = parameters[1].substr(0, parameters[1].size() - 1);

            unsuscribe_topic(topic);
            return 0;
        }else if(parameters[0] == REMOVE_TOPIC){
            if(parameters.size() != 2){
                return -2;
            }

            topic_t topic = parameters[1].substr(0, parameters[1].size() - 1);

            remove_created_topic(topic);

            return 0;
        }


        else{
            return -1;
        }

    }


    void handle_tcpconnection(net::tcp::Connection_ptr client, const std::string data){

        printf("-> %s\n", data.c_str() );

        int res = process_request(data);

        if(res == -1){
            std::string response = "";

            response += "Error in the command\n";
            response += HELP;

            client->write(response);
        }
        else if(res == -2) client->write("Error with the arguments\n");

        printf("REQUEST PROCESSED\n");

        client->write("> ");
    }
}

#endif

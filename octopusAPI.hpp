/*

    This is the API of my service, for future developers

*/
#ifndef __OCTOPUSAPI__HPP__
#define __OCTOPUSAPI__HPP__

#include "libs/udp.hpp"
#include "libs/types.hpp"
#include "libs/myapi.hpp"
#include "libs/octopus.hpp"

namespace octopus{
    class octopusAPI {
    private:
        Octopus *master_server;


    public:
        octopusAPI (void (*publication_handler)(size_t value_hash, topic_message_t message)){
            master_server = new Octopus(publication_handler);

            master_server->configDiscovery();

            master_server->configAnnouncement();

            master_server->configSuscription();

            master_server->configPublishment();

            master_server->configShowTableDiscoveredServers();

            master_server->configShowTopics();

            master_server->configTCPconnection();
        }

        void create_topic(topic_t topic){

            master_server->create_topic(topic);

        }
        void subscribe_to_topic(topic_t topic){
            master_server->suscribe2topic(topic);
        }
        void publish(topic_t topic, topic_message_t message){
            master_server->publish(topic, message);
        }

        void unsubscribe(topic_t topic){
            master_server->unsuscribe(topic);
        }

        void remove_topic(topic_t topic){
            master_server->remove_topic(topic);
        }

        void stop(){
            master_server->stop();
        }

    };
}

#endif

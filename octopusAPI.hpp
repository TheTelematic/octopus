/*

    This is the API of my service, for future developers

*/
#ifndef __OCTOPUSAPI__HPP__
#define __OCTOPUSAPI__HPP__

#include "libs/udp.hpp"
#include "libs/types.hpp"
#include "libs/myapi.hpp"
#include "libs/octopus.hpp"

#include "API_DCPS.hpp"

namespace octopus{
    class octopusAPI {
    private:
        Octopus master_server;


    public:
        octopusAPI (){
            master_server.configDiscovery();

            master_server.configAnnouncement();

            master_server.configSuscription();

            master_server.configPublishment();

            master_server.configShowTableDiscoveredServers();

            master_server.configShowTopics();

            master_server.configTCPconnection();
        }

        void create_topic(topic_t topic){

            master_server.create_topic(topic);

        }
        void suscribe_to_topic(topic_t topic){
            master_server.suscribe2topic(topic);
        }
        void publish(topic_t topic, topic_message_t message){
            master_server.publish(topic, message);
        }

        void unsuscribe(topic_t topic){
            master_server.unsuscribe(topic);
        }

        void remove_topic(topic_t topic){
            master_server.remove_topic(topic);
        }



    };
}

#endif

#ifndef __OCTOPUS__HPP
#define __OCTOPUS__HPP

#include <util/timer.hpp>

#include "myapi.hpp"
#include "udp.hpp"


namespace octopus{

    octoUDPserver* octoUDPserver::singleton_instance = nullptr;

    class Octopus{
    private:
        octoUDPserver* server;

        static Octopus *singleton;

        Octopus(){
            server = octoUDPserver::getInstance();
        }

    public:

        static Octopus* getInstance(){
            if(singleton == nullptr) singleton = new Octopus();

            return singleton;

        }


        void configDiscovery(){
            assert(server != nullptr);

            auto* ds = server->getDS();
            ds->on_read( [ds](
                        net::UDP::addr_t addr,
                        net::UDP::port_t port,
                        const char* data,
                        size_t len
                        ){
                            handle_discoversocket_receiver(data, len);
                        }

            );
        }

        void configAnnouncement(){
            Timers::oneshot(1s, [] (auto) {
                tryAnnounceServer();
            });
        }

        void configShowTableDiscoveredServers(){
            Timers::periodic(3s, 3s, [] (auto) {
                showTable();
            });
        }

        void configSuscription(){
            assert(server != nullptr);

            auto* ss = server->getSS();
            ss->on_read( [ss](
                        net::UDP::addr_t addr,
                        net::UDP::port_t port,
                        const char* data,
                        size_t len
                        ){
                            handle_suscriptionsocket_receiver(addr, data, len);
                        }

            );
        }

        bool suscribeAfter(Timers::duration_t to, topic_t topic){

            Timers::periodic(to, to, [topic] (auto) {
                suscribe_to_topic(topic);
            });

            return true;
        }

        void suscribe2topic(topic_t topic){

            suscribe_to_topic(topic);

        }

        void configShowTopics(){
            Timers::periodic(3s, 3s, [] (auto) {
                showTopics();
            });
        }

        bool publish(topic_t topic, topic_message_t message){
            return forcePublish(topic, message);

        }

        void configPeriodicPublication(topic_t topic, topic_message_t message, Timers::duration_t to){
            Message m(topic, message);

            Timers::periodic(to, to, [&m] (auto) {
                forcePublish(m.getTopic(), m.getMessage());
            });


        }

        void configPublishment(){
            assert(server != nullptr);

            auto* ps = server->getPS();
            ps->on_read( [ps](
                        net::UDP::addr_t addr,
                        net::UDP::port_t port,
                        const char* data,
                        size_t len
                        ){
                            handle_publicationsocket_receiver(addr, data, len);
                        }

            );
        }

    };

}


#endif

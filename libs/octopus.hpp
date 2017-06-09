#ifndef __OCTOPUS__HPP
#define __OCTOPUS__HPP

#include <util/timer.hpp>

#include "myapi.hpp"
#include "udp.hpp"
#include "tcp.hpp"

namespace octopus{
    static octoTCPserver* __octoTCP_server;

    class Octopus{

    public:
        Octopus(){
            octopus::__octoUDP_server = new octoUDPserver();
            octopus::__octoTCP_server = new octoTCPserver();
        }




        void configDiscovery(){
            assert(__octoUDP_server != nullptr);

            auto* ds = __octoUDP_server->getDS();
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
            assert(__octoUDP_server != nullptr);

            auto* ss = __octoUDP_server->getSS();
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

        void suscribeAfter(Timers::duration_t to, topic_t topic){

            Timers::oneshot(to, [topic] (auto) {
                suscribe_to_topic(topic);
            });
        }

        void configPeriodicSuscribition(topic_t topic, Timers::duration_t to){

            Timers::periodic(to, to, [topic] (auto) {
                suscribe_to_topic(topic);
            });

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
            Message *m = new Message(topic, message);

            Timers::periodic(to, to, [m] (auto) {
                forcePublish(m->getTopic(), m->getMessage());
            });


        }

        void publishAfter(Timers::duration_t to, topic_t topic, topic_message_t message){

            Message *m = new Message(topic, message);

            Timers::oneshot(to, [m] (auto) {
                forcePublish(m->getTopic(), m->getMessage());
            });
        }

        void configPublishment(){
            assert(__octoUDP_server != nullptr);

            auto* ps = __octoUDP_server->getPS();
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

        void configTCPconnection(){
            assert(__octoTCP_server != nullptr);

            auto* socket = __octoTCP_server->getSocket();

            socket->on_connect(
                [socket] (Connection_ptr client) {
                      printf("Connected [Client]: %s\n", client->to_string().c_str());

                      client->write("Welcome to Octopus!\n\n> ");

                      client->on_read(1024, [client](auto buf, size_t n) {
                          std::string data{ (char*)buf.get(), n };

                          handle_tcpconnection(client, data);
                      });

                      client->on_disconnect([client](Connection_ptr, Disconnect reason) {
                          printf("Disconnected [Client]: %s\n", reason.to_string().c_str());
                      });
            });
        }

        void create_topic(topic_t topic){
            createTopic(topic);
        }
    };

}


#endif

#ifndef __TYPES__D
#define __TYPES__D

#include <os>

namespace octopus{

    typedef uint8_t IPv4_t[4];
    typedef uint8_t netmaskv4_t[4];
    typedef uint8_t gatewayv4_t[4];
    typedef uint8_t dnsv4_t[4];

    struct new_configIPv4_t{
            IPv4_t ip;
            netmaskv4_t netmask;
            gatewayv4_t gateway;
            dnsv4_t dns;
    };

    typedef net::tcp::Listener TCPserver_t;
    typedef net::UDPSocket UDPsocket_t;

    typedef uint8_t broadcast_t[4];
    typedef net::IP4::addr ip4_t;

    typedef std::string ds_addrs_t;
    typedef std::list<ds_addrs_t> discovered_servers_t;
    typedef std::list<ds_addrs_t>::iterator iterator_ds_t;


    typedef std::string topic_t;
    typedef struct{
        size_t hash_of_topic;
        int any_server_suscribed;
        Timers::id_t timer_id;

    }topic_list_item_t;

    typedef std::list<topic_list_item_t> topic_list_t;
    typedef std::list<topic_list_item_t>::iterator iterator_tl_t;

    typedef std::string topic_message_t;

    typedef struct{
        std::list<std::string> addrs_publisher;
        size_t hash_of_topic;
        bool suscribed;
    }publisher_item_list_t;

    typedef std::list<publisher_item_list_t> publishers_list_t;
    typedef std::list<publisher_item_list_t>::iterator iterator_publishers_t;
    typedef std::list<std::string>::iterator iterator_string_t;


}


#endif

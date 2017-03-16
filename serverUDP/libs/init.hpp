/*
    Autor: Arturo Jesús Parra Soto
    email: arturoteleco95@protonmail.ch
*/

#ifndef __INIT__H
#define  __INIT__H

//Librerias hechas por mi
#include "types.hpp"



//Librerias de IncludeOS
#include <os>
#include <net/inet4>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stack>

using namespace std;

namespace octopus{

    new_configIPv4_t* defaultNetConfig(){
        static new_configIPv4_t* DEFAULT_CONFIG = new new_configIPv4_t;


        DEFAULT_CONFIG->ip[0] = 10;
        DEFAULT_CONFIG->ip[1] = 0;
        DEFAULT_CONFIG->ip[2] = 0;
        DEFAULT_CONFIG->ip[3] = 2;

        DEFAULT_CONFIG->netmask[0] = 255;
        DEFAULT_CONFIG->netmask[1] = 255;
        DEFAULT_CONFIG->netmask[2] = 255;
        DEFAULT_CONFIG->netmask[3] = 0;

        DEFAULT_CONFIG->gateway[0] = 10;
        DEFAULT_CONFIG->gateway[1] = 0;
        DEFAULT_CONFIG->gateway[2] = 0;
        DEFAULT_CONFIG->gateway[3] = 1;

        DEFAULT_CONFIG->dns[0] = 8;
        DEFAULT_CONFIG->dns[1] = 8;
        DEFAULT_CONFIG->dns[2] = 8;
        DEFAULT_CONFIG->dns[3] = 8;

        return DEFAULT_CONFIG;
    }




    //TODO: Una funcion que le pases la IP, la NETMASK, el GATEWAY y el DNS en formato string y te devuelva un tipo new_configIPv4_t

    new_configIPv4_t* formatStringConfig(const char* ip, const char* netmask, const char* gateway, const char* dns){
        /*
        std::cout << "IP -> " << ip << std::endl;
        std::cout << "NETMASK -> " << netmask << std::endl;
        std::cout << "GATEWAY -> " << gateway << std::endl;
        std::cout << "DNS -> " << dns << std::endl;*/
        //Devuelve un in_addr_t que es como un uint32_t
        auto ipf = inet_addr(ip);
        auto ntf = inet_addr(netmask);
        auto gtf = inet_addr(gateway);
        auto dnsf = inet_addr(dns);

        static new_configIPv4_t* NETWORK_CONFIG = new new_configIPv4_t;

        NETWORK_CONFIG->ip[3] = ipf >> 24;
        NETWORK_CONFIG->ip[2] = (ipf >> 16) & 0xFF;
        NETWORK_CONFIG->ip[1] = (ipf >> 8) & 0xFF;
        NETWORK_CONFIG->ip[0] = ipf & 0xFF;

        NETWORK_CONFIG->netmask[3] = ntf >> 24;
        NETWORK_CONFIG->netmask[2] = (ntf >> 16) & 0xFF;
        NETWORK_CONFIG->netmask[1] = (ntf >> 8) & 0xFF;
        NETWORK_CONFIG->netmask[0] = ntf & 0xFF;

        NETWORK_CONFIG->gateway[3] = gtf >> 24;
        NETWORK_CONFIG->gateway[2] = (gtf >> 16) & 0xFF;
        NETWORK_CONFIG->gateway[1] = (gtf >> 8) & 0xFF;
        NETWORK_CONFIG->gateway[0] = gtf & 0xFF;

        NETWORK_CONFIG->dns[3] = dnsf >> 24;
        NETWORK_CONFIG->dns[2] = (dnsf >> 16) & 0xFF;
        NETWORK_CONFIG->dns[1] = (dnsf >> 8) & 0xFF;
        NETWORK_CONFIG->dns[0] = dnsf & 0xFF;

        return NETWORK_CONFIG;

    }

    std::stack<std::string> parseArgs(const std::string &args){

        unsigned int start = 0, end;

        std::stack<std::string> result;

        std::string delimeter = " ";

        bool nombre_ejecutable = false;

        while((end = args.find(delimeter, start)) != std::string::npos){
            if(!nombre_ejecutable){
                nombre_ejecutable = true;
            }else{
                unsigned int tmp = args.find(delimeter, start);
                if((tmp >= end) || (tmp == std::string::npos)){

                    std::string tmp = args.substr(start, end - start);
                    result.push(tmp);
                }


            }
            start = end + 1;
        }

        if(start < (args.length() - 1)){
            std::string tmp = args.substr(start, args.length() - start);
            result.push(tmp);
        }

        return result;
    }

}


#endif

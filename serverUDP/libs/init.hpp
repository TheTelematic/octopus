/*
    Autor: Arturo Jesús Parra Soto
    email: arturoteleco95@protonmail.ch
*/

#ifndef __INIT__H
#define  __INIT__H

//Librerias hechas por mi
#include "types.hpp"



//Librerias de IncludeOS
#include <net/inet4>
#include <iostream>

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

}


#endif

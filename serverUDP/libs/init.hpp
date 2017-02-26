/*
    Autor: Arturo Jesús Parra Soto
    email: arturoteleco95@protonmail.ch
*/

#ifndef __INIT__H
#define  __INIT__H

//Librerias hechas por mi
#include "types.hpp"


//Librerias ajenas a IncludeOS
#include <iostream>


using namespace std;

//Librerias de IncludeOS
#include <net/inet4>



namespace octopus{
    /*
        Template to init new_configIPv4_t:

            nw->ip[0] = 10;
            nw->ip[1] = 0;
            nw->ip[2] = 0;
            nw->ip[3] = 2;

            nw->netmask[0] = 255;
            nw->netmask[1] = 255;
            nw->netmask[2] = 255;
            nw->netmask[3] = 0;

            nw->gateway[0] = 10;
            nw->gateway[1] = 0;
            nw->gateway[2] = 0;
            nw->gateway[3] = 1;

            nw->dns[0] = 8;
            nw->dns[1] = 8;
            nw->dns[2] = 8;
            nw->dns[3] = 8;

    */
    void change_IPconfig(new_configIPv4_t* nw){
        // Static IP configuration will get overwritten by DHCP, if found
        auto& inet = net::Inet4::ifconfig<0>(10);
        inet.network_config({ nw->ip[0],         nw->ip[1],       nw->ip[2],       nw->ip[3] },         // IP
                            { nw->netmask[0],    nw->netmask[1],  nw->netmask[2],  nw->netmask[3] },    // Netmask
                            { nw->gateway[0],    nw->gateway[1],  nw->gateway[2],  nw->gateway[3] },    // Gateway
                            { nw->dns[0],        nw->dns[1],      nw->dns[2],      nw->dns[3] });       // DNS
    }

    void init_TCP(const std::string& args){

        cout << "Initialized!" << endl;
        cout << "Your args: " << args.c_str() << endl;



    }
}


#endif

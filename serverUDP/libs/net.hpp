#ifndef __NET__HPP__
#define __NET__HPP__

#include <os>

#include "types.hpp"

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
    class octoNet{
    protected:
        net::Inet<net::IP4> *inet;

    public:
        //Realmente este constructor sirve de algo?
        octoNet(new_configIPv4_t* nw){
            // Static IP configuration will get overwritten by DHCP, if found
            auto& tmp = net::Inet4::ifconfig<0>(10);

            inet = &tmp;

            inet->network_config({ nw->ip[0],         nw->ip[1],       nw->ip[2],       nw->ip[3] },         // IP
                                { nw->netmask[0],    nw->netmask[1],  nw->netmask[2],  nw->netmask[3] },    // Netmask
                                { nw->gateway[0],    nw->gateway[1],  nw->gateway[2],  nw->gateway[3] },    // Gateway
                                { nw->dns[0],        nw->dns[1],      nw->dns[2],      nw->dns[3] });       // DNS



        }

        void changeNetConfig(new_configIPv4_t* nw){

            inet->network_config({ nw->ip[0],         nw->ip[1],       nw->ip[2],       nw->ip[3] },         // IP
                                { nw->netmask[0],    nw->netmask[1],  nw->netmask[2],  nw->netmask[3] },    // Netmask
                                { nw->gateway[0],    nw->gateway[1],  nw->gateway[2],  nw->gateway[3] },    // Gateway
                                { nw->dns[0],        nw->dns[1],      nw->dns[2],      nw->dns[3] });       // DNS


        }

        octoNet(){
            auto& tmp = net::Inet4::ifconfig<0>(10);

            inet = &tmp;
        }
        ~octoNet(){}
    };


}


#endif

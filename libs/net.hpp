#ifndef __NET__HPP__
#define __NET__HPP__

#include <os>

#include "types.hpp"
#include "init.hpp"



namespace octopus{
    static bool networkConfigured;
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
        new_configIPv4_t* my_config;


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


            my_config = nw;

        }

        //Innecesario pues se debe inicializar y una vez seteado no debe cambiarse
        void changeNetConfig(new_configIPv4_t* nw){

            inet->network_config({ nw->ip[0],         nw->ip[1],       nw->ip[2],       nw->ip[3] },         // IP
                                { nw->netmask[0],    nw->netmask[1],  nw->netmask[2],  nw->netmask[3] },    // Netmask
                                { nw->gateway[0],    nw->gateway[1],  nw->gateway[2],  nw->gateway[3] },    // Gateway
                                { nw->dns[0],        nw->dns[1],      nw->dns[2],      nw->dns[3] });       // DNS


            my_config = nw;
        }


        //Devuelve la ip en formato string
        void getIP(IPv4_t &ip){

            net::IP4::addr tmp = inet->ip_addr();

            ip[0] = tmp.part(0);
            ip[1] = tmp.part(1);
            ip[2] = tmp.part(2);
            ip[3] = tmp.part(3);
        }

        //Devuelve la direccion de broadcast en formato IP4::addr
        void getBROADCAST(broadcast_t &br){
            std::string ip = inet->ip_addr().str();
            std::string netmask = inet->netmask().str();
            new_configIPv4_t* tmp = formatStringConfig(ip.c_str(), netmask.c_str(), "", "");

            //printf("IP(String): %s\nNETMASK(String): %s\n", ip.c_str(), netmask.c_str() );
            /*printf("Getting broadcast:\nIp: %d.%d.%d.%d\nNetmask: %d.%d.%d.%d\n",tmp->ip[0],
                                                                            tmp->ip[1],
                                                                            tmp->ip[2],
                                                                            tmp->ip[3],

                                                                            tmp->netmask[0],
                                                                            tmp->netmask[1],
                                                                            tmp->netmask[2],
                                                                            tmp->netmask[3]);*/

            br[0] = tmp->ip[0] | (0xFF - tmp->netmask[0]);
            br[1] = tmp->ip[1] | (0xFF - tmp->netmask[1]);
            br[2] = tmp->ip[2] | (0xFF - tmp->netmask[2]);
            br[3] = tmp->ip[3] | (0xFF - tmp->netmask[3]);

            //printf("Broadcast: %d.%d.%d.%d\n", br[0], br[1], br[2], br[3] );

            delete tmp;
        }



        octoNet(){
            auto& tmp = net::Inet4::ifconfig<0>(10);

            inet = &tmp;

            networkConfigured = false;

            inet->on_config([](auto &self) {
                    std::cout << "DHCP IS CONFIGURED" << '\n';
                    networkConfigured = true;
            });
        }
        ~octoNet(){}
    };

    void printIP__uint32_t(uint32_t ip){
        unsigned char bytes[4];

        bytes[0] = ip & 0xFF;
        bytes[1] = (ip >> 8) & 0xFF;
        bytes[2] = (ip >> 16) & 0xFF;
        bytes[3] = (ip >> 24) & 0xFF;
        printf("%d.%d.%d.%d\n", bytes[0], bytes[1], bytes[2], bytes[3]);


    }
}


#endif

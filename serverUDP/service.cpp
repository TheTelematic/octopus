// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//Librerias de IncludeOS
#include <os>
#include <util/timer.hpp>


//Mis Librerias
#include "../libs/udp.hpp"
#include "../libs/init.hpp"


using namespace std;
using namespace octopus;

octoUDPserver* server = NULL;
bool send_discover = false;


void Service::start(){

        // Inicializar el sistema -- S00

        server = new octoUDPserver();

        // End S00

        //Configure behaviour -- S01

        auto* ds = server->getDS();
        ds->on_read( [ds](
                    net::UDP::addr_t addr,
                    net::UDP::port_t port,
                    const char* data,
                    size_t len
                    ){
                        //std::cout << "HI GUY" << '\n';
                        /**/
                        if(octopus::networkConfigured){
                            std::cout << "New discovery!" << std::endl;

                            /*uint32_t ip;

                            // I think this is not totally correct, because I send a sizeof(ip4_t)
                            if(len == sizeof(uint32_t)){

                                //assert(len == 4);

                                ip = data[3] << 24;
                                ip |= data[2] << 16;
                                ip |= data[1] << 8;
                                ip |= data[0];

                            }else{
                                std::cout << "-**ERROR 00001" << std::endl;
                            }


                            ip4_t tmp(ip);*/
                            std::string strdata(data,len);

                            CHECK(1, "Getting UDP data from %s:  %d -> IP: %s", addr.str().c_str(), port, strdata.c_str());
                        }else{
                            std::cout << "**Discovery received, but network isn't configured**" << '\n';
                        }
                        /**/



                    }

        );
        /*
        net::Inet::on_config([](auto &self) {
                std::cout << "DHCP IS CONFIGURED" << '\n';
        });*/


        // ---------------------------------------End S01

        // Announce the server -- S02

        //server->announceServer();

        // ---------------------------------------End S02

        // Configure timers -- S03
        /*Timer t;

        t.start(1s, [] {
                        server->announceServer();
                });

        if(t.is_running()) {
                cout << "TIMER CORRIENDO\n";
        }*/

        //assert(Timers::active() == 1);



        /*Timers::oneshot(1s, [] (auto) {


            //server->announceServer();

        });*/

        // ---------------------------------------Ens S03

        cout << "Test start now!" << endl;


}

/*
    I have to use this method for heavy stuff
*/
void Service::ready(){
    std::cout << "THE SERVICE IS READY" << '\n';



    server->announceServer();

    Timers::periodic(5s, 5s, [] (auto) {
        server->announceServer();
    });

    //server->announceServer();
}




























// End

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

//IncludeOS's libs
#include <os>
#include <util/timer.hpp>


//My libs
#include "../libs/udp.hpp"
#include "../libs/init.hpp"


using namespace std;
using namespace octopus;


/*
    GLOBAL VARIABLES
    -------------------------------------------

    How IncludeOS is in one processor and one only thread, global variables it's not a big risky.
    Because the functions of timers or of handlers are going to do all, before another function went executed
*/
bool new_server = false;
octoUDPserver* octoUDPserver::singleton_instance = nullptr;

/*
    DECLARATION OF THE FUNCTIONS
    -------------------------------------------
*/
void handle_discoversocket_receiver(const char *data, size_t len);
void announceServer();
void showTable();

/*
    MAIN FUNCTIONS
    -------------------------------------------
*/

void Service::start(){
    // Inicializar el sistema -- S00

    // End S00

    cout << "THE SERVICE IS STARTED" << endl;


}

/*
    I have to use this method for heavy stuff
*/
void Service::ready(){
    octoUDPserver* server = octoUDPserver::getInstance();
    assert(server != nullptr);
    
    std::cout << "THE SERVICE IS READY" << '\n';
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

    Timers::periodic(5s, 5s, [] (auto) {
        announceServer();
    });

    /*
        To show the IP ADDRESSES of the others servers discovered
    */
    Timers::periodic(3s, 3s, [] (auto) {
        showTable();
    });

    announceServer();
    std::cout << "THE SERVICE IS CONFIGURED" << '\n';
}




/*
    DEFINITION OF THE FUNCTIONS
    -------------------------------------------
*/

void handle_discoversocket_receiver(const char *data, size_t len){
    if(octopus::networkConfigured){
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);
        //std::cout << "New discovery!" << std::endl;

        std::string strdata(data,len);

        CHECK(1, "Discovered new server in %s", strdata.c_str());

        if(new_server){
            server->addServerAddr(inet_addr(strdata.c_str()));
        }else{
            new_server = server->addServerAddr(inet_addr(strdata.c_str()));
        }

    }else{
        std::cout << "**Discovery received, but network isn't configured**" << '\n';
    }
}

void announceServer(){
    octoUDPserver* server = octoUDPserver::getInstance();
    assert(server != nullptr);

    server->announceServer();
}

void showTable(){

    if (new_server) {
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);
        discovered_servers_t list_of_addresses = server->getServerAddresses();

        std::cout << "IP ADDRESSES TABLE" << '\n';
        std::cout << "--------------------" << '\n';

        for(iterator_ds_t it = list_of_addresses.begin(); it != list_of_addresses.end(); it++ ){

            printIP__uint32_t(*it);
        }
        std::cout << "--------------------" << '\n';

        new_server = false;
    }

}













// End

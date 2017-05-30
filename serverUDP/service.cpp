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



//My libs
#include "../libs/udp.hpp"
#include "../libs/octopus.hpp"


using namespace std;
using namespace octopus;


/*
    GLOBAL VARIABLES
    -------------------------------------------

    How IncludeOS is in one processor and one only thread, global variables it's not a big risky.
    Because the functions of timers or of handlers are going to do all, before another function went executed
*/
Octopus* Octopus::singleton = nullptr;

/*
    MAIN FUNCTIONS
    -------------------------------------------
*/

void Service::start(){

    cout << "THE SERVICE IS STARTED" << endl;

}

/*
    I have to use this method for heavy stuff
*/
void Service::ready(){
    cout << "THE SERVICE IS READY" << endl;

    Octopus *master_server = Octopus::getInstance();

    master_server->configDiscovery();

    master_server->configAnnouncement();

    master_server->configShowTableDiscoveredServers();

    master_server->configShowTopics();

    master_server->configSuscription();

    master_server->suscribeAfter(5s, "TOPIC #1"); // This failed because there are not servers to send it

    //master_server->configPublishment();

    //master_server->configPeriodicPublication("TOPIC #1", "Hello my friends", 1s);


    std::cout << "THE SERVICE IS CONFIGURED" << '\n';
}















// End

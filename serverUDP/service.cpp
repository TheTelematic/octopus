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
#include <iostream>



//Mis Librerias
#include "../libs/udp.hpp"
#include "../libs/init.hpp"

using namespace std;
using namespace octopus;


void Service::start(const std::string& args){

    // Inicializar el sistema -- S00

    auto parameters = parseArgs(args);

    std::string dns     = parameters.top().c_str(); parameters.pop();
    std::string gateway = parameters.top().c_str(); parameters.pop();
    std::string netmask = parameters.top().c_str(); parameters.pop();
    std::string ip      = parameters.top().c_str(); parameters.pop();

    auto* networkconfig = formatStringConfig(ip.c_str(), netmask.c_str(), gateway.c_str(), dns.c_str());

    octoUDPserver server(networkconfig);

    // End S00

    //Configurar comportamiento -- S01

    auto* ds = server.getDS();

    ds->on_read(
        [ds](
          net::UDP::addr_t addr,
          net::UDP::port_t port,
          const char* data,
          size_t len
        ){
           std::cout << "New discovery!" << std::endl;

           std::string strdata(data, len);

           CHECK(1, "Getting UDP data from %s:  %d -> IP: %s", addr.str().c_str(), port, strdata.c_str());

           ds->sendto(addr, port, "hi!", 4);
       }
       //this->trumpetServer();
   );


    // End S01

    // Trumpet the server -- S02

    server.trumpetServer();

    // End S02

    cout << "Test start now!" << endl;


}































// End

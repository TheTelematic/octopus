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
#include "../libs/tcp.hpp"
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

    octoTCPserver server(5050, networkconfig);

    auto* socket = server.getSocket();

    socket->on_connect(
        [socket] (Connection_ptr client) {
              printf("Connected [Client]: %s\n", client->to_string().c_str());

              client->on_read(1024, [client](auto buf, size_t n) {
                  std::string data{ (char*)buf.get(), n };

                  printf("Recibido: %s\n", data.c_str());
                  client->write(data + "<");
              });

              client->on_disconnect([client](Connection_ptr, Disconnect reason) {
                  printf("Disconnected [Client]: %s\n", reason.to_string().c_str());
              });
    });

    cout << "Test start now!" << endl;


}































// End

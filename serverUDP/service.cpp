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
#include <net/inet4>

//Mis Librerias
#include "libs/init.hpp"
#include "libs/types.hpp"

using namespace octopus;
using Connection_ptr = net::tcp::Connection_ptr;
using Disconnect = net::tcp::Connection::Disconnect;

void Service::start(/*const std::string& args*/){

    new_configIPv4_t* nw = new new_configIPv4_t;


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


    change_IPconfig(nw);
}































// End

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
#include <iostream>

//My libs
#include "../octopusAPI.hpp"
#include "../API_DCPS.hpp"

using namespace std;
using namespace octopus;

octopusAPI* api;


extern "C" char *strpbrk(const char *s, const char *accept) {
   const std::string temp(accept);
   size_t len = strlen(s);
   for (size_t idx = 0; idx < len; idx++) {
     for (auto c : temp) if (s[idx] == c) return const_cast<char*>(&s[idx]);
   }
   return nullptr;
}

extern "C" bool is_nan(double x) { return x != x; }

/*
    MAIN FUNCTIONS
    -------------------------------------------
*/
void publication_handler(size_t value_hash, topic_message_t message){
    printf("-Publication processed-\n Message: %s\nTopic (hashed): %zu\n",message.c_str(), value_hash );
}


void Service::start(){

    cout << "THE SERVICE IS STARTED" << endl;

}

/*
    I have to use this method for heavy stuff
*/
void Service::ready(){
    cout << "THE SERVICE IS READY" << endl;

    api = new octopusAPI(&publication_handler);


    std::cout << "THE SERVICE IS CONFIGURED" << '\n';
}


void Service::stop(){
    api->stop();
}















// End

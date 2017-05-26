
#ifndef __MYAPI__HPP
#define __MYAPI__HPP
#include "types.hpp"

namespace octopus{
    bool announceServer(){
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);

        return server->announceServer();
    }


    bool addAddrServer(std::string addr){
        octoUDPserver* server = octoUDPserver::getInstance();
        assert(server != nullptr);

        return server->addServerAddr(addr);
    }

    void showIpAddr(ds_addrs_t ip){

        std::cout << ip << '\n';

    }

}

#endif

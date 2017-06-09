
#ifndef __PROTOCOL_MESSAGES__HPP__
#define __PROTOCOL_MESSAGES__HPP__


#ifndef SEPARATOR
#define SEPARATOR "//\\\\"
#endif

#ifndef TOPIC_IS_CREATED
#define TOPIC_IS_CREATED "0"
#endif

#include "types.hpp"
#include "utils.hpp"

namespace octopus{



    void processMessageOfProtocol(std::string addr, std::string message_received){

        std::vector<std::string> v = split(message_received, SEPARATOR);

        if(v[0] == TOPIC_IS_CREATED){

            if(v.size() != 2) printf("----------$%&&/---------ERROR IN PROTOCOL------------$%&&/-----\n");

            printf("Topic created by %s: %s\n", addr.c_str(),  v[1].c_str());

        }else{

        }

    }


    std::string getMessageTopicCreated(topic_t topic){
        std::string message = "";
        message += TOPIC_IS_CREATED;
        message += SEPARATOR;
        message += topic;

        return message;
    }
}
#endif

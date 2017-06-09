
#ifndef __PROTOCOL_MESSAGES__HPP__
#define __PROTOCOL_MESSAGES__HPP__


#ifndef SEPARATOR
#define SEPARATOR "//"
#endif

#ifndef TOPIC_IS_CREATED
#define TOPIC_IS_CREATED "0"
#endif

#include "types.hpp"
#include "utils.hpp"

namespace octopus{

    size_t doHash(topic_t topic){
        std::hash<topic_t> hash;

        return hash(topic);

    }



    void processMessageOfProtocol(std::string addr, std::string message_received){

        std::vector<std::string> v = split(message_received, SEPARATOR);

        if(v[0] == TOPIC_IS_CREATED){

            if(v.size() != 2) printf("----------$%&&/---------ERROR IN PROTOCOL------------$%&&/-----\n");

            topic_t topic = v[1];
            topic.substr(1);

            printf("Topic created by %s: %s\n", addr.c_str(), topic.c_str() );
            printf("Hash: %zu\n", doHash(topic));


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

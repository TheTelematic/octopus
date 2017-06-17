
#ifndef __PROTOCOL_MESSAGES__HPP__
#define __PROTOCOL_MESSAGES__HPP__


#ifndef SEPARATOR
#define SEPARATOR "//"
#endif

#ifndef ERROR_PROTOCOL
#define ERROR_PROTOCOL "-1"
#endif

#ifndef TOPIC_IS_CREATED
#define TOPIC_IS_CREATED "0"
#endif

#ifndef SUSCRIBE_TO_TOPIC
#define SUSCRIBE_TO_TOPIC "1"
#endif


#ifndef PUBLICATION
#define PUBLICATION "3"
#endif

#ifndef TOPIC_IS_REMOVED
#define TOPIC_IS_REMOVED "4"
#endif

#ifndef UNSUSCRIBE_TO_TOPIC
#define UNSUSCRIBE_TO_TOPIC "5"
#endif

#include "types.hpp"
#include "utils.hpp"
#include "udp.hpp"

// My protobuf message
#include "../protobuf/topic.pb.h"


namespace octopus{

    struct REQUEST_t{
        std::string type;
        size_t hash_of_topic;
        topic_message_t message;
    };

    size_t doHash(topic_t topic){
        std::hash<topic_t> hash;

        return hash(topic);

    }

    std::string serializeWithProtobuf(std::string message){
        GenericTopic tmp;

        std::string result;
        if(tmp.IsInitialized()){
            tmp.set_msg(message);


            tmp.SerializeToString(&result);

            //google::protobuf::ShutdownProtobufLibrary();
        }

        return result;
    }


    std::string deserializeWithProtobuf(std::string serialized_input){
        GenericTopic topic;

        topic.ParseFromString(serialized_input);

        return topic.msg();
    }



    REQUEST_t processPublication(std::string message_received){



        std::vector<std::string> v = split(deserializeWithProtobuf(message_received), SEPARATOR);

        if(v[0] == TOPIC_IS_CREATED){

            if(v.size() != 2) printf("----------###/---------ERROR IN PROTOCOL------------###/-----\n");

            topic_t topic = v[1];
            topic.substr(1);

            size_t value_hash = doHash(topic);

            //printf("Topic created by %s: %s\n", addr.c_str(), topic.c_str() );
            //printf("Hash: %zu\n", value_hash);

            REQUEST_t req;

            req.type = TOPIC_IS_CREATED;
            req.hash_of_topic = value_hash;

            return req;




        }else if(v[0] == PUBLICATION){

            if(v.size() != 3) printf("----------###/---------ERROR IN PROTOCOL------------###/-----\n");

            topic_t topic = v[1];
            topic.substr(1);

            topic_message_t message = v[2];
            //message.substr(1);
            //printf("Message received: %s\n", message_received.c_str());

            //printf("Publication of %s: %s\n",topic.c_str(), message.c_str() );

            REQUEST_t req;

            req.type = PUBLICATION;

            size_t value_hash = doHash(topic);
            req.hash_of_topic = value_hash;

            req.message = message;

            return req;
        }else if(v[0] == TOPIC_IS_REMOVED){

            if(v.size() != 2) printf("----------###/---------ERROR IN PROTOCOL------------###/-----\n");

            topic_t topic = v[1];
            topic.substr(1);

            size_t value_hash = doHash(topic);

            //printf("Topic created by %s: %s\n", addr.c_str(), topic.c_str() );
            //printf("Hash: %zu\n", value_hash);

            REQUEST_t req;

            req.type = TOPIC_IS_REMOVED;
            req.hash_of_topic = value_hash;

            return req;

        }



        else{
            REQUEST_t req;

            req.type = ERROR_PROTOCOL;
            return req;
        }

    }

    REQUEST_t processSuscription(std::string message_received){
        std::vector<std::string> v = split(deserializeWithProtobuf(message_received), SEPARATOR);

        if(v[0] == SUSCRIBE_TO_TOPIC){

            if(v.size() != 2) printf("----------###/---------ERROR IN PROTOCOL------------###/-----\n");
            printf("Message received: %s\n", message_received.c_str());
            topic_t topic = v[1];
            topic.substr(1);

            std::stringstream sstream(topic);

            size_t value_hash;
            sstream >> value_hash;

            printf("Suscription of topic %s (%zu)\n",topic.c_str(), value_hash );

            REQUEST_t req;

            req.type = SUSCRIBE_TO_TOPIC;
            req.hash_of_topic = value_hash;

            return req;

        }else if(v[0] == UNSUSCRIBE_TO_TOPIC){

            if(v.size() != 2) printf("----------###/---------ERROR IN PROTOCOL------------###/-----\n");

            topic_t topic = v[1];
            topic.substr(1);

            size_t value_hash = doHash(topic);

            printf("UNsuscription of topic %s (%zu)\n",topic.c_str(), value_hash );

            REQUEST_t req;

            req.type = UNSUSCRIBE_TO_TOPIC;
            req.hash_of_topic = value_hash;

            return req;

        }


        else{
            REQUEST_t req;

            req.type = ERROR_PROTOCOL;
            return req;
        }


    }


    std::string getMessageTopicCreated(topic_t topic){
        std::string message = "";
        message += TOPIC_IS_CREATED;
        message += SEPARATOR;
        message += topic;

        return serializeWithProtobuf(message);

    }


    std::string getMessageSuscription(size_t value_hash){
        std::string message = "";
        message += SUSCRIBE_TO_TOPIC;
        message += SEPARATOR;

        char str[256] = "";

        snprintf(str, sizeof(str), "%zu", value_hash);

        std::string tmp(str);
        message += tmp;

        return serializeWithProtobuf(message);
    }

    std::string getMessagePublication(topic_t topic, topic_message_t message_){
        std::string message = "";
        message += PUBLICATION;
        message += SEPARATOR;
        message += topic;
        message += SEPARATOR;
        message += message_;

        return serializeWithProtobuf(message);
    }

    std::string getMessageTopicRemoved(topic_t topic){
        std::string message = "";
        message += TOPIC_IS_REMOVED;
        message += SEPARATOR;
        message += topic;

        return serializeWithProtobuf(message);
    }


    std::string getMessageUnsuscription(topic_t topic){
        std::string message = "";
        message += UNSUSCRIBE_TO_TOPIC;
        message += SEPARATOR;
        message += topic;

        return serializeWithProtobuf(message);
    }
}
#endif

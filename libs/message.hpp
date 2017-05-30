#ifndef __MESSAGE__HPP__
#define __MESSAGE__HPP__

namespace octopus{

    class Message{

    private:
        topic_t topic;
        topic_message_t message;
        std::string request;
        std::string response;



    public:
        Message(topic_t topic, topic_message_t message){
            this->topic = topic;
            this->message = message;
        }

        Message(std::string response){
            this->response = response;
        }

        void build(){
            request = topic + SPLITTER + message;
        }

        void debuild(){

            assert(response.size() > 0);

            topic = response.substr(0, response.find(SPLITTER));
            message = response.substr(response.find(SPLITTER) + SPLITTER.length(), response.size());


        }

        std::string getRequest(){

            return request;

        }

        topic_t getTopic(){
            return topic;
        }

        topic_message_t getMessage(){
            return message;
        }


    };



}


#endif

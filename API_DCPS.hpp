#ifndef __API_DCPS__
#define __API_DCPS__

#include "api/Subscriber.hpp"
#include "api/Publisher.hpp"
#include "api/DataWriter.hpp"
#include "api/DataWriterListener.hpp"
#include "api/PublisherListener.hpp"
#include "api/DataReader.hpp"
#include "api/DataReaderListener.hpp"
#include "api/SubscriberListener.hpp"
#include "api/DomainParticipant.hpp"
#include "api/tinydds/MessagePayload.hpp"

#include "octopusAPI.hpp"

namespace octopus{
    class octoPublisher : public virtual Publisher{
    public:
        DataWriter          create_datawriter(std::string topic, DataWriterListener listener){

        }
        int                 set_listener(PublisherListener listener){

        }
        PublisherListener   get_listener(){

        }
        void                publish(DataWriter datawriter, MessagePayload msg){

        }
    };



    class octoSubscriber: public virtual Subscriber{
    public:
        DataReader          create_datareader(std::string topic, DataReaderListener listener){

        }
        void                notify_datareader(){

        }
        int                 set_listener(SubscriberListener listener){

        }
        SubscriberListener  get_listener(){

        }
        DomainParticipant   get_participant(){

        }
    };

}

#endif

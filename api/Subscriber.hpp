#ifndef __SUBSCRIBER__HPP__
#define __SUBSCRIBER__HPP__

#include "Entity.hpp"
#include "DataReader.hpp"
#include "DataReaderListener.hpp"
#include "SubscriberListener.hpp"
#include "DomainParticipant.hpp"

namespace octopus {
    class Subscriber : public Entity {
    public:
        virtual DataReader          create_datareader(std::string topic, DataReaderListener listener);
        virtual void                notify_datareader();
        virtual int                 set_listener(SubscriberListener listener);
        virtual SubscriberListener  get_listener();
        virtual DomainParticipant   get_participant();
        //virtual void                setOERP(OERP oerp);
    };
} /* octopus */

#endif

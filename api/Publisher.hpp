#ifndef __PUBLISHER__HPP__
#define __PUBLISHER__HPP__

#include "Entity.hpp"
#include "DataWriter.hpp"
#include "DataWriterListener.hpp"
#include "PublisherListener.hpp"
#include "DataWriter.hpp"
#include "tinydds/MessagePayload.hpp"

namespace octopus {
    class Publisher : public Entity {
    public:
        virtual DataWriter          create_datawriter(std::string topic, DataWriterListener listener);
        virtual int                 set_listener(PublisherListener listener);
        virtual PublisherListener   get_listener();
        virtual void                publish(DataWriter datawriter, MessagePayload msg);
        //virtual void                setOERP(OERP oerp);
    };
} /* octopus */

#endif

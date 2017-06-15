#ifndef __DATAWRITER__HPP__
#define __DATAWRITER__HPP__

#include "DataWriterListener.hpp"
#include "Publisher.hpp"
#include "tinydds/MessagePayload.hpp"
#include "DataWriterListener.hpp"

namespace octopus {
    class Publisher;
    class DataWriter {
    public:
        virtual DataWriterListener      get_listener();
        virtual std::string             get_topic();
        virtual Publisher*              get_publisher();
        virtual void                    write(MessagePayload msg);
        virtual int                     set_listener(DataWriterListener listener);
    };
} /* octopus */

#endif

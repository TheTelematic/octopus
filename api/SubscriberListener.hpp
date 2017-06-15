#ifndef __SUBSCRIBERLISTENER__HPP__
#define __SUBSCRIBERLISTENER__HPP__

#include "DataReaderListener.hpp"
#include "Subscriber.hpp"

namespace octopus {
    class SubscriberListener : public DataReaderListener {
    public:
        virtual void            on_data_on_readers(Subscriber subs);
    };
} /* octopus */

#endif

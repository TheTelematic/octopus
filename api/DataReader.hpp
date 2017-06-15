#ifndef __DATAREADER__HPP__
#define __DATAREADER__HPP__

#include "DataReaderListener.hpp"
#include "Subscriber.hpp"

namespace octopus {
    class Subscriber;
    class DataReader {
    public:
        virtual int                 set_listener(DataReaderListener listener);
        virtual DataReaderListener  get_listener();
        virtual Subscriber*         get_subscriber();
    };
} /* octopus */

#endif

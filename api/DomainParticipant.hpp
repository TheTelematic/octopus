#ifndef __DOMAINPARTICIPANT__HPP__
#define __DOMAINPARTICIPANT__HPP__

#include "Entity.hpp"
#include "PublisherListener.hpp"
#include "SubscriberListener.hpp"
#include "Publisher.hpp"
#include "Subscriber.hpp"

namespace octopus {
    class DomainParticipant : public Entity {
    public:
        virtual Publisher           create_publisher(PublisherListener listener);
        virtual Subscriber          create_subscriber(SubscriberListener listener);
    };
} /* octopus */

#endif

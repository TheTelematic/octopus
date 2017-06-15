#ifndef __MESSAGEPAYLOAD__HPP__
#define __MESSAGEPAYLOAD__HPP__


namespace octopus {
    class MessagePayload{
    public:
        virtual void        marshall(uint8_t *data, size_t &size);
        virtual void        demarshall(uint8_t *data, size_t &size);
        virtual int         size();
    };
} /* octopus */

#endif

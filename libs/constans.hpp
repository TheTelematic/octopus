#ifndef __CONSTANTS__HPP__
#define __CONSTANTS__HPP__



namespace octopus{

    const uint16_t DISCOVER_PORT = 5085;
    const uint16_t SUSCRIBER_PORT = 5075;
    const uint16_t PUBLISHER_PORT = 5065;

    static const std::string SPLITTER = "#__#";

}

#define BROADCAST_ADDRESS {255, 255, 255, 255}
#define BROADCAST_ADDRESS_STR "255.255.255.255"
#define KEEPALIVE_TOPIC "KEEPALIVE"

#endif

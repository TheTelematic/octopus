#ifndef CREATE_TOPIC
#define CREATE_TOPIC "CREATE_TOPIC"
#endif

#ifndef SUSCRIBE
#define SUSCRIBE "SUSCRIBE"
#endif

#ifndef PUBLISH
#define PUBLISH "PUBLISH"
#endif

#ifndef UNSUSCRIBE
#define UNSUSCRIBE "UNSUSCRIBE"
#endif

#ifndef REMOVE_TOPIC
#define REMOVE_TOPIC "REMOVE_TOPIC"
#endif

#ifndef HELP
#define HELP "Available commands:\n \
CREATE_TOPIC {name_of_topic}    -> create a topic\n \
SUSCRIBE {name_of_topic}        -> suscribe to an added topic\n \
PUBLISH {message} {name_of_topic} -> publish a message of a topic\n \
UNSUSCRIBE {name_of_topic}      -> unsuscribe to an added topic\n \
REMOVE_TOPIC {name_of_topic}    -> remove a created topic\n"
#endif

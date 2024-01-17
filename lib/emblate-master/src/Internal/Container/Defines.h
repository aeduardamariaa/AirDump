#ifndef EMBLATE_DEFINES_H
#define EMBLATE_DEFINES_H

namespace Emblate
{
#ifndef int8_t
    typedef char int8_t;
#endif

#ifndef int16_t
    typedef short int16_t;
#endif

#ifndef int32_t
    typedef long int32_t;
#endif

#ifndef int64_t
    typedef long long int64_t;
#endif

#ifndef uint8_t
    typedef unsigned char uint8_t;
#endif

#ifndef uint16_t
    typedef unsigned short uint16_t;
#endif

#ifndef uint32_t
    typedef unsigned long uint32_t;
#endif

#ifndef uint64_t
    typedef unsigned long long uint64_t;
#endif

#ifndef size_t
    typedef uint16_t size_t;
#endif
}

#endif /* EMBLATE_DEFINES_H */

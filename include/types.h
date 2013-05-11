#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>

#include "defines.h"

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct block {
        u16 id;
        void *sprite;
} block;

#endif /* TYPES_H */

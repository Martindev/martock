#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct block {
        u16 id;
} block;

typedef struct block_profile {
        u8 opacity; /* Render opacity. */
        u8 density; /* Difficulty to break. */
        u8 gravity; /* Does it fall? */
        u8 weight; /* Fall speed/pack weight. */
} block_profile;

typedef struct chunk {
        u8 rules;
        int position;
        struct chunk *right;
        struct chunk *left;
        u8 heights[CHUNK_WIDTH];
        block fore[CHUNK_WIDTH][CHUNK_HEIGHT];
        block back[CHUNK_WIDTH][CHUNK_HEIGHT];
} chunk;

#endif /* TYPES_H */

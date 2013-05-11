#ifndef CHUNK_H
#define CHUNK_H

/* Chunk dimensions. */
enum {
        CHUNK_WIDTH  = 40,
        CHUNK_HEIGHT = 500
};

/* Chunk level limits. */
enum {
        CHUNK_SKY     =  50,
        CHUNK_SURFACE = 100,
        CHUNK_SOIL    = 150,
        CHUNK_MANTLE  = 450,
        CHUNK_CORE    = 500
};

typedef enum chunk_gen_id {
        CHUNK_GEN  = 0,
        CHUNK_LOAD = 1
} chunk_gen_id;

typedef struct chunk {
        u16 position;
        block grid[CHUNK_WIDTH][CHUNK_HEIGHT];
} chunk;

/* Allocate memory for and initialize a new chunk. */
chunk *chunk_new (chunk_gen_id id, u16 pos, chunk *right, chunk *left);

/* Save the data from an open chunk and free its memory. */
void chunk_close (chunk *ch);

#endif /* CHUNK_H */
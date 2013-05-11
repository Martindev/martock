#ifndef CHUNK_H
#define CHUNK_H

/* Chunk dimensions. */
enum {
        CHUNK_WIDTH  = 40,
        CHUNK_HEIGHT = 500
};

/* Chunk level beginnings. */
enum {
        CHUNK_SOIL    =  50,
        CHUNK_MANTLE  = 150,
        CHUNK_CORE    = 450
};

/* Generator flags. */
enum {
        CHUNK_FLAT      = 0x01,
        CHUNK_NO_CAVES  = 0x02,
        CHUNK_NO_HILLS  = 0x04,
        CHUNK_NO_PLANTS = 0x08,
        CHUNK_FULL      = 0x10
};

/* Relative positions. */
enum {
        CHUNK_RIGHT = 0,
        CHUNK_LEFT  = 1
};

/* Cellular automata modes. */
enum {
        CHUNK_CAVE_BORDER = 10,
        CHUNK_CAVE_DEPTH  = 5,
        CHUNK_CAVE_SEED   = 40
};

typedef struct chunk {
        u16 position;
        block grid[CHUNK_WIDTH][CHUNK_HEIGHT];
} chunk;

/* Load a chunk from file. */
chunk *chunk_load (u16 pos);

/* Generate a new chunk based on neighbors. */
chunk *chunk_generate (u8 rules, const chunk *neighbor, u8 side);

/* Represent the chunk data visually in a text document. */
void chunk_save_text (const chunk *ch);

/* Save the data from an open chunk and free its memory. */
void chunk_close (chunk *ch);

#endif /* CHUNK_H */
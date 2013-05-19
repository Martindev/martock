#ifndef CHUNK_H
#define CHUNK_H

/* Chunk dimensions. */
enum {
        CHUNK_WIDTH  = 80,
        CHUNK_HEIGHT = 200
};

/* Chunk level beginnings. */
enum {
        CHUNK_SOIL    = CHUNK_HEIGHT / 4,
        CHUNK_MANTLE  = CHUNK_HEIGHT / 3,
        CHUNK_CORE    = (CHUNK_HEIGHT / 4) * 3
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
        CHUNK_RIGHT           = 0,
        CHUNK_LEFT            = 1,
        CHUNK_RENDER_DISTANCE = 5
};

/* Cellular automata modes. */
enum {
        CHUNK_BORDER         = 3,
        CHUNK_HILL           = CHUNK_HEIGHT / 10,
        CHUNK_SMOOTH_RADIUS  = CHUNK_WIDTH / 10,
        CHUNK_CAVE_SEED      = 40,
        CHUNK_CAVE_RULE      = 4
};

typedef struct chunk {
        u8 rules;
        int position;
        struct chunk *right;
        struct chunk *left;
        u8 heights[CHUNK_WIDTH];
        block fore[CHUNK_WIDTH][CHUNK_HEIGHT];
        block back[CHUNK_WIDTH][CHUNK_HEIGHT];
} chunk;

/* Load a chunk from file. */
chunk *chunk_load (int pos);

/* Generate a new chunk based on neighbors. */
chunk *chunk_generate (u8 rules, const chunk *neighbor, u8 side);

/* Interactively view the chunk. */
void chunk_view (chunk *ch);

/* Render a chunk to an image file for preview. */
void chunk_save_img (chunk *ch);

/* Represent the chunk data visually in a text document. */
void chunk_save_text (const chunk *ch);

/* Save the data from an open chunk and free its memory. */
void chunk_close (chunk *ch);

#endif /* CHUNK_H */

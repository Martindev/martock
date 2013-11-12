#ifndef DEFINES_H
#define DEFINES_H

#define C 10000
#define SAVE_LEN 100

/* Global state variables. */
extern char save[SAVE_LEN];

/* Block id's. */
enum {
        BLOCK_SKY     = 0,
        BLOCK_GRASS   = 1,
        BLOCK_SOIL    = 2,
        BLOCK_STONE   = 3,
        BLOCK_IRON    = 4,
        BLOCK_MITHRIL = 5,
        BLOCK_DIAMOND = 6,
        BLOCK_TRUNK   = 7,
        BLOCK_LEAVES  = 8
};

/* Frequency. */
enum {
        BLOCK_IRON_ODD    = 30,
        BLOCK_MITHRIL_ODD = 20,
        BLOCK_DIAMOND_ODD = 10
};

/* Block metadata. */
enum {
        BLOCK_COUNT = 9, /* Quantity of blocks. */
        BLOCK_SIZE = 60, /* Sprite resolution. */
        BLOCK_SCALE = 1, /* Render scale. */
};

/* Visibilities. */
enum {
        BLOCK_TRANSPARENT = 0,
        BLOCK_OPAQUE = 255
};

/* Chunk dimensions. */
enum {
        CHUNK_WIDTH  = 500,
        CHUNK_HEIGHT = 500
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
        CHUNK_TREE           = 20,
        CHUNK_HILL           = CHUNK_HEIGHT / 5,
        CHUNK_SMOOTH_RADIUS  = CHUNK_WIDTH / 8,
        CHUNK_CAVE_SEED      = 40,
        CHUNK_CAVE_RULE      = 4
};

#endif /* DEFINES_H */

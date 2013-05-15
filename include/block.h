#ifndef BLOCK_H
#define BLOCK_H

#include <martock.h>

/* Block id's. */
enum {
        BLOCK_SKY   = 0,
        BLOCK_GRASS = 1,
        BLOCK_SOIL  = 2,
        BLOCK_STONE = 3,
        BLOCK_SAND  = 4,
        BLOCK_WATER = 5
};

/* Block metadata. */
enum {
        BLOCK_COUNT = 6,  /* Quantity of blocks. */
        BLOCK_SIZE  = 60, /* Sprite resolution. */
        BLOCK_SCALE = 3,  /* Render scale. */
};

typedef struct block {
        u16 id;
} block;

typedef struct block_profile {
        u8 opacity; /* Render opacity. */
        u8 density; /* Difficulty to break. */
        u8 gravity; /* Does it fall? */
        u8 weight;  /* Fall speed/pack weight. */
} block_profile;

/* Load the blocks texture file. */
int block_init (const char *tex);

/* Get a pointer to a sprite's sub bitmap. */
ALLEGRO_BITMAP *block_sprite(u16 id);

/* Get a pointer to a sprite's background sub bitmap. */
ALLEGRO_BITMAP *block_back (u16 id);

/* Profile Accessers */
u8 block_opacity (u16 id);
u8 block_density (u16 id);
u8 block_gravity (u16 id);
u8 block_weight  (u16 id);

/* Free the block module's memory. */
void blocks_deinit ();

#endif /* BLOCK_H */
#ifndef BLOCK_H
#define BLOCK_H

#include <martock.h>

/* Load the blocks texture file. */
int block_init (const char *tex);

/* Render a tile. */
void block_draw (block fg, block bg, int x, int y);

/* Get a pointer to a sprite's sub bitmap. */
ALLEGRO_BITMAP *block_sprite(u16 id);

/* Get a pointer to a sprite's background sub bitmap. */
ALLEGRO_BITMAP *block_back (u16 id);

/* Profile Accessers */
u8 block_opacity (u16 id);
u8 block_density (u16 id);
u8 block_gravity (u16 id);
u8 block_weight (u16 id);

/* Free the block module's memory. */
void block_deinit ();

#endif /* BLOCK_H */
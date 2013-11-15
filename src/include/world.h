#ifndef WORLD_H
#define WORLD_H

/* Create a world of the provided size and load it. */
chunk *world_generate (const char *s, u16 size, u8 rules);

/* Save a world to disk and unload it. */
void world_close (chunk *ch);

/* Provide a snapshot of the world with the given dimensions. */
void world_get_img(int c, int x, int y, u32 w, u32 h, ALLEGRO_BITMAP *b);

/* Get a specific block in the world. */
u16 world_get_block(int c, u32 x, u32 y);

/* Find the chunk at the border of the (loaded) world. */
chunk *world_edge (chunk *ch, u8 side);

/* Shift a world to either side, maintaining render distance. */
chunk *world_shift (chunk *ch, u8 side);

/* Open a viewer to see the results of world generation; dev only. */
void world_view ();

#endif /* WORLD_H */

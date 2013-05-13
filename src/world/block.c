#include <martock.h>

static ALLEGRO_BITMAP *sheet;
static ALLEGRO_BITMAP *sprites[BLOCK_COUNT];

/**
 *  Load the blocks texture file. If one is provided, load an alternate
 *  texture file.
 *
 *  @tex: texture file
 *
 *  @return: 0 no error
 *           1 file not found/corrupt
 *           2 file not wide enough
 *           3 file not tall enough
 */
int block_init (const char *tex)
{
        const char *name = (tex) ? tex : "assets/blocks.tga";

        if (!(sheet = al_load_bitmap(name)))
                return 1;

        if (al_get_bitmap_width(sheet) < BLOCK_COUNT * BLOCK_SIZE)
                return 2;

        if (al_get_bitmap_height(sheet) < BLOCK_SIZE)
                return 3;

        memset(sprites, 0, sizeof(ALLEGRO_BITMAP*) * BLOCK_COUNT);
        for (int i = 0; i < BLOCK_COUNT; i++)
                sprites[i] = al_create_sub_bitmap(sheet, i * BLOCK_SIZE, 0,
                                                  BLOCK_SIZE, BLOCK_SIZE);

        return 0;
}

/**
 *  Return a pointer to the requested sprite for drawing.
 *
 *  @id: type of block/sprite
 *
 *  @return: pointer
 */
ALLEGRO_BITMAP *block_sprite(u16 id)
{
        return sprites[id];
}

/**
 *  Deallocate all resources used by the block sprites.
 */
void blocks_deinit ()
{
        if (sheet)
                al_destroy_bitmap(sheet);
}
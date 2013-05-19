#include <martock.h>

static ALLEGRO_BITMAP *sheet;
static ALLEGRO_BITMAP *sprites[BLOCK_COUNT];
static ALLEGRO_BITMAP *backs[BLOCK_COUNT];

static block_profile profiles[BLOCK_COUNT];

static void init_profiles ()
{
        profiles[BLOCK_SKY].opacity = 0;
        profiles[BLOCK_SKY].density = 0;
        profiles[BLOCK_SKY].gravity = 0;
        profiles[BLOCK_SKY].weight = 0;

        profiles[BLOCK_GRASS].opacity = 255;
        profiles[BLOCK_GRASS].density = 10;
        profiles[BLOCK_GRASS].gravity = 0;
        profiles[BLOCK_GRASS].weight = 10;

        profiles[BLOCK_SOIL].opacity = 255;
        profiles[BLOCK_SOIL].density = 10;
        profiles[BLOCK_SOIL].gravity = 0;
        profiles[BLOCK_SOIL].weight = 15;

        profiles[BLOCK_STONE].opacity = 255;
        profiles[BLOCK_STONE].density = 30;
        profiles[BLOCK_STONE].gravity = 0;
        profiles[BLOCK_STONE].weight = 40;

        profiles[BLOCK_SAND].opacity = 255;
        profiles[BLOCK_SAND].density = 3;
        profiles[BLOCK_SAND].gravity = 0;
        profiles[BLOCK_SAND].weight = 30;

        profiles[BLOCK_WATER].opacity = 150;
        profiles[BLOCK_WATER].density = 0;
        profiles[BLOCK_WATER].gravity = 30;
        profiles[BLOCK_WATER].weight = 20;
}

/**
* Load the blocks texture file. If one is provided, load an alternate
* texture file.
*
* @tex: texture file
*
* @return: 0 no error
* 1 file not found/corrupt
* 2 file not wide enough
* 3 file not tall enough
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

        init_profiles();

        ALLEGRO_BITMAP *temp = al_get_target_bitmap();
        ALLEGRO_BITMAP *map = al_create_bitmap(BLOCK_COUNT * BLOCK_SIZE,
                                               BLOCK_SIZE * 2);
        al_set_target_bitmap(map);
        al_draw_bitmap(sheet, 0, 0, 0);
        al_draw_tinted_bitmap(sheet, al_map_rgb(100, 100, 100), 0, BLOCK_SIZE, 0);

        if (temp)
                al_set_target_bitmap(temp);

        al_destroy_bitmap(sheet);
        sheet = map;

        memset(sprites, 0, sizeof(ALLEGRO_BITMAP*) * BLOCK_COUNT);
        for (int i = 0; i < BLOCK_COUNT; i++)
                sprites[i] = al_create_sub_bitmap(sheet, i * BLOCK_SIZE, 0,
                                                  BLOCK_SIZE, BLOCK_SIZE);

        memset(backs, 0, sizeof(ALLEGRO_BITMAP*) * BLOCK_COUNT);
        for (int i = 0; i < BLOCK_COUNT; i++)
                backs[i] = al_create_sub_bitmap(sheet, i * BLOCK_SIZE,
                                                BLOCK_SIZE,
                                                BLOCK_SIZE, BLOCK_SIZE);

        return 0;
}

/**
* Draw a tile to the target bitmap, handling overlays appropriately. Tiles in
* the background should be visible if the foreground tile is less than opaque.
*
* @fg: foreground block
* @bg: background block
* @x: horizontal pixel coordinate
* @y: vertical pixel coordinate
* @scale: size to draw the tile
*/
void block_draw (block fg, block bg, int x, int y, int scale)
{
        if ((fg.id < 0) || (fg.id >= BLOCK_COUNT)) {
                fprintf(stderr, "Foreground err: %d", fg.id);
                return;
        }

        if ((bg.id < 0) || (bg.id >= BLOCK_COUNT)) {
                fprintf(stderr, "Background err: %d", bg.id);
                return;
        }

        if ((profiles[fg.id].opacity < BLOCK_OPAQUE) && bg.id) {
                al_draw_scaled_bitmap(backs[bg.id], 0, 0, BLOCK_SIZE,
                                      BLOCK_SIZE, x, y, scale, scale, 0);
                if (fg.id)
                        al_draw_tinted_scaled_bitmap(sprites[fg.id],
                                al_map_rgba_f(1, 1, 1, profiles[fg.id].opacity),
                                0, 0, BLOCK_SIZE, BLOCK_SIZE, x, y, scale,
                                scale, 0);
        } else
                al_draw_scaled_bitmap(sprites[fg.id], 0, 0, BLOCK_SIZE,
                                      BLOCK_SIZE, x, y, scale, scale, 0);
}

/**
* Return a pointer to the requested sprite for drawing.
*
* @id: type of block/sprite
*
* @return: pointer
*/
ALLEGRO_BITMAP *block_sprite (u16 id)
{
        return sprites[id];
}

/**
* Return a pointer to the requested back sprite for drawing. Back sprites
* are darkened, for rendering in the background layer.
*
* @id: type of block/sprite
*
* @return: pointer
*/
ALLEGRO_BITMAP *block_back (u16 id)
{
        return backs[id];
}

/**
* Access the profile property for the requested block type.
*
* @id: block type
*
* @return: profile value
*/
u8 block_opacity (u16 id)
{
        return profiles[id].opacity;
}

u8 block_density (u16 id)
{
        return profiles[id].density;
}

u8 block_gravity (u16 id)
{
        return profiles[id].gravity;
}

u8 block_weight (u16 id)
{
        return profiles[id].weight;
}

/**
* Deallocate all resources used by the block sprites.
*/
void blocks_deinit ()
{
        if (sheet)
                al_destroy_bitmap(sheet);
}
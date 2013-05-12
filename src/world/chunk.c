#include <martock.h>

/**
 *  Load a chunk from file if it exists.
 *
 *  @pos: the position of the chunk in the world
 *
 *  @return: the loaded chunk; NULL on failure
 */
chunk *chunk_load (u16 pos)
{
        chunk *ch = NULL;
        FILE *file = NULL;

        /* Return if the memory allocation fails. */
        if (!(ch = calloc(1, sizeof(chunk))))
                return NULL;

        /* Return if the file can't be found. */
        if (!(file = vfopen("rb", "world/chunks/%d.ch", pos)))
                return NULL;

        fread(ch, sizeof(chunk), 1, file);
        return ch;
}

/**
 *  Construct a new chunk according the provided rules using cellular automata.
 *
 *  @rules: cellular automata rules
 *  @neighbor: the chunk this is appending to
 *  @side: which side it's appending to the neighbor
 *
 *  @return: the newly generated chunk; NULL on failure
 */
chunk *chunk_generate (u8 rules, const chunk *neighbor, u8 side)
{
        chunk *ch = NULL;

        /* Return if the memory allocation fails. */
        if (!(ch = calloc(1, sizeof(chunk))))
                return NULL;

        /* Set the defaults for each vertical level. */
        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = 0; j < CHUNK_SOIL; j++)
                        ch->grid[i][j].id = BLOCK_SKY;

        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = CHUNK_SOIL; j < CHUNK_MANTLE; j++)
                        ch->grid[i][j].id = BLOCK_SOIL;

        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = CHUNK_MANTLE; j < CHUNK_HEIGHT; j++)
                        ch->grid[i][j].id = BLOCK_STONE;

        /* If a flat chunk was requested, it's done. */
        if (rules & CHUNK_FLAT)
                return ch;

        /* Initial seeding. */
        srand(time(NULL));
        for (int i = CHUNK_BORDER; i < CHUNK_WIDTH - CHUNK_BORDER; i++)
                for (int j = CHUNK_MANTLE; j < CHUNK_CORE; j++)
                        if ((rand() % 100) < CHUNK_CAVE_SEED)
                                ch->grid[i][j].id = BLOCK_SKY;

        /* Cave automata. */
        for (int c = 0; c < CHUNK_CAVE_DEPTH; c++)
                for (int i = CHUNK_BORDER; i < CHUNK_WIDTH - CHUNK_BORDER; i++)
                        for (int j = CHUNK_MANTLE; j < CHUNK_CORE; j++) {
                                int t = 0;

                                t = (ch->grid[i - 1][j - 1].id) ? (t + 1) : t;
                                t = (ch->grid[i - 1][j    ].id) ? (t + 1) : t;
                                t = (ch->grid[i - 1][j + 1].id) ? (t + 1) : t;

                                t = (ch->grid[i    ][j - 1].id) ? (t + 1) : t;
                                t = (ch->grid[i    ][j + 1].id) ? (t + 1) : t;

                                t = (ch->grid[i + 1][j - 1].id) ? (t + 1) : t;
                                t = (ch->grid[i + 1][j    ].id) ? (t + 1) : t;
                                t = (ch->grid[i + 1][j + 1].id) ? (t + 1) : t;

                                if (t > CHUNK_CAVE_RULE)
                                        ch->grid[i][j].id = BLOCK_STONE;
                                else
                                        ch->grid[i][j].id = BLOCK_SKY;
                        }

        return ch;
}

/**
 *  Render a chunk to an image file to preview it.
 *
 *  @ch: the chunk to preview
 */
void chunk_save_img (chunk *ch)
{
        if (!ch)
                return;

        int scale = BLOCK_SIZE / BLOCK_SCALE;
        int width = scale * CHUNK_WIDTH;
        int height = scale * CHUNK_HEIGHT;

        ALLEGRO_BITMAP *canvas = al_create_bitmap(width, height);

        if (!canvas)
                return;

        al_set_target_bitmap(canvas);

        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = 0; j < CHUNK_HEIGHT; j++) {
                        al_draw_scaled_bitmap(block_sprite(ch->grid[i][j].id),
                                              0, 0, BLOCK_SIZE, BLOCK_SIZE,
                                              i * scale, j * scale,
                                              scale, scale, 0);
                }

        char temp[100] = {0};
        sprintf(temp, "world/chunks/%d.png", ch->position);
        al_save_bitmap(temp, canvas);
        al_destroy_bitmap(canvas);
}

/**
 *  Create a lingual save representing the chunk visually with text.
 *
 *  @ch: pointer to the chunk to save
 */
void chunk_save_text (const chunk *ch)
{
        if (!ch)
                return;

        FILE *file = vfopen("w", "world/chunks/%d.txt", ch->position);

        if (file)
                for (int j = 0; j < CHUNK_HEIGHT; j++) {
                        for (int i = 0; i < CHUNK_WIDTH; i++)
                                fprintf(file, "%2d", ch->grid[i][j].id);
                        fprintf(file, "\n");
                }
}

/**
 *  Save the data from the chunk if a save file structure is present, and then
 *  free the memory used by the chunk.
 *
 *  @ch: pointer to the chunk memory
 */
void chunk_close (chunk *ch)
{
        if (!ch)
                return;

        FILE *file = vfopen("wb", "world/chunks/%d.ch", ch->position);

        if (file)
                fwrite(ch, sizeof(chunk), 1, file);

        free(ch);
}
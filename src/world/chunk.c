#include <stdio.h>
#include <stdlib.h>
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
                for (int j = CHUNK_MANTLE; j < CHUNK_CORE; j++)
                        ch->grid[i][j].id = BLOCK_STONE;

        /* If a flat chunk was requested, it's done. */
        if (rules & CHUNK_FLAT)
                return ch;

        return ch;
}

/**
 *  Create a lingual save representing the chunk visually with text.
 *
 *  @ch: pointer to the chunk to save
 */
void chunk_save_text (const chunk *ch)
{
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
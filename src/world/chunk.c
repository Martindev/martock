#include <stdio.h>
#include <stdlib.h>
#include <martock.h>

/**
 *  Allocate memory for and generate a chunk or load a chunk (refer to gen_id).
 *
 *  @id: mode to fill the allocated memory; either load a chunk from file, or
 *       generate a new one based on the provided rule
 *  @pos: position relative to the world origin
 *  @right: pointer to the chunk right of the currently generating chunk
 *  @left: pointer to the chunk left of the currently generating chunk
 *
 *  @return: a pointer to the new memory; NULL on failure
 */
chunk *chunk_new (chunk_gen_id id, u16 pos, chunk *right, chunk *left)
{
        chunk *ch = NULL;
        chunk *neighbor = NULL;

        /* If it isn't the origin chunk, at least one neighbor is required. */
        if ((id == CHUNK_GEN) && (pos) && (!right && !left))
                return NULL;

        /* Associate the neighbor for reference. */
        neighbor = (right) ? right : left;

        ch = calloc(1, sizeof(chunk));

        if (!ch)
                return NULL;

        ch->position = pos;

        /* Set the defaults for each vertical level. */
        for (int j = 0; j < CHUNK_SKY; j++)
                for (int i = 0; i < CHUNK_WIDTH; i++)
                        ch->grid[i][j].id = BLOCK_SKY;

        for (int j = CHUNK_SKY; j < CHUNK_SKY + 1; j++)
                for (int i = 0; i < CHUNK_WIDTH; i++)
                        ch->grid[i][j].id = BLOCK_GRASS;

        for (int j = CHUNK_SKY + 1; j < CHUNK_SOIL; j++)
                for (int i = 0; i < CHUNK_WIDTH; i++)
                        ch->grid[i][j].id = BLOCK_SOIL;

        for (int j = CHUNK_SOIL; j < CHUNK_CORE; j++)
                for (int i = 0; i < CHUNK_WIDTH; i++)
                        ch->grid[i][j].id = BLOCK_STONE;

        return ch;
}

/* Save the data from an open chunk and free its memory. */
void chunk_close (chunk *ch)
{
        if (!ch)
                return;

        char name[100] = {0};
        sprintf(name, "world/chunks/%d.ch", ch->position);
        FILE *file = fopen(name, "w");

        if (file)
                for (int j = 0; j < CHUNK_HEIGHT; j++) {
                        for (int i = 0; i < CHUNK_WIDTH; i++)
                                fprintf(file, "%2d", ch->grid[i][j].id);
                        fprintf(file, "\n");
                }

        free(ch);
}
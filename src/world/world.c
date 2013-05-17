#include <martock.h>

/**
 *  Create a world of the requested preset size following the requested rules.
 *
 *  @size: chunks to generate initially on either side of the origin
 *  @rules: rules for chunk generation
 *
 *  @return: pointer to middle chunk
 */
chunk *world_gen (u16 size, u8 rules)
{
        if (size < CHUNK_RENDER_DISTANCE)
                return NULL;

        chunk *ch = chunk_generate(rules, NULL, 0);
        ch->position = 0 - size;
        chunk *ita = NULL, *itb = NULL;

        /* Generate the world. */
        ita = ch;
        for (int i = 0 - size; i <= size; i++) {
                ita = chunk_request(ita, CHUNK_RIGHT, rules);
        }

        /* Save them all to disk. */
        ita = world_edge(ita, CHUNK_LEFT);
        while (ita->right) {
                itb = ita;
                ita = ita->right;
                chunk_save_text(itb);
                chunk_close(itb);
        }

        /* Load CHUNK_RENDER_DISTANCE chunks back into memory. */
        for (int i = 0 - CHUNK_RENDER_DISTANCE;
                 i <= CHUNK_RENDER_DISTANCE; i++) {
                itb = chunk_request(ita, CHUNK_RIGHT, rules);
                ch = (!i) ? itb : ch;
                ita = ita->right;
        }

        return ch;
}

/**
 *  Move the world's doubly linked list of chunks around to accomodate moves
 *  of a player or camera. Load/unload chunks from memory using the constant
 *  for render distance as a guide.
 *
 *  @ch: current center chunk
 *  @side: direction of request
 *
 *  @return: new center chunk
 */
chunk *world_shift (chunk *ch, u8 side)
{
        if (!ch)
                return NULL;

        if ((side != CHUNK_RIGHT) && (side != CHUNK_LEFT))
                return NULL;

        chunk *new, *drop;

        /* Find outermost loaded chunk. */
        drop = world_edge(ch, (side == CHUNK_LEFT) ? CHUNK_RIGHT : CHUNK_LEFT);
        new = world_edge(ch, (side == CHUNK_LEFT) ? CHUNK_LEFT : CHUNK_RIGHT);

        chunk_request(new, side, CHUNK_FULL);
        chunk_close(drop);

        return (side == CHUNK_LEFT) ? ch->left : ch->right;
}

/**
 *  Find the egde of the (loaded) world and return a pointer to it.
 *
 *  @ch: current center chunk
 *  @side: left or right edge
 *
 *  @return: pointer to the outermose chunk
 */
chunk *world_edge (chunk *ch, u8 side)
{
        if (!ch)
                return NULL;

        chunk *it = ch;

        if (side == CHUNK_LEFT)
                while (it->left)
                        it = it->left;
        else
                while (it->right)
                        it = it->right;

        return it;
}
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
        if (size <= 0)
                return NULL;

        chunk *ch = chunk_generate(rules, NULL, 0);
        chunk *ita = NULL, *itb = ch;

        for (int i = 1; i <= size; i++) {
                ita = chunk_generate(rules, itb, CHUNK_RIGHT);
                itb->right = ita;
                ita->left = itb;
                itb = ita;
        }

        itb = ch;
        for (int i = -1; i >= (size * -1); i--) {
                ita = chunk_generate(rules, itb, CHUNK_LEFT);
                itb->left = ita;
                ita->right = itb;
                itb = ita;
        }

        /* TODO: close world now. */
        /* TODO: Load CHUNK_RENDER_DISTANCE chunks back into memory. */

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

        const chunk *it, *new;
        chunk *drop;

        /* Find outermost loaded chunk. */
        for (int i = 1; i < CHUNK_RENDER_DISTANCE; i++)
                it = (side == CHUNK_RIGHT) ? it->right : it->left;
        new = it;

        for (int i = 1; i < CHUNK_RENDER_DISTANCE; i++)
                it = (side == CHUNK_LEFT) ? it->right : it->left;
        drop = it;

        new = chunk_request(new, side, CHUNK_FULL);
        chunk_close(drop);

        return (side == CHUNK_LEFT) ? ch->left : ch->right;
}
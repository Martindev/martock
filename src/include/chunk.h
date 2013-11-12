#ifndef CHUNK_H
#define CHUNK_H

#include <martock.h>

/* Load a chunk from file. */
chunk *chunk_load (int pos);

/* Generate a new chunk based on neighbors. */
chunk *chunk_generate (u8 rules, const chunk *neighbor, u8 side);

/* Interactively view the chunk. */
void chunk_view (chunk *ch);

/* Render a chunk to an image file for preview. */
void chunk_save_img (chunk *ch);

/* Represent the chunk data visually in a text document. */
void chunk_save_text (const chunk *ch);

/* Save the data from an open chunk and free its memory. */
void chunk_close (chunk *ch);

#endif /* CHUNK_H */

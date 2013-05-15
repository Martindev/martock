#ifndef WORLD_H
#define WORLD_H

#include <martock.h>

/* Initialize a world. */
chunk *world_gen (u16 size, u8 rules);

/* Shift the chunks currently in memory to accomodate viewer or player moves. */
chunk *world_shift (chunk *ch, u8 side);

#endif /* WORLD_H */
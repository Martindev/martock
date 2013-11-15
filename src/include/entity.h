#ifndef ENTITY_H
#define ENTITY_H

#include <martock.h>

/* Make an entity of the requested race. */
entity entity_make(int c, double x, double y, race_t r);

/* Apply physics to the entity. */
void entity_update (entity *e);

#endif /* ENTITY_H */
#include <martock.h>

/**
 *  Create an entity at the given position with the requested race.
 *
 *  @c: chunk position
 *  @x: x coord
 *  @y: y coord
 *  @r: race
 */
entity entity_make(int c, double x, double y, race_t r)
{
        entity some;

        some.c = c;
        some.x = x;
        some.y = y;
        some.oc = c;
        some.ox = x;
        some.oy = y;
        some.race = r;
        some.velv = 0;
        some.velh = 0;

        if (r == RACE_HERO) {
                some.w = HERO_WIDTH;
                some.h = HERO_HEIGHT;
        }

        some.dir = DIR_LEFT;

        return some;
}

/**
 *  This should handle velocity, movement, gravity, collisions, etc for an
 *  entity.
 *
 *  @e: entity to update
 *  @d: the direction(s) the entity is now trying to move, if any
 */
void entity_update(entity *e)
{
}
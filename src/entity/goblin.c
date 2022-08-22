/*
 * goblin.c contains the update function for the goblin entity
 */

#include <stdlib.h>

#include "entity.h"

// Returns a value from -1 to 0 inclusive, used for randomly moving a goblin
static inline int rand_move(void)
{
	return rand() % 3 - 1;
}

// Updates an existing goblin
void goblin_update(Entity *e)
{
	move_entity(e, rand_move(), rand_move());
}


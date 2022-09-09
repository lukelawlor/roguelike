/*
 * goblin.c contains the update function for the goblin entity
 */

#include <stdlib.h>

#include "entity.h"
#include "goblin.h"

// Returns a value from -1 to 0 inclusive, used for randomly moving a goblin
static inline int rand_move(void);

// Creates and returns a pointer to a new goblin
Entity *goblin_new(int y, int x)
{
	return entity_new(y, x, 'g', goblin_update, 1, "Goblin");
}

// Updates an existing goblin
void goblin_update(Entity *e)
{
	entity_move(e, rand_move(), rand_move());
}

// Returns a value from -1 to 0 inclusive, used for randomly moving a goblin
static inline int rand_move(void)
{
	return rand() % 3 - 1;
}

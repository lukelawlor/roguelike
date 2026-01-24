/* 'goblin.c' contains the update function for the goblin entity. */
#include <stdlib.h>

#include "entity.h"
#include "goblin.h"

/* Return a value from -1 to 0 inclusive, used for randomly moving a
   goblin */
static inline int rand_move (void);

/* Create & return a pointer to a new goblin */
Entity *
goblin_new (int y, int x)
{
  return entity_new (goblin_update, 1, y, x, 'g', "Goblin");
}

/* Update an existing goblin */
void
goblin_update (Entity *e)
{
  entity_move (e, rand_move (), rand_move ());
}

/* Return a value from -1 to 0 inclusive, used for randomly moving a
   goblin */
static inline int
rand_move (void)
{
  return rand () % 3 - 1;
}

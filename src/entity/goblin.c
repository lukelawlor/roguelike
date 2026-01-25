/* 'goblin.c' contains the update function for the goblin entity. */
#include <stdlib.h>

#include "entity.h"
#include "goblin.h"
#include "player.h"
#include "../talk.h"

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
EntRet
goblin_update (Entity *e)
{
  if (player_at (e->y, e->x))
    {
      entity_delete (e);
      talk ("YOWCH. ");
      return ENT_RET_DELETE;
    }
  entity_move (e, rand_move (), rand_move ());
  if (player_at (e->y, e->x))
    {
      entity_delete (e);
      talk ("whoops. ");
      return ENT_RET_DELETE;
    }
  return ENT_RET_OK;
}

/* Return a value from -1 to 0 inclusive, used for randomly moving a
   goblin */
static inline int
rand_move (void)
{
  return rand () % 3 - 1;
}

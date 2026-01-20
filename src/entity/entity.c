/* 'entity.c' contains functions for manipulating entities. */
#include <stdlib.h>

#include "entity.h"
#include "../map.h"

/* Return a pointer to an Entity list node with a 'NULL' value for 'e'
   & 'next' */
static ELNode *elnode_new (void);

/* Entity list head */
ELNode elhead = { NULL, NULL };

/* Entity id list (contains pointers to constructors for entities,
   used for spawning entities based on their "id" when loading
   maps) */
Entity *(*entity_id_list[ENT_MAX]) (int y, int x) = {
  player_new,
  goblin_new,
  map_editor_new
};

/* Return a pointer to a new Entity struct */
Entity *
entity_new (int y, int x, char c, void (*update)(Entity *e),
            int update_tick, char *name, void *s)
{
  /* Allocate memory for the new Entity & setting values */
  Entity *temp = malloc (sizeof (Entity));
  temp->y = y;
  temp->x = x;
  temp->c = c;
  temp->update = update;
  temp->update_tick = update_tick;
  temp->tick = 0;
  temp->name = name;
  temp->s = s;

  /* Add the new Entity struct to the Entity list */
  ELNode *node = &elhead;
  while (node->e != NULL)
    node = node->next;
  node->e = temp;
  node->next = elnode_new();

  return temp;
}

/* Return a pointer to an Entity list node with a 'NULL' value for 'e'
   & 'next' */
static ELNode *
elnode_new (void)
{
  ELNode *temp = malloc (sizeof (ELNode));
  temp->e = NULL;
  temp->next = NULL;
  return temp;
}

/* Translate an entity's position by (y, x) if there is open space at
   the new position */
void
entity_move (Entity *e, int y, int x)
{
  /* Check for open space */
  if (MAPT (e->y + y, e->x + x) != MAPTILE_AIR)
    return;
        
  /* Move the entity & redraw the map spaces at its new & old
     positions */
  e->y += y;
  e->x += x;
  draw_entity (e);
  draw_map_space (e->y - y, e->x - x);
}

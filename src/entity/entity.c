/* 'entity.c' contains functions for manipulating entities. */
#include <stdlib.h>

#include "entity.h"
#include "../error.h"
#include "../map.h"

/* Return a pointer to an Entity list node with a NULL value for 'e' &
   'next'; return NULL on error */
static ELNode *elnode_new (void);

/* Pointer to entity list head & tail */
ELNode *g_elhead, *g_eltail;

/* Entity id list (contains pointers to constructors for entities,
   used for spawning entities based on their "id" when loading
   maps) */
Entity *(*g_ent_id_list[ENT_MAX]) (int y, int x) = {
  player_new,
  goblin_new,
  map_editor_new
};

/* Return a pointer to a new Entity struct or NULL on error */
Entity *
entity_new (void (*update) (Entity *e), int update_tick,
            int y, int x, char c, char *name)
{
  Entity *e;
  if ((e = malloc (sizeof (Entity))) == NULL)
    {
      PERR ();
      fprintf (stderr,
               "failed to allocate memory for a new entity struct\n");
      return NULL;
    }
  ELNode *node;
  if ((node = elnode_new ()) == NULL)
    {
      free (e);
      return NULL;
    }
  node->e = e;

  /* Use parameters */
  e->update = update;
  e->update_tick = update_tick;
  e->tick = 0;
  e->y = y;
  e->x = x;
  e->c = c;
  e->name = name;

  /* Set default entity values */
  e->hp = ENT_DEFAULT_HP;
  e->mp = ENT_DEFAULT_MP;
  e->ac = ENT_DEFAULT_AC;

  /* NULL initialize 's' */
  e->s = NULL;

  /* Add the new entity struct to the entity list */
  if (g_elhead == NULL)
    g_elhead = g_eltail = node;
  else
    {
      g_eltail->next = node;
      g_eltail = node;
    }
  
  return e;
}

/* Return a pointer to an Entity list node with a NULL value for 'e' &
   'next'; return NULL on error */
static ELNode *
elnode_new (void)
{
  ELNode *node;
  if ((node = malloc (sizeof (ELNode))) == NULL)
    {
      PERR ();
      fprintf (stderr,
               "failed to allocate memory for a new entity node");
      return NULL;
    }
  node->e = NULL;
  node->next = NULL;
  return node;
}

/* Free the memory of all entities in the entity list */
void
entity_free_all (void)
{
  ELNode *node, *next;
  node = g_elhead;
  while (node != NULL)
    {
      next = node->next;
      free (node->e->s);
      free (node->e);
      free (node);
      node = next;
    }
  g_elhead = g_eltail = NULL;
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

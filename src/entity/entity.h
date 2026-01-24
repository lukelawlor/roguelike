/* 'entity.h' contains the Entity type definition & extern
   declarations for Entity linked lists.

   It also defines function prototypes for the update functions of all
   entities in the game. The definitions of these functions are found
   in c source files in the entity directory. These files are named
   after the entity whose update function they define (e.g. 'player.c'
   contains the definition for 'player_update'). */
#ifndef ENTITY_ENTITY_H
#define ENTITY_ENTITY_H

#include <stdbool.h>

/* Default entity statistics */
#define ENT_DEFAULT_HP 100
#define ENT_DEFAULT_MP 100
#define ENT_DEFAULT_AC 6

/* Length of entity id array */
#define ENT_MAX 3

/* Entity type used to represent entities in the map */
typedef struct Entity {
  /* Function run each time the entity is updated */
  void (*update) (struct Entity *e);

  /* The number of game ticks that need to go by for the 'update'
     function to be called */
  int update_tick;

  /* The current number of ticks that have passed (always from 0 to
     'update_tick' - 1, inclusive) */
  int tick;

  /* Position in map */
  int y;
  int x;

  /* Character used to depict the drawn entity */
  char c;

  /* Entity name */
  char *name;

  /* Hitpoints */
  int hp;

  /* Magic points used to cast spells */
  int mp;

  /* Armor class */
  int ac;

  /* Pointer to an "extension struct," which contains extra variables
     to extend entity functionality */
  void *s;
} Entity;

/* Entity linked list */
typedef struct ELNode {
  Entity *e;
  struct ELNode *next;
} ELNode;

/* Pointer to entity list head & tail */
extern ELNode *g_elhead, *g_eltail;

/* Entity id list (contains pointers to constructors for entities,
   used for spawning entities based on their "id" when loading
   maps) */
extern Entity *(*g_ent_id_list[ENT_MAX]) (int y, int x);

/* Create a new entity & add it to the entity list; return a pointer
   to the entity or NULL on error */
Entity *entity_new (void (*update) (Entity *e), int update_tick,
                    int y, int x, char c, char *name);

/* Free the memory of all entities in the entity list */
void entity_free_all (void);

/* Translate an entity's position by (y, x) if there is open space at
   the new position */
void entity_move (Entity *e, int y, int x);

/* Headers for individual entities in the game */
#include "player.h"
#include "goblin.h"
#include "map_editor.h"

#endif

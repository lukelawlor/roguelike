/*
 * entity.c contains functions for manipulating entities
 */

#include <stdlib.h>

#include "entity.h"
#include "../map.h"

// Returns a pointer to an Entity list node with a NULL value for e and next
static ELNode *elnode_new(void);

// Entity list head
ELNode elhead = {NULL, NULL};

// Returns a pointer to a new Entity struct
Entity *entity_new(int y, int x, char c, void (*update)(Entity *e), int update_tick, char *name, void *s)
{
	// Allocating mem for the new Entity and setting values
	Entity *temp = malloc(sizeof(Entity));
	temp->y = y;
	temp->x = x;
	temp->c = c;
	temp->update = update;
	temp->update_tick = update_tick;
	temp->tick = 0;
	temp->name = name;
	temp->s = s;

	// Adding temp to the Entity list
	ELNode *node = &elhead;
	while (node->e != NULL)
		node = node->next;
	node->e = temp;
	node->next = elnode_new();

	return temp;
}

// Returns a pointer to an Entity list node with a NULL value for e and next
static ELNode *elnode_new(void)
{
	ELNode *temp = malloc(sizeof(ELNode));
	temp->e = NULL;
	temp->next = NULL;
	return temp;
}

// Translates an entity's position by (y, x) if there is open space at the new position
void entity_move(Entity *e, int y, int x)
{
	// Check for open space
	if (MAPT(e->y + y, e->x + x) != MAPTILE_AIR)
		return;
	
	// Move the entity and redraw the map spaces at its new and previous positions
	e->y += y;
	e->x += x;
	draw_entity(e);
	draw_map_space(e->y - y, e->x - x);
}

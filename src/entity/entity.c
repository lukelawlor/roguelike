/*
 * entity.c contains functions for manipulating entities
 */

#include <stdlib.h>

#include "entity.h"
#include "../map.h"

// Returns a pointer to an Entity list node with a NULL value for e and next
static ELNode *new_elnode(void);

// Entity list head
ELNode elhead = {NULL, NULL};

// Returns a pointer to a new Entity struct
Entity *new_entity(int y, int x, char *name, char c, void (*update)(Entity *e))
{
	// Allocating mem for the new Entity and setting values
	Entity *temp = malloc(sizeof(Entity));
	temp->y = y;
	temp->x = x;
	temp->name = name;
	temp->c = c;
	temp->update = update;

	// Adding temp to the Entity list
	ELNode *node = &elhead;
	while (node->e != NULL)
		node = node->next;
	node->e = temp;
	node->next = new_elnode();

	return temp;
}

// Returns a pointer to an Entity list node with a NULL value for e and next
static ELNode *new_elnode(void)
{
	ELNode *temp = malloc(sizeof(ELNode));
	temp->e = NULL;
	temp->next = NULL;
	return temp;
}

// Translates an entity's position by (y, x) if there is open space at the new position
void move_entity(Entity *e, int y, int x)
{
	// Check for open space
	if (MAPT(e->y + y, e->x + x) != MAPTILE_AIR)
		return;
	
	// Move entity and redraw parts of the map that have changed
	draw_map_space(e->y, e->x);
	e->y += y;
	e->x += x;
	draw_entity(e);
}

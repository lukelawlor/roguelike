/*
 * entity.c contains functions for manipulating Entity structs
 */

#include <stdlib.h>

#include "entity.h"

// Returns a pointer to a new Entity struct
Entity *new_entity(int y, int x, char *name, char c)
{
	Entity *temp = malloc(sizeof(Entity));
	temp->y = y;
	temp->x = x;
	temp->name = name;
	temp->c = c;
	return temp;
}

/*
 * map.c contains functions for drawing parts of the game map
 */

#include <ncurses.h>

#include "win.h"
#include "entity/entity.h"
#include "map.h"

// Array that stores the character representations of map tile types at the indexes of their values
const char maptile_chars[] = {
	'.',
	'#'
};

// Global map variable (a 2d array representing a grid of map spaces)
Mapspace map[MAPH][MAPW];

// Draws the entire map
void draw_map(void)
{
	// Draw map tiles
	for (int y = 0; y < MAPH; y++)
		for (int x = 0; x < MAPW; x++)
			draw_map_space(y, x);
	
	// Draw entities
	ELNode *node = &elhead;
	while (node->next != NULL)
	{
		draw_entity(node->e);
		node = node->next;
	}
}

// Draws a single map space
void draw_map_space(int y, int x)
{
	mvwaddch(mapwin, y, x, MAPTC(MAPT(y, x)));
}

// Draws an entity
void draw_entity(Entity *e)
{
	mvwaddch(mapwin, e->y, e->x, e->c);
}

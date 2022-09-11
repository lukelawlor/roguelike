/*
 * map.c contains functions for drawing parts of the game map and loading maps
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
			draw_map_tile(y, x);
	
	// Draw all entities
	ELNode *node = &elhead;
	while (node->e != NULL)
	{
		draw_entity(node->e);
		node = node->next;
	}
}

// Draws the tile of a single map space
void draw_map_tile(int y, int x)
{
	mvwaddch(mapwin, y, x, MAPTC(MAPT(y, x)));
}

// Draws an entity
void draw_entity(Entity *e)
{
	mvwaddch(mapwin, e->y, e->x, e->c);
}

// Draws an entire map space (tile and entity)
void draw_map_space(int y, int x)
{
	draw_map_tile(y, x);

	// Check if any entities are at the map space coordinates and draw them if so
	for (ELNode *node = &elhead; node->e != NULL; node = node->next)
	{
		if (node->e->y == y && node->e->x == x)
		{
			draw_entity(node->e);
			
			// One entity can be drawn at max, so the function call ends here
			return;
		}
	}
}

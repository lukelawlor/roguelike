/*
 * map.c contains functions for drawing parts of the game map and loading maps
 */

#include <ncurses.h>

#include "win.h"
#include "entity/entity.h"
#include "map.h"

/*
 * maptile_chars is a pointer to a 2d array that stores the character representations of map tile types and their different styles.
 *
 * The first dimension of the array is the tile type, and the second dimension is the style.
 */
chtype maptile_chars[2][2];

// Global map variable (a 2d array representing a grid of map spaces)
Mapspace map[MAPH][MAPW];

// Initializes maptile_chars
void init_maptile_chars(void)
{
	maptile_chars[0][0] = '.';
	maptile_chars[0][1] = '#';
	maptile_chars[1][0] = '-';
	maptile_chars[1][1] = '|';
}

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
	Mapspace *ms = &map[y][x];
	if (ms->vis != MAPVIS_SEE)
		return;
	mvwaddch(mapwin, y, x, MAPTC(ms));
}

// Draws an entity
void draw_entity(Entity *e)
{
	Mapspace *ms = &map[e->y][e->x];
	if (ms->vis != MAPVIS_SEE)
		return;
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

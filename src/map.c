/*
 * map.c contains functions for drawing parts of the game map and loading maps
 */

#include <errno.h>

#include <ncurses.h>

#include "error.h"
#include "win.h"
#include "entity/entity.h"
#include "map.h"

/*
 * maptile_chars is a pointer to a 2d array that stores the character representations of map tile types and their different styles.
 *
 * The first dimension of the array is the tile type, and the second dimension is the style.
 */
chtype maptile_chars[MAP_TILE_NUM][MAP_STYLE_NUM];

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

// Loads map data from a text file; prints errors and returns nonzero on error
int load_map_txt(char *path, enum map_space_visibility default_visibility)
{
	FILE *mapfile;
	if ((mapfile = fopen(path, "r")) == NULL)
	{
		perror("roguelike: error opening map file");
		return 1;
	}

	// Current character being read
	unsigned int c;

	// Read the map file from the top, moving from left to right on rows of text
	for (int y = 0; y < MAPH; y++)
	{
		for (int x = 0; x < MAPW; x++)
		{
			c = fgetc(mapfile);
			Mapspace *ms = &map[y][x];
			
			// Get tile type and style
			for (int tile = 0; tile < MAP_TILE_NUM; tile++)
			{
				for (int style = 0; style < MAP_STYLE_NUM; style++)
				{
					if (maptile_chars[tile][style] == c)
					{
						// Tile & style found
						ms->tile = tile;
						ms->style = style;
						goto load_map_txt_set_vis;
					}
				}
			}

			// Tile & style not found, use default values and print a warning
			fprintf(stderr, "roguelike: warning: map tile & style not found for space at y%d x%d\n", y, x);
			ms->tile = MAPTILE_AIR;
			ms->style = 0;

			// Set visibility
			load_map_txt_set_vis:
			ms->vis = default_visibility;
		}
		// Skip newline character at the end of a row
		fgetc(mapfile);
	}
	return 0;
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

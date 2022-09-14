/*
 * map.h contains definitions for the game's map and macros to easily access map data
 */

#ifndef	MAP_H
#define	MAP_H
// Map dimensions
#define	MAPH	24
#define	MAPW	80

// Number of map tile types and styles for each of them
#define	MAP_TILE_NUM	2
#define	MAP_STYLE_NUM	2

// Macro to quickly access characters of map tile types
#define	MAPTC(map_space)	maptile_chars[map_space->tile][map_space->style]

// Macro to quickly access map space tile types
#define	MAPT(y, x)	map[y][x].tile

// Map space tile types
enum map_space_tile{
	MAPTILE_AIR,
	MAPTILE_WALL
};

// Map space visibility levels
enum map_space_visibility{
	// Player has never seen the space
	MAPVIS_UNSEEN,

	// Player has seen the space before
	MAPVIS_SEEN,

	// Player can currently see the space
	MAPVIS_SEE
};

/*
 * maptile_chars is a 2d array that stores the character representations of map tile types and their different styles.
 *
 * The first dimension of the array is the tile type, and the second dimension is the style.
 */
#include <ncurses.h>
extern chtype maptile_chars[MAP_TILE_NUM][MAP_STYLE_NUM];

// Mapspace type used to store the data of each space in the map
typedef struct {
	// Tile type
	enum map_space_tile tile : 1;

	// Tile style (affects appearance of tile type; ranges from 0-1)
	unsigned int style : 5;

	// Visibility level
	enum map_space_visibility vis : 2;
} Mapspace;

// Global map variable (a 2d array representing a grid of map spaces)
extern Mapspace map[MAPH][MAPW];

void init_maptile_chars(void);

// Loads map data from a text file; prints errors and returns nonzero on error
int load_map_txt(char *path, enum map_space_visibility default_visibility);

// Draws the entire map
void draw_map(void);

// Draws a single map space tile
void draw_map_tile(int y, int x);

// Draws an entire map space (tile and entity)
void draw_map_space(int y, int x);

// Draws an entity
#include "entity/entity.h"
void draw_entity(Entity *e);
#endif

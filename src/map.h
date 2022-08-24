/*
 * map.h contains definitions for the game's map and macros to easily access map data
 */

#ifndef	MAP_H
#define	MAP_H
// Map dimensions
#define	MAPH	20
#define	MAPW	60

// Map tile types and characters to represent them
#define MAPTILE_AIR		0
#define	MAPTILE_WALL		1

// Macro to quickly access characters of map tile types
#define	MAPTC(tile)	maptile_chars[tile]

// Macro to quickly access map space tile types
#define	MAPT(y, x)	map[y][x].tile

// Array that stores the character representations of map tile types at the indexes of their values
extern const char maptile_chars[];

// Mapspace type used to store the data of each space in the map
typedef struct {
	// Map tile type
	unsigned int tile : 1;
} Mapspace;

// Global map variable (a 2d array representing a grid of map spaces)
extern Mapspace map[MAPH][MAPW];

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

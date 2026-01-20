/* 'map.h' contains definitions for the game's map and macros to
   easily access map data. */
#ifndef MAP_H
#define MAP_H

#include <ncurses.h> /* for 'chtype' type */

#include "entity/entity.h" /* for 'Entity' type */

/* Map height & width */
#define MAPH 19
#define MAPW 62

/* Number of map tile types & styles for each of them */
#define MAP_TILE_NUM  2
#define MAP_STYLE_NUM 2

/* Macro to quickly access characters of map tile types */
#define MAPTC(map_space) g_maptile_chars[map_space->tile] \
  [map_space->style]

/* Macro to quickly access map space tile types */
#define MAPT(y, x) g_map[y][x].tile

/* Map space tile types */
enum map_space_tile { MAPTILE_AIR, MAPTILE_WALL };

/* Map space visibility levels */
enum map_space_visibility {
  MAPVIS_UNSEEN, /* Player has never seen the space */
  MAPVIS_SEEN, /* Player has seen the space before */
  MAPVIS_SEE /* Player can currently see the space */
};

/* Mapspace type used to store the data of each space in the map */
typedef struct {
  /* Tile type */
  enum map_space_tile tile : 1;

  /* Tile style (affects appearance of tile type; ranges from 0-1) */
  unsigned int style : 5;

  /* Visibility level */
  enum map_space_visibility vis : 2;
} Mapspace;

/* 'maptile_chars' is a 2-dimensional array that stores the character
   representations of map tile types & their different styles.

   The first dimension of the array is the tile type, and the second
   dimension is the style. */
extern chtype g_maptile_chars[MAP_TILE_NUM][MAP_STYLE_NUM];

/* Global map variable, a 2-dimensional array representing a grid of
   map spaces */
extern Mapspace g_map[MAPH][MAPW];

void init_maptile_chars (void);

/* Load map data from a text file; print errors & return nonzero on
   error */
int load_map_txt (char *path);

/* Draw the entire map */
void draw_map (void);

/* Draw a single map space tile */
void draw_map_tile (int y, int x);

/* Draw an entire map space (tile & entity) */
void draw_map_space (int y, int x);

/* Draw an entity */
void draw_entity (Entity *e);

#endif

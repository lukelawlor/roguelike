/*
 * map_editor.c contains the update function for the map_editor entity
 */

#include <stdlib.h>

#include <ncurses.h>

#include "../win.h"
#include "entity.h"
#include "map_editor.h"

// Moves the map editor
static inline void map_editor_move(Entity *e, int y, int x);

// The last map tile placed by a map_editor entity
static unsigned int map_editor_last_tile = MAPTILE_AIR;

// True if the map_editor is placing objects as it moves
static bool map_editor_auto_tile = false;

// Creates and returns a pointer to a new map_editor
Entity *map_editor_new(int y, int x)
{
	return entity_new(y, x, '$', map_editor_update, 1, "Map Editor");
}

// Updates an existing map_editor
void map_editor_update(Entity *e)
{
	// Get input from the user
	switch (wgetch(mapwin))
	{
		// Movement
		case 'j':
			map_editor_move(e, 1, 0);
			break;
		case 'k':
			map_editor_move(e, -1, 0);
			break;
		case 'h':
			map_editor_move(e, 0, -1);
			break;
		case 'l':
			map_editor_move(e, 0, 1);
			break;
		case '1':
			if ((map_editor_auto_tile = map_editor_auto_tile ? false : true))
				MAPT(e->y, e->x) = map_editor_last_tile;
			break;
		case '2':
			map_editor_last_tile = MAPT(e->y, e->x) = MAPTILE_AIR;
			break;
		case '3':
			map_editor_last_tile = MAPT(e->y, e->x) = MAPTILE_WALL;
			break;
		// Quitting the game
		case 'q':
			endwin();
			exit(EXIT_SUCCESS);
	}
}

// Moves the map editor
static inline void map_editor_move(Entity *e, int y, int x)
{
	if ((e->y += y) < 0 || e->y > MAPH - 1)
	{
		e->y -= y;
		return;
	}
	if ((e->x += x) < 0 || e->x > MAPW - 1)
	{
		e->x -= x;
		return;
	}
	if (map_editor_auto_tile)
		MAPT(e->y, e->x) = map_editor_last_tile;
	draw_entity(e);
	draw_map_space(e->y - y, e->x - x);
}

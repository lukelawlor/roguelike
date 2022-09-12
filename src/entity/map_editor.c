/*
 * map_editor.c contains the update function for the map_editor entity
 */

#include <stdlib.h>

#include <ncurses.h>

#include "../win.h"
#include "entity.h"
#include "map_editor.h"

// map_editor extension struct
typedef struct MapEditor{
	// The last tile placed by the map_editor
	unsigned int last_tile;

	// True if the map_editor is automatically placing tiles as they move
	bool auto_tile;
} MapEditor;

// Extension struct pointer
static MapEditor *s;

// Moves the map editor
static inline void map_editor_move(Entity *e, MapEditor *s, int y, int x);

// Creates and returns a pointer to a new map_editor
Entity *map_editor_new(int y, int x)
{
	s = malloc(sizeof(MapEditor));
	s->last_tile = MAPTILE_AIR;
	s->auto_tile = false;
	return entity_new(y, x, '$', map_editor_update, 1, "Map Editor", s);
}

// Updates an existing map_editor
void map_editor_update(Entity *e)
{
	s = (MapEditor *) e->s;

	// Get input from the user
	switch (wgetch(mapwin))
	{
		// Movement
		case 'j':
			map_editor_move(e, s, 1, 0);
			break;
		case 'k':
			map_editor_move(e, s, -1, 0);
			break;
		case 'h':
			map_editor_move(e, s, 0, -1);
			break;
		case 'l':
			map_editor_move(e, s, 0, 1);
			break;
		case '1':
			if ((s->auto_tile = s->auto_tile ? false : true))
				MAPT(e->y, e->x) = s->last_tile;
			break;
		case '2':
			s->last_tile = MAPT(e->y, e->x) = MAPTILE_AIR;
			break;
		case '3':
			s->last_tile = MAPT(e->y, e->x) = MAPTILE_WALL;
			break;
		// Quitting the game
		case 'q':
			endwin();
			exit(EXIT_SUCCESS);
	}
}

// Moves the map editor
static inline void map_editor_move(Entity *e, MapEditor *s, int y, int x)
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
	if (s->auto_tile)
		MAPT(e->y, e->x) = s->last_tile;
	draw_entity(e);
	draw_map_space(e->y - y, e->x - x);
}

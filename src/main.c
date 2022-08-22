/*
 * main.c contains the main function and game loop
 */

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#include "win.h"
#include "map.h"
#include "entity.h"

int main(void)
{
	// Init ncurses
	if (initscr() == NULL)
	{
		fprintf(stderr, "adventure: error: failed to initialize ncurses\n");
		exit(EXIT_FAILURE);
	}

	// Init game windows
	
	// End stdscr so error messages aren't buried
	endwin();
	if (init_windows() != 0)
		exit(EXIT_FAILURE);
	
	// Bring stdscr back
	refresh();
	
	// Set map data to create a basic map with nothing but air and a rectangular wall border
	for (int y = 0; y < MAPH; y++)
	{
		for (int x = 0; x < MAPW; x++)
		{
			if (y == 0 || x == 0 || y == MAPH - 1 || x == MAPW - 1)
				MAPT(y, x) = MAPTILE_WALL;
			else
				MAPT(y, x) = MAPTILE_AIR;
		}
	}

	// Draw the entire map
	draw_map();
	
	// Create a player entity and place it in the world
	Entity *player = new_entity(1, 1, "Player", '@');
	
	// Game loop
	wgetch(mapwin);

	// Game end
	endwin();
	exit(EXIT_SUCCESS);
}

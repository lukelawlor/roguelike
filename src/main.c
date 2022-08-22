/*
 * main.c contains the main function and game loop
 */

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#include "win.h"
#include "entity.h"
#include "map.h"

int main(void)
{
	// Init ncurses
	if (initscr() == NULL)
	{
		fprintf(stderr, "adventure: error: failed to initialize ncurses\n");
		exit(EXIT_FAILURE);
	}

	if (noecho() == ERR)
	{
		fprintf(stderr, "adventure: error: ncurses noecho() call failed\n");
		exit(EXIT_FAILURE);
	}

	if (curs_set(0) == ERR)
		fprintf(stderr, "adventure: error: cursor invisibility not supported by terminal\n");

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

	// Create a player entity and place it in the world
	Entity *player = new_entity(1, 1, "Player", '@');
	
	// Draw the entire map
	draw_map();

	// Game loop
	for (;;)
	{
		switch (wgetch(mapwin))
		{
			case 'j':
				move_entity(player, 1, 0);
				break;
			case 'k':
				move_entity(player, -1, 0);
				break;
			case 'h':
				move_entity(player, 0, -1);
				break;
			case 'l':
				move_entity(player, 0, 1);
				break;
			case 'q':
				endwin();
				exit(EXIT_SUCCESS);
		}
	}

	// Game end
	endwin();
	exit(EXIT_SUCCESS);
}

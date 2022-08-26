/*
 * main.c contains the main function and game loop
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ncurses.h>

#include "main.h"
#include "win.h"
#include "entity/entity.h"
#include "map.h"
#include "error.h"

// Game area
char *area;

// Game hour (1-24)
int hour;

// Game minute (0-59)
int min;

// Player entity
Entity *player;

int main(void)
{
	// Init ncurses
	if (initscr() == NULL)
	{
		PERR("failed to initialize ncurses");
		exit(EXIT_FAILURE);
	}

	if (noecho() == ERR)
	{
		PERR("ncurses noecho() call failed");
		exit(EXIT_FAILURE);
	}

	if (curs_set(0) == ERR)
		PERR("cursor invisibility not supported by terminal");

	// Init game windows
	
	// End stdscr so error messages aren't buried
	endwin();
	if (init_windows() != 0)
		exit(EXIT_FAILURE);
	
	// Bring stdscr back
	refresh();

	// Set global variables
	area = "Nowhere";
	hour = 6;
	min = 0;
	
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
	player = new_entity(1, 1, "Player", '@', player_update);
	new_entity(4, 4, "Goblin", '1', goblin_update);
	new_entity(4, 4, "Goblin", '2', goblin_update)->update_tick = 2;
	new_entity(4, 4, "Goblin", '3', goblin_update)->update_tick = 3;
	new_entity(4, 4, "Goblin", '4', goblin_update)->update_tick = 5; 
	new_entity(4, 4, "Goblin", '5', goblin_update)->update_tick = 10;
	new_entity(4, 4, "Goblin", '6', goblin_update)->update_tick = 20;

	
	// Draw the entire map
	draw_map();

	// Draw infowin
	draw_infowin();
	wrefresh(infowin);

	// Printing test text
	waddstr(statwin, "statwin");
	wrefresh(statwin);
	waddstr(talkwin, "talkwin");
	wrefresh(talkwin);

	// Game loop
	for (;;)
	{
		// Update entities
		for (ELNode *node = &elhead; node->e != NULL; node = node->next)
		{
			// Increase the entity's tick
			if ((node->e->tick += FRAME_TICK_INC) >= node->e->update_tick)
			{
				// Call the entity's update function as many times as the entity's tick goes into its update_tick
				int updates = node->e->tick / node->e->update_tick;

				for (int i = 0; i < updates; i++)
					(*node->e->update)(node->e);

				// Reset the entity's tick
				node->e->tick %= node->e->update_tick;
			}
		}
	}

	// Game end
	endwin();
	exit(EXIT_SUCCESS);
}

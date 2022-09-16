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

	// Initialize character representations of map spaces
	init_maptile_chars();
	
	load_map_txt("data/default_map.txt");
	
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

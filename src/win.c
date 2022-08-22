/*
 * win.c contains global variables and functions for manipulating game windows
 */

#include <stdio.h>

#include <ncurses.h>

#include "map.h"

// Window containing the game map
WINDOW *mapwin;

// Initializes game windows, returns nonzero and prints errors on error
int init_windows(void)
{
	if ((mapwin = newwin(MAPH, MAPW, 0, 0)) == NULL)
	{
		fprintf(stderr, "adventure: error: mapwin creation failed\n");
		return 1;
	}
	return 0;
}

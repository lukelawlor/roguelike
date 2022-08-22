/*
 * win.c contains global variables and functions for manipulating game windows
 */

#include <stdio.h>

#include <ncurses.h>

#include "main.h"
#include "win.h"
#include "error.h"

// Game map window
WINDOW *mapwin;

// Basic info window (game name, version, area, time)
WINDOW *infowin;

// Player stats or inventory window
WINDOW *statwin;

// Dialogue window
WINDOW *talkwin;

// Initializes game windows, returns nonzero and prints errors on error
int init_windows(void)
{
	if ((mapwin = newwin(MAPWIN_H, MAPWIN_W, 0, 0)) == NULL)
	{
		PERR("mapwin creation failed");
		return 1;
	}

	if ((infowin = newwin(INFOWIN_H, INFOWIN_W, INFOWIN_Y, INFOWIN_X)) == NULL)
	{
		PERR("infowin creation failed");
		return 1;
	}

	if ((statwin = newwin(STATWIN_H, STATWIN_W, STATWIN_Y, STATWIN_X)) == NULL)
	{
		PERR("statwin creation failed");
		return 1;
	}

	if ((talkwin = newwin(TALKWIN_H, TALKWIN_W, TALKWIN_Y, TALKWIN_X)) == NULL)
	{
		PERR("talkwin creation failed");
		return 1;
	}

	return 0;
}

// Updates infowin
void draw_infowin(void)
{
	// Print game name, version, and area
	wprintw(infowin, "%s v%s\n\n%s\n", GAME_NAME, GAME_VERSION, area);

	// Print the time
	#if HOURS24
		wprintw(infowin, "%d:", hour);
		if (min < 10)
			waddch(infowin, '0');
		wprintw(infowin, "%d", min);
	#else
		wprintw(infowin, "%d:", hour > 12 ? hour - 12 : hour);
		if (min < 10)
			waddch(infowin, '0');
		wprintw(infowin, "%d ", min);
		waddstr(infowin, hour >= 12 && hour != 24 ? "pm" : "am");
	#endif
}

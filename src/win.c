/* 'win.c' contains global variables & functions for manipulating game
   windows. */
#include <stdio.h>

#include <ncurses.h>

#include "main.h"
#include "win.h"
#include "error.h"

/* Game map window */
WINDOW *g_mapwin;

/* Basic information window (to view the game name, version, area,
   time) */
WINDOW *g_infowin;

/* Player statistics or inventory window */
WINDOW *g_statwin;

/* Dialogue window */
WINDOW *g_talkwin;

/* Initialize game windows; return nonzero & prints errors on error */
int
init_windows (void)
{
  if ((g_mapwin = newwin (MAPWIN_H, MAPWIN_W, 0, 0)) == NULL)
    {
      PERR ();
      fprintf (stderr, "mapwin creation failed");
      return 1;
    }

  if ((g_infowin
       = newwin (INFOWIN_H, INFOWIN_W, INFOWIN_Y, INFOWIN_X)) == NULL)
    {
      PERR ();
      fprintf (stderr, "infowin creation failed");
      return 1;
    }

  if ((g_statwin
       = newwin (STATWIN_H, STATWIN_W, STATWIN_Y, STATWIN_X)) == NULL)
    {
      PERR ();
      fprintf (stderr, "statwin creation failed");
      return 1;
    }

  if ((g_talkwin
       = newwin (TALKWIN_H, TALKWIN_W, TALKWIN_Y, TALKWIN_X)) == NULL)
    {
      PERR ();
      fprintf (stderr, "talkwin creation failed");
      return 1;
    }

  return 0;
}

/* Update 'g_infowin' */
void
draw_infowin (void)
{
  /* Print the game name, version & area */
  wprintw (g_infowin, "%s v%s\n\n%s\n", GAME_NAME, GAME_VERSION,
           g_area);

  /* Print the time */
#if HOURS24
  wprintw (g_infowin, "%d:", g_hour);
  if (g_min < 10)
    waddch (g_infowin, '0');
  wprintw (g_infowin, "%d", g_min);
#else
  wprintw (g_infowin, "%d:", g_hour > 12 ? g_hour - 12 : g_hour);
  if (g_min < 10)
    waddch (g_infowin, '0');
  wprintw (g_infowin, "%d ", g_min);
  waddstr (g_infowin, g_hour >= 12 && g_hour != 24 ? "pm" : "am");
#endif
}

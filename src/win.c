/* 'win.c' contains global variables & functions for manipulating game
   windows. */
#include <stdio.h>

#include <ncurses.h>

#include "main.h"
#include "win.h"
#include "error.h"

/* Strings to signify ante & post meridiem */
#define STR_ANTE_MERIDIEM "am"
#define STR_POST_MERIDIEM "pm"

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
  if (g_hours24)
    {
      wprintw (g_infowin, "%d:", g_hour);
      if (g_min < 10)
        waddch (g_infowin, '0');
      wprintw (g_infowin, "%d:", g_min);
      if (g_sec < 10)
        waddch (g_infowin, '0');
      wprintw (g_infowin, "%d ", (int) g_sec);
    }
  else
    {
      /* Hour to print */
      char hour;
      if (g_hour == 0)
        hour = 12;
      else if (g_hour <= 12)
        hour = g_hour;
      else
        hour = g_hour - 12;
      wprintw (g_infowin, "%d:", hour);
      if (g_min < 10)
        waddch (g_infowin, '0');
      wprintw (g_infowin, "%d:", g_min);
      if (g_sec < 10)
        waddch (g_infowin, '0');
      wprintw (g_infowin, "%d ", (int) g_sec);
      if (g_hour < 12)
        waddstr (g_infowin, STR_ANTE_MERIDIEM);
      else
        waddstr (g_infowin, STR_POST_MERIDIEM);
    }

  wrefresh (g_infowin);

  /* Clear lines that change & move into the starting position for the
     next call of this function */
  wmove (g_infowin, 3, 0);
  wclrtoeol (g_infowin);
  wmove (g_infowin, 2, 0);
  wclrtoeol (g_infowin);
  wmove (g_infowin, 0, 0);
}

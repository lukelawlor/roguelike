/* 'win.c' contains global variables & functions for manipulating game
   windows. */
#include <stdio.h>
#include <string.h>

#include <ncurses.h>

#include "entity/entity.h" /* for 'Entity' */
#include "error.h"
#include "main.h"
#include "win.h"

/* Strings to signify ante & post meridiem */
#define STR_ANTE_MERIDIEM "am"
#define STR_POST_MERIDIEM "pm"

/* Lengths of various kinds of strings, including the null-terminator,
   to print to statwin */
#define STATWIN_LEN_NAME 7 /* An entity's name */
#define STATWIN_LEN_NUMBER 5
#define STATWIN_LEN_POINTER 15

/* Number of characters to ignore at the start of a string
   representation of a pointer (2 means don't print "0x") */
#define STATWIN_PTR_SKIP 2

/* String to print as a pointer to represent NULL */
#define STATWIN_PTR_NULL "  NULL"

/* Game map window */
WINDOW *g_mapwin;

/* Basic information window (to view the game name, version, area,
   time) */
WINDOW *g_infowin;

/* Player statistics or inventory window */
WINDOW *g_statwin;

/* Dialogue window */
WINDOW *g_talkwin;

/* A placeholder 'Entity' to be printed if there is nothing else to
   print in statwin */
static Entity s_nobody = {
  .update = NULL,
  .update_tick = 0,
  .tick = 0,
  .y = 0,
  .x = 0,
  .c = '?',
  .name = "Nobody",
  .hp = 0,
  .mp = 0,
  .ac = 0,
  .node = NULL,
  .s = NULL,
};

/* Pointers to entities whose statistics will be printed in
   statwin. The top entity is printed above the bottom one. */
Entity *g_statwin_ent_top = &s_nobody;
Entity *g_statwin_ent_bottom = &s_nobody;

/* Print the statistics of an entity to statwin. This is to be called
   by 'draw_statwin()'. 'y' is the y value to start printing at. */
static void print_entity (Entity *e, int y);

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

/* Print to 'g_infowin' & refresh it */
void
draw_infowin (void)
{
  /* Print the game name, version, area & day */
  wprintw (g_infowin, "%s v%s%s\nDay %lld\n", GAME_NAME, GAME_VERSION,
           g_area, g_day);

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
  wmove (g_infowin, 1, 0);
  wclrtoeol (g_infowin);
  wmove (g_infowin, 2, 4);
  wclrtoeol (g_infowin);
  wmove (g_infowin, 3, 0);
  wclrtoeol (g_infowin);
  wmove (g_infowin, 0, 0);
}

/* Print to 'g_statwin' & refresh it */
void
draw_statwin (void)
{
  print_entity (g_statwin_ent_top, 0);
  print_entity (g_statwin_ent_bottom, 8);
  wrefresh (g_statwin);
}

/* Print the statistics of an entity to statwin. This is to be called
   by 'draw_statwin()'. 'y' is the y value to start printing at. */
static void
print_entity (Entity *e, int y)
{
  char name[STATWIN_LEN_NAME];
  char hp[STATWIN_LEN_NUMBER];
  char mp[STATWIN_LEN_NUMBER];
  char ac[STATWIN_LEN_NUMBER];
  char e_y[STATWIN_LEN_NUMBER];
  char e_x[STATWIN_LEN_NUMBER];
  char kind[STATWIN_LEN_POINTER];
  char node[STATWIN_LEN_POINTER];
  char ptr[STATWIN_LEN_POINTER];
  strncpy (name, e->name, STATWIN_LEN_NAME - 1);
  snprintf (hp, STATWIN_LEN_NUMBER - 1, "%d", e->hp);
  snprintf (mp, STATWIN_LEN_NUMBER - 1, "%d", e->mp);
  snprintf (ac, STATWIN_LEN_NUMBER - 1, "%d", e->ac);
  snprintf (e_y, STATWIN_LEN_NUMBER - 1, "%d", e->y);
  snprintf (e_x, STATWIN_LEN_NUMBER - 1, "%d", e->x);
  if (e->update == NULL)
    strncpy (kind, STATWIN_PTR_NULL, STATWIN_LEN_POINTER - 1);
  else
    snprintf (kind, STATWIN_LEN_POINTER - 1, "%p", e->update);
  if (e->node == NULL)
    strncpy (node, STATWIN_PTR_NULL, STATWIN_LEN_POINTER - 1);
  else
    snprintf (node, STATWIN_LEN_POINTER - 1, "%p", e->node);
  snprintf (ptr, STATWIN_LEN_POINTER - 1, "%p", e);
  mvwprintw (g_statwin, y, 0, "%c %s's stats", e->c, name);
  mvwprintw (g_statwin, y + 1, 0, "Hitpoints: %s", hp);
  mvwprintw (g_statwin, y + 2, 0, "Magicpnts: %s", mp);
  mvwprintw (g_statwin, y + 3, 0, "Armorclas: %s", ac);
  mvwprintw (g_statwin, y + 4, 0, "Y, X: %s, %s", e_y, e_x);
  mvwprintw (g_statwin, y + 5, 0, "Typ: %s", kind + STATWIN_PTR_SKIP);
  mvwprintw (g_statwin, y + 6, 0, "Nod: %s", node + STATWIN_PTR_SKIP);
  mvwprintw (g_statwin, y + 7, 0, "Ptr: %s", ptr + STATWIN_PTR_SKIP);
}

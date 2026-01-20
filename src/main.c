/* 'main.c' contains the main function & game loop. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ncurses.h>

#include "main.h"
#include "win.h"
#include "entity/entity.h"
#include "map.h"
#include "error.h"

/* Game area */
char *g_area;

/* Game hour (1-24) */
char g_hour;

/* Game minute (0-59) */
char g_min;

/* Game seconds (0-59) */
char g_sec;

/* Player entity */
Entity *player;

int
main (void)
{
  /* Initialize ncurses */
  if (initscr () == NULL)
    {
      PERR ();
      fprintf (stderr, "failed to initialize ncurses\n");
      exit (EXIT_FAILURE);
    }

  if (noecho () == ERR)
    {
      endwin ();
      PERR ();
      fprintf (stderr, "ncurses noecho() call failed\n");
      exit (EXIT_FAILURE);
    }

  if (curs_set (0) == ERR)
    {
      endwin ();
      PERR ();
      fprintf (stderr,
               "cursor invisibility not supported by terminal\n");
      refresh ();
    }

  /* Initialize game windows */
        
  /* End stdscr so error messages aren't buried */
  endwin ();
  if (init_windows () != 0)
    exit (EXIT_FAILURE);
        
  /* Bring stdscr back */
  refresh();

  /* Set global variables */
  g_area = "Nowhere";

  /* Initialize character representations of map spaces */
  init_maptile_chars ();
        
  endwin ();
  load_map_txt ("data/default_map.txt");
  refresh ();
        
  /* Draw the entire map */
  draw_map ();

  /* Draw infowin */
  draw_infowin ();
  wrefresh (g_infowin);

  /* Print test text */
  waddstr (g_statwin, "statwin");
  wrefresh (g_statwin);
  waddstr (g_talkwin, "talkwin");
  wrefresh (g_talkwin);

  /* Game loop */
  for (;;)
    {
      /* Update entities */
      for (ELNode *node = &elhead; node->e != NULL; node = node->next)
        {
          /* Increase the entity's 'tick' */
          if ((node->e->tick += FRAME_TICK_INC)
              >= node->e->update_tick)
            {
              /* Call the entity's 'update' function as many times as
                 the entity's 'tick' goes into its 'update_tick' */
              int updates = node->e->tick / node->e->update_tick;
              for (int i = 0; i < updates; i++)
                (*node->e->update) (node->e);

              /* Reset the entity's tick */
              node->e->tick %= node->e->update_tick;
            }
        }

      /* Increase game time */
      g_sec += 30;

      if (g_sec > 59)
        {
          g_min += g_sec / 60;
          g_sec %= 60;
          if (g_min > 59)
            {
              g_hour += g_min / 60;
              g_min %= 60;
              if (g_hour > 24)
                g_hour %= 24;
            }
          draw_infowin ();
        }
    }

  /* Game end */
  endwin ();
  exit (EXIT_SUCCESS);
}

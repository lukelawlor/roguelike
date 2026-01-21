/* 'main.c' contains the main function & game loop. */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* for 'time (NULL)' to set the random seed */

#include <ncurses.h>

#include "entity/entity.h"
#include "error.h"
#include "input.h"
#include "main.h"
#include "map.h"
#include "win.h"

/* Increase in game ticks per game loop iteration */
int g_game_loop_step_tick;

/* Increase in seconds of game time per game loop iteration */
long long g_game_loop_step_sec;

/* Game area */
char *g_area;

/* Game hour (0-23) */
char g_hour;

/* Game minute (0-59) */
char g_min;

/* Game seconds (0-59 & beyond to accumulate time before converting
   seconds into minutes & hours) */
long long g_sec;

/* 24 hour time formatting flag */
bool g_hours24;

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

  /* Set the random seed */
  srand (time (NULL));

  /* Set global variables */
  g_game_loop_step_tick = 1;
  g_game_loop_step_sec = 10;
  g_area = "Nowhere";
  g_hour = 14;
  g_min = 43;
  g_sec = 6;
  g_hours24 = false;

  /* Initialize character representations of map spaces */
  init_maptile_chars ();
        
  endwin ();
  load_map_txt ("data/default_map.txt");
  refresh ();
        
  /* Draw the entire map */
  draw_map ();

  /* Draw infowin */
  draw_infowin ();

  /* Print test text */
  waddstr (g_statwin, "statwin");
  wrefresh (g_statwin);
  waddstr (g_talkwin, "talkwin");
  wrefresh (g_talkwin);

  /* Game loop */
  for (;;)
    {
      /* Update entities */
      bool player_exists = false;
      for (ELNode *node = &elhead; node->e != NULL; node = node->next)
        {
          /* Increase the entity's 'tick' */
          if ((node->e->tick += g_game_loop_step_tick)
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
          /* Check if the player entity exists */
          if (node->e->update == player_update)
            player_exists = true;
        }

      /* Increase game time */
      g_sec += g_game_loop_step_sec;
      if (g_sec > 59)
        {
          g_min += g_sec / 60;
          g_sec %= 60;
          if (g_min > 59)
            {
              g_hour += g_min / 60;
              g_min %= 60;
              if (g_hour > 23)
                g_hour %= 24;
            }
        }

      draw_infowin ();
      
      /* If the player doesn't exist, then ask for some input from the
         user to prevent an infinite loop */
      if (!player_exists)
        GETC ();
    }

  /* Game end */
  endwin ();
  exit (EXIT_SUCCESS);
}

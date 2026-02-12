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
#include "talk.h"
#include "win.h"

/* Increase in game ticks per game loop iteration */
int g_game_loop_step_tick;

/* Increase in seconds of game time per game loop iteration */
long long g_game_loop_step_sec;

/* Game area */
char *g_area;

/* Game day */
long long g_day;

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
Entity *g_player;

int
main (void)
{
  /* Initialize ncurses */
  if (initscr () == NULL)
    {
      PERR ("failed to initialize ncurses");
      exit (EXIT_FAILURE);
    }

  if (noecho () == ERR)
    {
      endwin ();
      PERR ("ncurses 'noecho ()' call failed");
      exit (EXIT_FAILURE);
    }

  if (curs_set (0) == ERR)
    {
      endwin ();
      PERR ("cursor invisibility not supported by terminal");
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
  g_game_loop_step_sec = 1000;
  g_area = "Nowhere";
  g_day = 0;
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

  draw_infowin ();
  draw_statwin ();

  /* Print test text */
  talk ("WELCOME TO THE WORLD. ");
  PINF ("game started succesfully");

  /* Game loop */
  for (;;)
    {
      /* Update entities */
      bool player_exists = false;
      ELNode *i, *next;
      i = g_elhead;
      for (;;)
        {
          if (i == NULL)
            break;
          next = i->next;
          
          /* Check if the player entity exists */
          if (i->e->update == player_update)
            player_exists = true;

          /* Increase the entity's 'tick' */
          if ((i->e->tick += g_game_loop_step_tick)
              >= i->e->update_tick)
            {
              /* Calculate how many times to update the entity */
              int updates = i->e->tick / i->e->update_tick;

              /* Reset the entity's tick */
              i->e->tick %= i->e->update_tick;
              
              EntRet ret;
              for (int j = 0; j < updates; ++j)
                {
                  ret = (*i->e->update) (i->e);
                  if (ret == ENT_RET_DELETE)
                      break;
                }
            }
          i = next;
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
                {
                  g_hour %= 24;
                  ++g_day;
                }
            }
        }

      draw_infowin ();
      
      /* If the player doesn't exist, then ask for some input from the
         user to prevent an infinite loop */
      if (!player_exists)
        {
          if (GETC () == 'q')
            {
                endwin ();
                exit (EXIT_SUCCESS);
            }
        }

    }

  /* Game end */
  endwin ();
  exit (EXIT_SUCCESS);
}

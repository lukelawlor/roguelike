/* 'player.c' contains the update function for the player entity. */
#include <stdlib.h>

#include <ncurses.h>

#include "../input.h"
#include "entity.h"
#include "player.h"

/* Create & return a pointer to a new player */
Entity *
player_new (int y, int x)
{
  return entity_new (player_update, 1, y, x, '@', "Player");
}

/* Update an existing player */
void
player_update (Entity *e)
{
  /* Get input from the user */
  switch (GETC ())
    {
      /* Player movement */
    case 'j':
      entity_move (e, 1, 0);
      break;
    case 'k':
      entity_move (e, -1, 0);
      break;
    case 'h':
      entity_move (e, 0, -1);
      break;
    case 'l':
      entity_move (e, 0, 1);
      break;
      /* Quit the game */
    case 'q':
      endwin ();
      exit (EXIT_SUCCESS);
    }
}

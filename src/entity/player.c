/* 'player.c' contains the update function for the player entity. */
#include <stdlib.h>

#include <ncurses.h>

#include "entity.h"
#include "player.h"
#include "../input.h"
#include "../map.h"
#include "../talk.h"

/* Pointer to the player entity. This assumes that it's only possible
   for there to be 1 or 0 players at a given time. */
static Entity *s_player;

/* Create & return a pointer to a new player */
Entity *
player_new (int y, int x)
{
  s_player = entity_new (player_update, 1, y, x, '@', "Player");
  return s_player;
}

/* Update an existing player */
EntRet
player_update (Entity *e)
{
  /* Get input from the user */
  switch (GETC ())
    {
      /* Player movement */
    case 'j': entity_move (e, 1, 0); break;
    case 'k': entity_move (e, -1, 0); break;
    case 'h': entity_move (e, 0, -1); break;
    case 'l': entity_move (e, 0, 1); break;
    case 'y': entity_move (e, -1, -1); break;
    case 'u': entity_move (e, -1, 1); break;
    case 'b': entity_move (e, 1, -1); break;
    case 'n': entity_move (e, 1, 1); break;
      /* Realistic human speech */
    case 't':
      talk ("Taa rothar oog agam. ");
      break;
      /* Die */
    case 'd':
      draw_map_tile (e->y, e->x);
      entity_delete (e);
      talk ("Noooo. ");
      return ENT_RET_DELETE;
      /* Quit the game */
    case 'q':
      endwin ();
      exit (EXIT_SUCCESS);
    }
  return ENT_RET_OK;
}

/* Return true if the player is at the specified coordinates */
bool
player_at (int y, int x)
{
  if (s_player == NULL)
    return false;
  return s_player->y == y && s_player->x == x;
}

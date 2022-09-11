/*
 * player.c contains the update function for the player entity
 */

#include <stdlib.h>

#include <ncurses.h>

#include "../win.h"
#include "entity.h"
#include "player.h"

// Creates and returns a pointer to a new player
Entity *player_new(int y, int x)
{
	return entity_new(y, x, '@', player_update, 1, "Player", NULL);
}

// Updates an existing player
void player_update(Entity *e)
{
	// Get input from the user
	switch (wgetch(mapwin))
	{
		// Player movement
		case 'j':
			entity_move(e, 1, 0);
			break;
		case 'k':
			entity_move(e, -1, 0);
			break;
		case 'h':
			entity_move(e, 0, -1);
			break;
		case 'l':
			entity_move(e, 0, 1);
			break;
		// Quitting the game
		case 'q':
			endwin();
			exit(EXIT_SUCCESS);
	}
}

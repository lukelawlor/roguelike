/*
 * player.c contains the update function for the player entity
 */

#include <stdlib.h>

#include <ncurses.h>

#include "../win.h"
#include "entity.h"

// Updates an existing player
void player_update(Entity *e)
{
	// Get input from the user
	switch (wgetch(mapwin))
	{
		// Player movement
		case 'j':
			move_entity(e, 1, 0);
			break;
		case 'k':
			move_entity(e, -1, 0);
			break;
		case 'h':
			move_entity(e, 0, -1);
			break;
		case 'l':
			move_entity(e, 0, 1);
			break;
		// Quitting the game
		case 'q':
			endwin();
			exit(EXIT_SUCCESS);
	}
}

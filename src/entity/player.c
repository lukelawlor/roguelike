#include <stdlib.h>

#include <ncurses.h>

#include "../win.h"
#include "entity.h"

void player_update(Entity *e)
{
	switch (wgetch(mapwin))
	{
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
		case 'q':
			endwin();
			exit(EXIT_SUCCESS);
	}
}

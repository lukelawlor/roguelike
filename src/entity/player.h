/* 'player.h' contains function prototypes for creating & updating players. */
#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

/* Create & return a pointer to a new player */
Entity *player_new (int y, int x);

/* Update a player */
EntRet player_update (Entity *e);

/* Return true if the player is at the specified coordinates */
bool player_at (int y, int x);

#endif

/* 'player.h' contains function prototypes for creating & updating players. */
#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

/* Create & return a pointer to a new player */
Entity *player_new (int y, int x);

/* Update a player */
void player_update (Entity *e);

#endif

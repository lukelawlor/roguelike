/*
 * player.h contains function prototypes for creating and updating players
 */

#ifndef	ENTITY_PLAYER_H
#define	ENTITY_PLAYER_H
// Creates and returns a pointer to a new player
Entity *player_new(int y, int x);

// Updates a player
void player_update(Entity *e);
#endif

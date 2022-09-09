/*
 * goblin.h contains function prototypes for creating and updating players
 */

#ifndef	ENTITY_GOBLIN_H
#define	ENTITY_GOBLIN_H
// Creates and returns a pointer to a new goblin
Entity *goblin_new(int y, int x);

// Updates a goblin
void goblin_update(Entity *e);
#endif

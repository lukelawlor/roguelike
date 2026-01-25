/* 'goblin.h' contains function prototypes for creating and updating
   goblins. */
#ifndef ENTITY_GOBLIN_H
#define ENTITY_GOBLIN_H

/* Create & return a pointer to a new goblin */
Entity *goblin_new (int y, int x);

/* Update a goblin */
EntRet goblin_update (Entity *e);

#endif

/*
 * map_editor.h contains function prototypes for creating and updating map_editors
 */

#ifndef	ENTITY_MAP_EDITOR_H
#define	ENTITY_MAP_EDITOR_H
// Creates and returns a pointer to a new map_editor
Entity *map_editor_new(int y, int x);

// Updates a map_editor
void map_editor_update(Entity *e);
#endif

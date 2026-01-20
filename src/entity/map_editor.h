/* 'map_editor.h' contains function prototypes for creating & updating
   map_editors. */
#ifndef ENTITY_MAP_EDITOR_H
#define ENTITY_MAP_EDITOR_H

// Create & return a pointer to a new map_editor
Entity *map_editor_new (int y, int x);

// Update a map_editor
void map_editor_update (Entity *e);

#endif

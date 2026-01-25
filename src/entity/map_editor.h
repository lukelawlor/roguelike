/* 'map_editor.h' contains function prototypes for creating & updating
   map editors. */
#ifndef ENTITY_MAP_EDITOR_H
#define ENTITY_MAP_EDITOR_H

/* Create & return a pointer to a new map editor or NULL on error */
Entity *map_editor_new (int y, int x);

/* Update a map editor */
EntRet map_editor_update (Entity *e);

#endif

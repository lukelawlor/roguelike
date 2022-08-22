/*
 * entity.h contains the Entity type definition and extern declarations for Entity linked lists
 */

#ifndef	ENTITY_H
#define	ENTITY_H
#endif

// Entity type used to represent entities in the map
typedef struct {
	// Position in map
	int y;
	int x;

	char *name;
	
	// Character used to depict the drawn entity
	char c;
} Entity;

// Entity linked list
struct EntityListNode {
	Entity *e;
	struct EntityListNode *next;
};
typedef struct EntityListNode ELNode;

// Entity linked list head
extern ELNode elhead;

// Returns a pointer to a new Entity struct
Entity *new_entity(int y, int x, char *name, char c);

// Translates an entity's position by (y, x) if there is open space at the new position
void move_entity(Entity *e, int y, int x);

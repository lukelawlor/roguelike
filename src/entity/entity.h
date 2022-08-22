/*
 * entity.h contains the Entity type definition and extern declarations for Entity linked lists
 */

#ifndef	ENTITY_H
#define	ENTITY_H
// Entity type used to represent entities in the map
typedef struct EntityTag{
	// Position in map
	int y;
	int x;

	char *name;
	
	// Character used to depict the drawn entity
	char c;

	// Function run each time the game is updated
	void (*update)(struct EntityTag *e);
} Entity;

// Entity linked list
typedef struct EntityListNode {
	Entity *e;
	struct EntityListNode *next;
} ELNode;

// Entity linked list head
extern ELNode elhead;

// Creates a new entity and adds it to the entity list, returns a pointer to the entity
Entity *new_entity(int y, int x, char *name, char c, void (*update)(Entity *e));

// Translates an entity's position by (y, x) if there is open space at the new position
void move_entity(Entity *e, int y, int x);

// Function prototypes for entity update functions
#define	EINC(e)	void e##_update(Entity *)
EINC(player);

#endif

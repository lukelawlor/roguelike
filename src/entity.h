/*
 * entity.h contains the Entity struct definition
 */

// Entity type used to represent entities in the map
typedef struct {
	// Position in map
	int y;
	int x;

	char *name;
	
	// Character used to depict the drawn entity
	char c;
} Entity;

// Returns a pointer to a new Entity struct
Entity *new_entity(int y, int x, char *name, char c);

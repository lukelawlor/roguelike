/*
 * main.h contains miscellaneous macros and extern declarations for miscellaneous, commonly-used global variables
 */

// Game details
#define	GAME_NAME	"Adventure"
#define	GAME_VERSION	"0.0.0"

// 24 hour time formatting flag
#define	HOURS24		0

// Increase in game ticks per game loop iteration
#define	FRAME_TICK_INC	1

// Game area
extern char *area;

// Game time
extern int hour, min;

// Player entity
#include "entity/entity.h"
extern Entity *player;

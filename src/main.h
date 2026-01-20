/* 'main.h' contains miscellaneous macros & extern declarations for
   miscellaneous, commonly-used global variables. */
#ifndef MAIN_H
#define MAIN_H

/* Game details */
#define GAME_NAME    "Roguelike"
#define GAME_VERSION "0.0.0"

/* 24 hour time formatting flag */
#define HOURS24 0

/* Increase in game ticks per game loop iteration */
#define FRAME_TICK_INC 1

/* Game area */
extern char *g_area;

/* Game time */
extern char g_hour, g_min, g_sec;

/* Player entity */
#include "entity/entity.h"
extern Entity *player;

#endif

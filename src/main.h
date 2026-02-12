/* 'main.h' contains miscellaneous macros & extern declarations for
   miscellaneous, commonly-used global variables. */
#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

/* Game details */
#define GAME_NAME "Roguelike"
#define GAME_VERSION "0.0.0"

/* Game name used in error messages. See './error.c'. */
#define GAME_NAME_LOWERCASE "roguelike"

/* Increase in game ticks per game loop iteration */
extern int g_game_loop_step_tick;

/* Increase in seconds of game time per game loop iteration */
extern long long g_game_loop_step_sec;

/* Game area */
extern char *g_area;

/* Game time */
extern char g_hour, g_min;
extern long long g_day, g_sec;

/* 24 hour time formatting flag */
extern bool g_hours24;

/* Player entity */
#include "entity/entity.h"
extern Entity *g_player;

#endif

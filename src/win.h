/* 'win.h' contains the extern declarations for the game's windows &
   window dimensions. */
#ifndef WIN_H
#define WIN_H

#include "entity/entity.h" /* For 'Entity' */
#include "map.h" /* for 'MAPW' & 'MAPH' */

/* Window dimensions */
#define MAPWIN_W MAPW
#define MAPWIN_H MAPH

#define INFOWIN_Y 0
#define INFOWIN_X MAPW
#define INFOWIN_H 4
#define INFOWIN_W 16

#define STATWIN_Y INFOWIN_H
#define STATWIN_X INFOWIN_X
#define STATWIN_H 16
#define STATWIN_W INFOWIN_W

#define TALKWIN_Y MAPH
#define TALKWIN_X 0
#define TALKWIN_H 4
#define TALKWIN_W (MAPW + INFOWIN_W)

/* Game map window */
extern WINDOW *g_mapwin;

/* Basic information window (to view the game name, version, area,
   time) */
extern WINDOW *g_infowin;

/* Player statistics or inventory window */
extern WINDOW *g_statwin;

/* Pointers to entities whose statistics will be printed in
   statwin. The top entity is printed above the bottom one. */
extern Entity *g_statwin_ent_top, *g_statwin_ent_bottom;

/* Dialogue window */
extern WINDOW *g_talkwin;

/* Initialize game windows; return nonzero & prints errors on error */
int init_windows (void);

/* Print to 'g_infowin' & refresh it */
void draw_infowin (void);

/* Print to 'g_statwin' & refresh it */
void draw_statwin (void);

#endif

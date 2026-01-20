/* 'win.h' contains the extern declarations for the game's windows &
   window dimensions. */
#ifndef WIN_H
#define WIN_H

#include "map.h" /* for 'MAPW' & 'MAPH' */

/* Window dimensions */
#define MAPWIN_W MAPW
#define MAPWIN_H MAPH

#define INFOWIN_Y 0
#define INFOWIN_X (MAPW + 1)
#define INFOWIN_H 6
#define INFOWIN_W 20

#define STATWIN_Y (INFOWIN_H + 2)
#define STATWIN_X INFOWIN_X
#define STATWIN_H 10
#define STATWIN_W INFOWIN_W

#define TALKWIN_Y (MAPH + 1)
#define TALKWIN_X 0
#define TALKWIN_H 3
#define TALKWIN_W MAPW

/* Game map window */
extern WINDOW *g_mapwin;

/* Basic information window (to view the game name, version, area,
   time) */
extern WINDOW *g_infowin;

/* Player statistics or inventory window */
extern WINDOW *g_statwin;

/* Dialogue window */
extern WINDOW *g_talkwin;

/* Initialize game windows; return nonzero & prints errors on error */
int init_windows (void);

/* Update 'g_infowin' */
void draw_infowin (void);

#endif

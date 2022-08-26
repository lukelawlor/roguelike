/*
 * win.h contains the extern declarations for the game's windows and window dimensions
 */
#ifndef	WIN_H
#define	WIN_H
// Window dimensions
#include "map.h"
#define	MAPWIN_W	MAPW
#define	MAPWIN_H	MAPH

#define	INFOWIN_Y	0
#define	INFOWIN_X	MAPW + 1
#define	INFOWIN_H	6
#define	INFOWIN_W	20

#define	STATWIN_Y	INFOWIN_H + 2
#define	STATWIN_X	INFOWIN_X
#define	STATWIN_H	10
#define	STATWIN_W	INFOWIN_W

#define	TALKWIN_Y	MAPH + 1
#define	TALKWIN_X	0
#define	TALKWIN_H	3
#define	TALKWIN_W	MAPW

// Game map window
extern WINDOW *mapwin;

// Basic info window (game name, version, area, time)
extern WINDOW *infowin;

// Player stats or inventory window
extern WINDOW *statwin;

// Dialogue window
extern WINDOW *talkwin;

// Initializes game windows, returns nonzero and prints errors on error
int init_windows(void);

// Updates infowin
void draw_infowin(void);
#endif

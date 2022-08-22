/*
 * win.h contains the extern declarations for the game's windows
 */

// Game map window
extern WINDOW *mapwin;

// Initializes game windows, returns nonzero and prints errors on error
int init_windows(void);

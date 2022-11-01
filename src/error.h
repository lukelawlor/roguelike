/*
 * error.h contains a macro for printing error messages
 */
#ifndef	ERROR_H
#define	ERROR_H

#include <ncurses.h>

// Macro called to print text at the start of an error message
#define	PERR()	fprintf(stderr, "roguelike: error in %s at ln %d: ", __FILE__, __LINE__)

#endif

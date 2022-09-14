/*
 * error.h contains a macro for printing error messages
 */
#ifndef	ERROR_H
#define	ERROR_H

#define	PERR(msg)	fprintf(stderr, "roguelike: error: %s line %d: %s\n", __FILE__, __LINE__, msg)

#endif

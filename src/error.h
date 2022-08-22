/*
 * error.h contains a macro for printing error messages
 */

#define	PERR(msg)	fprintf(stderr, "adventure: error: %s line %d: %s\n", __FILE__, __LINE__, msg)

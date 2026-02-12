/* 'error.h' contains function macros to print error messages &
   informational messages for debugging, 'PERR()' & 'PINF()'. */
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h> /* for 'fprintf ()' */

/* If defined, these macros enable printing error & informational
   messages */
#define	ENABLE_PERR
#define	ENABLE_PINF

/* Do no operation */
#define NOOP do {} while (0)

/* Print an error message */
#ifdef ENABLE_PERR
#define PERR(...) {                                     \
    perr_start ();                                      \
    fprintf (stderr, __FILE__ ":%d ", __LINE__);        \
    fprintf (stderr, __VA_ARGS__);                      \
    perr_end ();                                        \
  }
#else
#define PERR() NOOP
#endif

/* Print an informational message for debugging */
#ifdef ENABLE_PINF
#define PINF(...) {                                     \
    pinf_start ();                                      \
    /* fprintf (stderr, __FILE__ ":%d ", __LINE__); */  \
    fprintf (stderr, __VA_ARGS__);                      \
    pinf_end ();                                        \
  }
#else
#define PINF() NOOP
#endif

/* Print text at the start & end of an error or informational
   message */
void perr_start (void);
void perr_end (void);
void pinf_start (void);
void pinf_end (void);

#endif

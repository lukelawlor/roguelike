/* 'error.c' defines functions used to print error messages &
   informational messages for debugging. See 'error.h' for the
   function macros used to print such messages, 'PERR()' &
   'PINF()'. */
#include <stdio.h> /* for 'fprintf ()' & 'fputc ()' */

#include "error.h"
#include "main.h" /* for 'GAME_NAME_LOWERCASE' */

void
perr_start (void)
{
  fprintf (stderr, GAME_NAME_LOWERCASE ": error: ");
}

void
perr_end (void)
{
  fputc ('\n', stderr);
}

void
pinf_start (void)
{
  fprintf (stderr, GAME_NAME_LOWERCASE ": info: ");
}

void
pinf_end (void)
{
  perr_end ();
}

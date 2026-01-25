/* 'talk.c' defines functions to manipulate the "talkwin:" the area
   where text is commonly printed for the player to read. */
#include <string.h> /* for 'strlen()' */

#include <ncurses.h>

#include "talk.h"
#include "win.h"

/* The character to represent the cursor in talkwin */
#define TALKWIN_CURSOR_CHAR '*'

/* The maximum amount of characters that can fit in talkwin */
#define MAX_TALKWIN_CHARS (TALKWIN_W * TALKWIN_H)

/* Print the string 'str' on the talkwin */
void
talk (const char *str)
{
  /* The number of characters printed to talkwin */
  static long long chars_printed = 0;
  
  long long chars_to_be_printed;
  const int len = strlen (str);
  chars_to_be_printed = chars_printed + len;

  /* Print */
  if (chars_to_be_printed <= MAX_TALKWIN_CHARS)
      waddstr (g_talkwin, str);
  else
    {
      int chars_over_max = chars_to_be_printed - MAX_TALKWIN_CHARS;
      int chars_under_max = MAX_TALKWIN_CHARS - chars_printed;

      /* Index of 'str' */
      int i = 0;
      
      for (int j = 0; j < chars_under_max; ++j, ++i)
        waddch (g_talkwin, str[i]);

      /* Move to avoid printing out of view */
      wmove (g_talkwin, 0, 0);
      
      for (int j = 0; j < chars_over_max; ++j, ++i)
        waddch (g_talkwin, str[i]);
    }

  /* Print a character to represent the cursor. This is necessary to
     know where the last printed message is. */
  if (chars_to_be_printed == MAX_TALKWIN_CHARS)
    wmove (g_talkwin, 0, 0);
  waddch (g_talkwin, TALKWIN_CURSOR_CHAR);

  chars_printed = chars_to_be_printed % MAX_TALKWIN_CHARS;

  /* Move the cursor to the printed cursor so that it is overwritten
     by the next call to 'talk()' */
  wmove (g_talkwin, chars_printed / TALKWIN_W,
         chars_printed % TALKWIN_W);

  wrefresh (g_talkwin);
}

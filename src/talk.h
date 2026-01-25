/* 'talk.h' declares functions to manipulate the "talkwin:" the area
   where text is commonly printed for the player to read.

   Right now, the talkwin is an ncurses 'WINDOW' named 'g_talkwin',
   defined in './win.h'. */
#ifndef TALK_H
#define TALK_H

/* Print the string 'str' on the talkwin */
void talk (const char *str);

#endif

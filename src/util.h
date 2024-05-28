#ifndef UTIL_H
#define UTIL_H

#include <conio.h>

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24
#define TITLE_X 13
#define FACE_X 11
#define SWORD_X FACE_X + 15
#define TITLE_DRAWING_Y 3
#define PROMPT_CAP 25

#define MAIN_HALL 0
#define NORTH 1
#define SOUTH 2
#define DENNIS 3

#define FLAG_STARTED 1
#define FLAG_SCROLL 2
#define FLAG_GOING 4 // used by doLook(), if set, look command was used, otherwise go was assumed to be used
#define GET_FLAG(f) (flags & f) == f
#define SET_FLAG(f) flags |= f
#define UNSET_FLAG(f) flags &= (~f)

extern unsigned char flags;
extern signed short score;
extern unsigned char flaskGets;
extern unsigned char location;
extern char input[PROMPT_CAP];

#define CLEAR() \
	clrscr(); \
	gotoxy(0, 0);

#endif
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

#define UNSET_LOCATION 0
#define MAIN_HALL 1
#define NORTH 2
#define SOUTH 3
#define DENNIS 4

#define THING_NOTHING 0
#define THING_UNKNOWN 1
#define THING_PARAPETS 2
#define THING_DENNIS 3
#define THING_JIMBERJAM 4
#define THING_ROPE 5
#define THING_FLASK 6
#define THING_SCROLL 7

#define FLAG_STARTED 1
#define FLAG_SCROLL 2
#define FLAG_BAUBEL 4
#define FLAG_GOING 8 // used by doLook(), if set, look command was used, otherwise go was assumed to be used
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
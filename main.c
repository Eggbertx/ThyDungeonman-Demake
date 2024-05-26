#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24
#define TITLE_X  13
#define FACE_X 11
#define SWORD_X FACE_X + 15
#define TITLE_DRAWING_Y 3
#define PROMPT_CAP 25

#define MAIN_HALL 0
#define NORTH 1
#define SOUTH 2
#define DENNIS 3

unsigned char started = 0;
signed short score = 0;
unsigned char flaskGets = 0;
unsigned char gotFlask = 0;
unsigned char location = MAIN_HALL;
char input[PROMPT_CAP];

void yonTitleScreen() {
	unsigned char i;
	clrscr();
	cursor(0);
	cputsxy(TITLE_X, 1, "Thy Dungeonman");

	// draw the face
	cputsxy(FACE_X, 4, "/\\");
	cputsxy(FACE_X+8, 4, "/\\");
	cputsxy(FACE_X, 5, "!!/----\\!!");
	cputsxy(FACE_X, 6, "\\_------_/");
	cputsxy(FACE_X+1, 8, "/ o  o \\");
	cputsxy(FACE_X+1, 10, "/  !!  \\");
	cputsxy(FACE_X+1, 12, "/ ---- \\");
	cputsxy(FACE_X+1, 14, "/\\/\\/\\/\\");

	// draw the sword
	cputsxy(SWORD_X, 4, "/\\");
	for(i = 5; i < 10; i++)
		cputsxy(SWORD_X, i, "!!");
	cputsxy(SWORD_X-2, i, "o_!!_o");
	cputsxy(SWORD_X-2, i+1, "\\----/");
	cputsxy(SWORD_X, i+2, "!!");
	cputsxy(SWORD_X, i+3, "oo");

	cputsxy(2, i+9, "Press any key to enter yon Dungeon");
}

void doPrompt() {
	char ch = 0;
	unsigned char promptPtr = 0;
	memset(input, 0, PROMPT_CAP);
	gotoxy(0, SCREEN_HEIGHT-2);
	puts("What wouldst thou deau?");
	cputc('>');
	cursor(1);
	while(1) {
		if(promptPtr >= PROMPT_CAP)
			continue;
		ch = cgetc();
		if(ch == 10 || ch == 13)
			break; // new line
		if(ch == 8 && promptPtr > 0) {
			input[--promptPtr] = 0;
			cputc(' ');
			gotox(promptPtr+1);
			cputc(' ');
			gotox(promptPtr+1);
		} else {
			input[promptPtr++] = ch;
			cputc(ch);
		}
	}
	memset(input + promptPtr, 0, PROMPT_CAP);
}

void look() {
	switch (location)
	{
	case MAIN_HALL:
		if(!started) {
			puts("THY DUNGEONMAN\n\nYOU ARE THY DUNGEONMAN\n\n");
		}
		printf("Ye find yeself in yon dungeon. ");
		if(gotFlask)
			printf("Back\nyonder there is a FLASK. ");
		else
			puts("Ye see a SCROLL. Behind ye SCROLL is a FLASK.");
		puts("Obvious exits are NORTH, SOUTH, and DENNIS.");
		break;
	
	default:
		break;
	}
}

int main() {
	yonTitleScreen();
	cgetc();
	do {
		clrscr();
		gotoxy(0, 0);
		look();
		doPrompt();
	} while(score > -1);
	getchar();
	return 0;
}

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
unsigned char gotScroll = 0;
unsigned char location = MAIN_HALL;
char input[PROMPT_CAP];

void clear() {
	clrscr();
	gotoxy(0, 0);
}

void yonTitleScreen() {
	unsigned char i;
	clear();
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
			// backspace, decrement the prompt position and draw a space over where the character was
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

void doGet() {
	char* getting = input + 4;
	char getCmp = 1;

	switch(location) {
	case MAIN_HALL:
		break;
	case NORTH:
		break;
	case SOUTH:
		break;
	case DENNIS:
		break;
	}
}

void parsePrompt() {
	char inputCmp = 1;
	strlower(input);
	printf("\nInput: '%s'\n", input);
	inputCmp = strncmp("get ", input, 4);
	if(inputCmp == 0) {
		doGet();
	}
	getchar();
}



void look() {
	switch(location) {
	case MAIN_HALL:
		if(!started)
			puts("THY DUNGEONMAN\n\nYOU ARE THY DUNGEONMAN\n\n");

		printf("Ye find yeself in yon dungeon. ");
		
		if(gotScroll)
			puts("Back yonder there is a FLASK. ");
		else
			puts("Ye see a SCROLL. Behind ye SCROLL is a FLASK.");

		printf("Obvious exits are NORTH, SOUTH, and DENNIS.");
		break;
	
	default:
		break;
	}
}

int main() {
	yonTitleScreen();
	cgetc();
	do {
		clear();
		look();
		doPrompt();
		parsePrompt();
	} while(score > -1);
	getchar();
	return 0;
}

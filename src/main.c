#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "commands.h"

void parsePrompt();

void yonTitleScreen() {
	unsigned char i;
	CLEAR();
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


void parsePrompt() {
	strlower(input);
	CLEAR();
	if(strncmp("get ", input, 4) == 0) {
		if(doGet() != 0) {
			puts("Thou cannotst get that. Quit making stuffeth up!");
		}
		return;
	}

	if(strncmp("go ", input, 3) == 0) {
		if(doGo() != 0) {
			puts("Thou cannotst go there. Who do thou think thou art? A magistrate?!");
		}
		return;
	}

	if(strcmp("die", input) == 0) {
		score -= 100;
		printf("That wasn't very smart.\nYour score was %d\n\n", score);
		return;
	}

	if(strcmp("look", input) == 0) {
		UNSET_FLAG(FLAG_GOING);
		doLook();
		return;
	}

	puts("That does not computeth. Type HELP if thou needs of it.");
	return;
}

int main() {
	yonTitleScreen();
	cgetc();
	doLook();
	do {
		doPrompt();
		parsePrompt();
	} while(score > -1);
	getchar();
	return 0;
}

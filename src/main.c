#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "commands.h"

void yonTitleScreen() {
	unsigned char i = 5;
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
	while(i < 10)
		cputsxy(SWORD_X, i++, "!!");
	cputsxy(SWORD_X-2, i, "o_!!_o");
	cputsxy(SWORD_X-2, ++i, "\\----/");
	cputsxy(SWORD_X, ++i, "!!");
	cputsxy(SWORD_X, ++i, "oo");

	cputsxy(2, i+6, "Press any key to enter yon Dungeon");
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


unsigned char parsePrompt() {
	strlower(input);
	CLEAR();
	if(strncmp("get ", input, 4) == 0) {
		if(doGet()) {
			puts("Thou cannotst get that. Quit making stuffeth up!");
		}
		return GET_FLAG(FLAG_DEAD)?0:1;
	}

	if(strncmp("go ", input, 3) == 0) {
		if(doGo()) {
			puts("Thou cannotst go there. Who do thou think thou art? A magistrate?!");
		}
		return 1;
	}

	if(strcmp("die", input) == 0) {
		score -= 100;
		printf("That wasn't very smart.\nYour score was %d\n\n", score);
		return 0;
	}

	if(strcmp("look", input) == 0 || strcmp("help", input) == 0) {
		doGoOrLook(location);
		return 1;
	}

	if(strcmp("not dennis", input) == 0 && location == LOCATION_DENNIS) {
		// for compatibility with the main game, since "go dennis" works but "go not dennis" doesn't for some reason
		doGoOrLook(LOCATION_DUNGEON);
		return 1;
	}

	puts("That does not computeth. Type HELP if thou needs of it.");

	return 1;
}

int main() {
	unsigned char alive = 0;
	yonTitleScreen();
	cgetc();
	doGoOrLook(location);
	do {
		doPrompt();
		alive = parsePrompt();
	} while(alive == 1);
	getchar();
	return 0;
}

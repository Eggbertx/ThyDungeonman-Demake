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
unsigned char lookOrGoMsg = 0; // used by look(), if 0, look command was used, otherwise go was assumed to be used
char input[PROMPT_CAP];

void parsePrompt();

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

unsigned char doGet() {
	char* getting = input + 4;

	switch(location) {
	case MAIN_HALL:
		if(strcmp("flask", getting) == 0 || strcmp("ye flask", getting) == 0 || strcmp("the flask", getting) == 0) {
			clear();
			if(++flaskGets < 3) {
				score++;
				puts(
					"You cannot get the FLASK. It is firmly bolted to a wall which is firmly bolted to "
					"the rest of the dungeon which is probably bolted to a castle. Never you mind."
				);
				doPrompt();
				parsePrompt();
			} else {
				score -= 1000;
				printf(
					"Okay, okay. You unbolt yon FLASK and hold it aloft. A great shaking begins. The "
					"dungeon ceiling collapses down upon you, crushing you in twain. Apparently this "
					"was a load-bearing FLASK.\n"
					"Your score was %d", score
				);
				getchar();
				return 0;
			}
		}
		break;
	case NORTH:
		break;
	case SOUTH:
		break;
	case DENNIS:
		break;
	}

	return 1;
}

unsigned char doGo() {
	char* goingTo = input + 3;

	switch(location) {
	case MAIN_HALL:
		if(strcmp("north", goingTo) == 0) {
			location = NORTH;
			return 0;
		}
		break;
	case NORTH:
		break;
	case SOUTH:
		break;
	case DENNIS:
		break;
	}
	return 1;
}

void parsePrompt() {
	strlower(input);

	if(strncmp("get ", input, 4) == 0) {
		if(doGet() != 0) {
			clear();
			puts("Thou cannotst get that. Quit making stuffeth up!");
			doPrompt();
			parsePrompt();
		}
		goto done;
	}

	if(strncmp("go ", input, 3) == 0) {
		if(doGo() != 0) {
			clear();
			puts("Thou cannotst go there. Who do thou think thou art? A magistrate?!");
			doPrompt();
			parsePrompt();
		}
		goto done;
	}

	if(strcmp("die", input) == 0) {
		score -= 100;
		clear();
		printf("That wasn't very smart.\nYour score was %d\n\n", score);
	}

	done:
	return;
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
	case NORTH:
		cputs(lookOrGoMsg?
			"Ye thou now be at parapets. ":
			"You go NORTH through yon corridor. You arraive at parapets. ");
		puts("Ye see a ROPE.\nObvious exits are SOUTH.");
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

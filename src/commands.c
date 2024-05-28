#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "util.h"

unsigned char doGet() {
	char* getting = input + 4;

	switch(location) {
	case MAIN_HALL:
		CLEAR();
		if(strcmp("flask", getting) == 0 || strcmp("ye flask", getting) == 0 || strcmp("the flask", getting) == 0) {
			if(++flaskGets < 3) {
				score++;
				puts(
					"You cannot get the FLASK. It is firmly bolted to a wall which is firmly bolted to "
					"the rest of the dungeon which is probably bolted to a castle. Never you mind."
				);
				return 0;
			} else {
				score -= 1000;
				printf(
					"Okay, okay. You unbolt yon FLASK and hold it aloft. A great shaking begins. The "
					"dungeon ceiling collapses down upon you, crushing you in twain. Apparently this "
					"was a load-bearing FLASK.\n"
					"Your score was %d", score
				);
				return 0;
			}
		} else if(strcmp("scroll", getting) == 0) {
			SET_FLAG(FLAG_SCROLL);
			puts(
				"Ye takes the SCROLL and reads of it. It doth say:\n\n"
				"BEWARE READER OF YE SCROLL,\n"
				"DANGERS AWAIT TO THE -\n\n"
				"The SCROLL disappears in thy hands with ye olde ZAP!"
			);
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


unsigned char doGo() {
	char* goingTo = input + 3;

	switch(location) {
	case MAIN_HALL:
		if(strcmp("north", goingTo) == 0) {
			location = NORTH;
			doLook();
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

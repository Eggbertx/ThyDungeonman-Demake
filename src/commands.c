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
			if(GET_FLAG(FLAG_SCROLL)) {
				score--;
				puts("Ye doth suffer from memory loss. YE SCROLL is no more. Honestly.");
			} else {
				SET_FLAG(FLAG_SCROLL);
				puts(
					"Ye takes the SCROLL and reads of it. It doth say:\n\n"
					"BEWARE READER OF YE SCROLL,\n"
					"DANGERS AWAIT TO THE -\n\n"
					"The SCROLL disappears in thy hands with ye olde ZAP!"
				);
				score += 2;
			}
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

// assumes we've already validated the location
void lookAt(unsigned char thing) {
	switch(thing) {
	case THING_PARAPETS:
		puts("Well, they're parapets. This much we know for sure.");
		break;
	case THING_DENNIS:
		puts("That jimberjam really makes the outfit.");
	case THING_JIMBERJAM:
		puts("Man, that art a nice jimberjam.");
		break;
	case THING_ROPE:
		puts("It looks okay. You've seen better.");
		break;
	case THING_FLASK:
		puts("Looks like you could quaff some serious mead out of that thing.");
		break;
	case THING_SCROLL:
		puts(GET_FLAG(FLAG_SCROLL)?
			"Ye seeth nothing wheretofore it went ZAP.":
			"Parchment, definitely parchment. I'd recognize it anywhere.");
		break;
	default:
		puts("It looketh pretty awesome.");
		break;
	}
}

void doLook() {
	CLEAR();
	switch(location) {
	case MAIN_HALL:
		if(!GET_FLAG(FLAG_STARTED))
			puts("THY DUNGEONMAN\n\nYOU ARE THY DUNGEONMAN\n\n");
		SET_FLAG(FLAG_STARTED);

		printf("Ye find yeself in yon dungeon. ");
		
		puts(GET_FLAG(FLAG_SCROLL)?
			"Back yonder there is a FLASK. ":
			"Ye see a SCROLL. Behind ye SCROLL is a FLASK.");

		puts("Obvious exits are NORTH, SOUTH, and DENNIS.");
		break;
	case NORTH:
		cputs(GET_FLAG(FLAG_GOING)?
			"Ye thou now be at parapets. ":
			"You go NORTH through yon corridor. You arrive at parapets. ");
		puts("Ye see a ROPE.\nObvious exits are SOUTH.");
		break;
	default:
		break;
	}
}

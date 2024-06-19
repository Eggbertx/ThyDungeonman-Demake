#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "util.h"

unsigned char doGet() {
	char* getting = input + 4;

	switch(location) {
	case LOCATION_DUNGEON:
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
				SET_FLAG(FLAG_DEAD);
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
	case LOCATION_NORTH:
		break;
	case LOCATION_SOUTH:
		break;
	case LOCATION_DENNIS:
		break;
	}

	return 1;
}


unsigned char doGo() {
	char* goingTo = input + 3;

	switch(location) {
	case LOCATION_DUNGEON:
		if(strcmp("north", goingTo) == 0) {
			doGoOrLook(LOCATION_NORTH);
			return 0;
		}
		if(strcmp("south", goingTo) == 0) {
			doGoOrLook(LOCATION_SOUTH);
			return 0;
		}
		if(strcmp("dennis", goingTo) == 0) {
			doGoOrLook(LOCATION_DENNIS);
			return 0;
		}
		break;
	case LOCATION_NORTH:
		if(strcmp("south", goingTo) == 0) {
			doGoOrLook(LOCATION_DUNGEON);
			return 0;
		}
		break;
	case LOCATION_SOUTH:
		if(strcmp("north", goingTo) == 0) {
			doGoOrLook(LOCATION_DUNGEON);
			return 0;
		}
		break;
	case LOCATION_DENNIS:
		if(strcmp("not dennis", goingTo) == 0) {
			doGoOrLook(LOCATION_DUNGEON);
			return 0;
		}
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

// if newLoc == location, look was used, otherwise go <location> was used
void doGoOrLook(unsigned char newLoc) {
	CLEAR();
	switch(newLoc) {
	case LOCATION_DUNGEON:
		if(!GET_FLAG(FLAG_STARTED)) {
			SET_FLAG(FLAG_STARTED);
			puts("THY DUNGEONMAN\n\nYOU ARE THY DUNGEONMAN\n\n");
		} else if(location == LOCATION_NORTH) {
			puts("You go SOUTH back through yon corridor.");
		} else if(location == LOCATION_SOUTH) {
			puts("You go NORTH.");
		} else if(location == LOCATION_DENNIS) {
			puts("You go NOT DENNIS.");
		}

		printf("Ye find yeself in yon dungeon. ");
		
		puts(GET_FLAG(FLAG_SCROLL)?
			"Back yonder there is a FLASK. ":
			"Ye see a SCROLL. Behind ye SCROLL is a FLASK.");

		puts("Obvious exits are NORTH, SOUTH, and DENNIS.");
		break;
	case LOCATION_NORTH:
		cputs((location == newLoc)?
			"Ye thou now be at parapets. ":
			"You go NORTH through yon corridor. You arrive at parapets. ");
		puts("Ye see a ROPE.\nObvious exits are SOUTH.");
		break;
	default:
		break;
	}
	location = newLoc;
}

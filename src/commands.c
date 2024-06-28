#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "util.h"

unsigned char doGet() {
	char* getting = input + 4;

	if(strcmp("graphics", getting) == 0) {
		puts("Graphics shmaphics...for sooth!");
		return 1;
	}

	switch(location) {
	case LOCATION_DUNGEON:
		if(strcmp("flask", getting) == 0 || strcmp("ye flask", getting) == 0 || strcmp("the flask", getting) == 0) {
			if(++flaskGets < 3) {
				score++;
				puts(
					"You cannot get the FLASK. It is firmly bolted to a wall which is firmly bolted to "
					"the rest of the dungeon which is probably bolted to a castle. Never you mind."
				);
				return 1;
			} else {
				score -= 1000;
				printf(
					"Okay, okay. You unbolt yon FLASK and hold it aloft. A great shaking begins. The "
					"dungeon ceiling collapses down upon you, crushing you in twain. Apparently this "
					"was a load-bearing FLASK.\n"
					"Your score was %d", score
				);
				SET_FLAG(FLAG_DEAD);
				return 1;
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
			return 1;
		}
		break;
	case LOCATION_NORTH:
		if(strcmp("rope", getting) == 0) {
			printf(
				"You attempt to take ye ROPE but alas it is enchanted! It glows a mustard red and smells like a public privy. "
				"The ROPE wraps round your neck and hangs you from parapets. With your last breath, you wonder what parapets are.\n"
				"Your score was %d", --score
			);
			SET_FLAG(FLAG_DEAD);
			return 1;
		}
	case LOCATION_SOUTH:
		if(strcmp("trinket", getting) == 0) {
			if(GET_FLAG(FLAG_BAUBEL)) {
				puts("Sigh. The trinket is in thou pouchel. Recallest thou?");
				score--;
			} else {
				puts(
					"Ye getsts yon TRINKET and discover it to be a bauble. You rejoice at your good fortune. You shove the TRINKET "
					"in your pouchel. It kinda hurts."
				);
				score += 2;
				SET_FLAG(FLAG_BAUBEL);
			}
			return 1;
		}
	case LOCATION_DENNIS:
		break;
	}

	return 0;
}


unsigned char doGo() {
	char* goingTo = input + 3;

	switch(location) {
	case LOCATION_DUNGEON:
		if(strcmp("north", goingTo) == 0) {
			doGoOrLook(LOCATION_NORTH);
			return 1;
		}
		if(strcmp("south", goingTo) == 0) {
			doGoOrLook(LOCATION_SOUTH);
			return 1;
		}
		if(strcmp("dennis", goingTo) == 0) {
			doGoOrLook(LOCATION_DENNIS);
			return 1;
		}
		break;
	case LOCATION_NORTH:
		if(strcmp("south", goingTo) == 0) {
			doGoOrLook(LOCATION_DUNGEON);
			return 1;
		}
		break;
	case LOCATION_SOUTH:
		if(strcmp("north", goingTo) == 0) {
			doGoOrLook(LOCATION_DUNGEON);
			return 1;
		}
		break;
	case LOCATION_DENNIS:
		if(strcmp("not dennis", goingTo) == 0) {
			doGoOrLook(LOCATION_DUNGEON);
			return 1;
		}
		break;
	}
	return 0;
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
	case THING_TRINKET:
		puts(GET_FLAG(FLAG_BAUBEL)?
			"Just a bulge in thou pouchel at this point.":
			"Quit looking! Just get it already."
		);
		break;
	default:
		puts("It looketh pretty awesome.");
		break;
	}
}

unsigned char doTalk(char* talkTo) {
	unsigned char noSubject = strlen(talkTo) == 0;
	CLEAR();
	if(location == LOCATION_DENNIS && (noSubject || strcmp("dennis", talkTo) == 0)) {
		puts(
			"You engage Dennis in leisurely discussion. Ye learns that his jimberjam was purchased on sale at a discount "
			"market and that he enjoys pacing about nervously. You become bored and begin thinking about parapets."
		);
		return 1;
	}
	if(!noSubject) {
		printf("Who is \"%s\"? Your new boyfriend?! Someone at work you don't want me to meeteth?!", talkTo);
		return 1;
	}
	return 0;
}

// if newLoc == location, look was used, otherwise go <newLoc> was used
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
	case LOCATION_SOUTH:
		if(location == newLoc) {
			puts(GET_FLAG(FLAG_BAUBEL)?
				"Ye stand high above a canyon-like depression.":
				"Ye stand yeself close to a yet-unnamed escarpment. Nonetheless, ye spies a TRINKET."
			);
		} else {
			puts(
				"You head south to an embankment. Or maybe a chasm. You can't decide which. "
				"Anyway, ye spies a TRINKET."
			);
		}
		puts("Obvious exits are NORTH.");
		break;
	case LOCATION_DENNIS:
		puts(
			"Ye arrive at Dennis. He wears a sporty frock coat and a long jimberjam. He paces about nervously. "
			"Obvious exits are NOT DENNIS"
		);
		break;
	default:
		break;
	}
	location = newLoc;
}

void doLook(char* thing) {
	switch (location) {
	case LOCATION_DUNGEON:
		if(strcmp("flask", thing) == 0) {
			lookAt(THING_FLASK);
			return;
		} else if(strcmp("scroll", thing) == 0) {
			lookAt(THING_SCROLL);
			return;
		}
		break;
	case LOCATION_NORTH:
		if(strcmp("rope", thing) == 0) {
			lookAt(THING_ROPE);
			return;
		} else if(strcmp("parapets", thing) == 0) {
			lookAt(THING_PARAPETS);
			return;
		}
		break;
	case LOCATION_SOUTH:
		break;
	case LOCATION_DENNIS:
		break;
	default:
		break;
	}
	lookAt(THING_UNKNOWN);
}
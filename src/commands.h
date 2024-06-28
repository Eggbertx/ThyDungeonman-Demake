#ifndef COMMANDS_H
#define COMMANDS_H

unsigned char doGo();

void doGoOrLook(unsigned char newLoc);

void doLook(char* thing);

unsigned char doGet();

unsigned char doTalk(char* talkTo);

#endif
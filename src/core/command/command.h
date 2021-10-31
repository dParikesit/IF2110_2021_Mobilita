#ifndef COMMAND_H
#define COMMAND_H

#include "../../system/stats/stats.h"
#include "../../system/map/map.h"
#include "../../adt/queue/prioqueue.h"
#include "../time/time.h"

typedef enum CommandType {
	NEW_GAME = 0,
	EXIT = 1,
	LOAD_GAME = 2,
	MOVE = 3,
	PICK_UP = 4,
	DROP_OFF = 5,
	MAP = 6,
	TO_DO = 7,
	IN_PROGRESS = 8,
	BUY = 9,
	INVENTORY = 10,
	HELP = 11,
	SAVE_GAME = 12,
	RETURN = 13,
	INVALID = 14
} CommandType;

static inline const char * const stringCommand[] = {
	[NEW_GAME] = "NEW_GAME",
	[EXIT] = "EXIT",
	[LOAD_GAME] = "LOAD_GAME",
	[MOVE] = "MOVE",
	[PICK_UP] = "PICK_UP",
	[DROP_OFF] = "DROP_OFF",
	[MAP] = "MAP",
	[TO_DO] = "TO_DO",
	[IN_PROGRESS] = "IN_PROGRESS",
	[BUY] = "BUY",
	[INVENTORY] = "INVENTORY",
	[HELP] = "HELP",
	[SAVE_GAME] = "SAVE_GAME",
	[RETURN] = "RETURN",
	[INVALID] = "INVALID"
};

void showMainMenu(); // Show main menu command
void showListCommand(); // Show available command list (HELP)
CommandType parseCommand(); // Read and parse command from stdin.
boolean isCommandAvailable(CommandType cmdType); // Check if command can be run
void runCommand(CommandType cmdType); // Run command

#endif
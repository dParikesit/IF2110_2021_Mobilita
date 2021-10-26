#ifndef STREAM_h
#define STREAM_h

#include <stdio.h>
#include "../../adt/machine/wordmachine.h"

// Initialize
void initStream(FILE* file);
void closeStream();

// Helper
boolean isEqualCharArray(char* input, char* output);

// Read stuff
char* toCharArray();
int toInt();
void* toArbitrary();

// Write stuffs
void fromCharArray(char* str);
void fromInt(int value);
void fromArbitrary(void* value, int size, int amount);

#endif
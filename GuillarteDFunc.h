#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 20

void
titleScreen();

int
promptChoice(int min,
			 int max);
			 
void
login(char adminPass[]);

void
manageData();
			 


#endif
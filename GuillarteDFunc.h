#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 20

typedef char str100 [100];

struct question
{
    char topic[50];
    int number;
    char questionText[200];
    char choices[3][50];
    int correctAns;
};

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
#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 20

typedef char str100 [101];
typedef char str50 [51];
typedef char str200 [201];

struct question
{
    str50 topic;
    int number;
    str200 questionText;
    str50 choices[3];
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
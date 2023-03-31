#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_PASS_LEN 20
#define MAX_RECORDS 1000
#define MAX_CHOICES 3
#define MAX_QTEXT 200
#define MAX_TOPIC_ANS 50
#define MAX_TOPIC 5

typedef char str50 [MAX_TOPIC_ANS];
typedef char str200 [MAX_QTEXT];
typedef char str20 [MAX_PASS_LEN];


struct question
{
    str50 topic[MAX_TOPIC];
    int number;
    str200 questionText;
    str50 choices[MAX_CHOICES];
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

int
addRecord(struct question records[MAX_RECORDS],
		  int count);

void
editRecord(struct question records[MAX_RECORDS],
		   int count);
			 


#endif
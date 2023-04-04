#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_PASS_LEN 20
#define MAX_STR_LEN 50
#define MAX_QTEXT_LEN 200
#define MAX_RECORDS 1000
#define MAX_CHOICES 3
#define MAX_TOPICS 5

typedef char str50 [MAX_STR_LEN];
typedef char str200 [MAX_QTEXT_LEN];
typedef char str20 [MAX_PASS_LEN];


struct question
{
    str50 sTopic;
    int nQNum;
    str200 sQText;
    str50 sChoices[MAX_CHOICES];
    int nCorrAns;
};

void
displayMenu();

int
promptChoice(int nMin,
			 int nMax);
			 
void
login(str20 sAdminPass);

void
manageData();

int
findRecord(struct question records[MAX_RECORDS],
		   int nCount,
		   char* pQText,
		   char* pAnswer);
		   
int getLastQNum(struct question records[MAX_RECORDS],
				int nCount,
				char* pTopic);
				
int
addRecord(struct question records[MAX_RECORDS],
		  int nCount);

void
removeNewLine(char* pStr);

void
displayTopics(struct question records[MAX_RECORDS],
			  int nCount);

void
displayQuestions(struct question records[MAX_RECORDS],
                 int nCount,
                 char* pTopic,
                 int arrQstIndices[MAX_RECORDS],
                 int *pQstNum);

void
displayQuestion(struct question record);
                   
int
validateAnswer(struct question record,
               str50 sNewAns);

void
editRecord(struct question records[MAX_RECORDS],
		   int nCount);

int
deleteRecord(struct question records[MAX_RECORDS],
             int nCount);

#endif
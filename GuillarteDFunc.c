#include "GuillarteDFunc.h"

/*This function displays the title screen when you start the game up.
*/
void
displayMenu()
{
	int nBorder;

	printf("\n");

	/* Prints top border of title screen */
	for(nBorder = 0; nBorder < 50; nBorder++)
	{

		/* Prints ╔ */
		if(nBorder == 0)
			printf("%c", 201);

			/* Prints ╗ */
		else if(nBorder == 49)
			printf("%c", 187);

			/* Prints ═ */
		else
			printf("%c", 205);
	}

	/* Prints program title and author information, 186 here is ║ */
	printf("\n%c%*s%*s%c\n", 186, 38, "~General Knowledge Quiz Game~", 10, " ", 186);
	printf("%c%*s%*s%c\n", 186, 35, "Dana Louise A. Guillarte", 13, " ", 186);
	printf("%c%*s%*s%c\n", 186, 25, "S23A", 23, " ", 186);

	/* Prints divider */
	for (nBorder = 0; nBorder < 50; nBorder++)
	{

		/* Prints ╠ */
		if (nBorder == 0)
			printf("%c", 204);

			/* Prints ╣ */
		else if (nBorder == 49)
			printf("%c", 185);

			/* Prints ═ */
		else
			printf("%c", 205);
	}

	/* Prints game options and exit, 186 here is ║ */
	printf("\n%c%*s%*s%c", 186, 27, "[1] Play", 21, " ", 186);
	printf("\n%c%*s%*s%c", 186, 30, "[2] Manage Data", 18, " ", 186);
	printf("\n%c%*s%*s%c\n", 186, 27, "[3] Exit", 21, " ", 186);

	/* Prints bottom border */
	for (nBorder = 0; nBorder < 50; nBorder++)
	{

		/* prints ╚ */
		if (nBorder == 0)
			printf("%c", 200);

			/* prints ╝ */
		else if (nBorder == 49)
			printf("%c\n", 188);

			/* Prints ═ */
		else
			printf("%c", 205);
	}
}

/* This function checks if the scanned entry of the user is within the range that is accepted
   @param min - minimum accepted value
   @param max - maximum accepted value
   @return choice if the choice is in the range [min, max], else 0
*/
int
promptChoice(int nMin,
             int nMax)
{
	int nChoice;

	/* Loops until a valid input is received */
	do
	{

		/* Prompts user for their choice */
		scanf("%d", &nChoice);

		/* Checks if input is within valid range */
		if (!(nChoice >= nMin && nChoice <= nMax))
		{
			printf("Invalid input!\n");
			printf("Enter valid choice [%d - %d]: \n", nMin, nMax);
		}
	} while (!(nChoice >= nMin && nChoice <= nMax));

	/* Returns the valid input */
	return nChoice;
}

/* This function accepts the password entered by the user and checks if correct
   @param sAdminPass - array containing the admin password for checking
   @param nRecords - number of records in the array
   @param records[MAX_RECORDS] - array containing the questions and answers
   @return number of records in the array
*/
int
login(str20 sAdminPass,
      int nRecords,
      struct question records[MAX_RECORDS])
{
	char cInput;
	char sPassword[MAX_PASS_LEN + 1];
	int nCount = 0, nChoice = 1;

	printf("Enter admin password: ");

	/* Gets password from user */
	while ((cInput = getch()) != '\r' && nCount < MAX_PASS_LEN)
	{

		/* If user presses backspace, move back one character and overwrite
		   with a space */
		if (cInput == '\b' && nCount > 0)
		{
			printf("\b \b");
			nCount--;
		}

			/* If user inputs any other character besides backspace, tab or null,
			   print a * to screen and save to sPassword */
		else if (cInput != '\b' && cInput != '\t' && cInput != 0)
		{
			printf("*");
			sPassword[nCount++] = cInput;
		}
	}
	sPassword[nCount] = '\0';
	printf("\n");

	/* If the password entered is incorrect, give the user the option to try again */
	while (strcmp(sPassword, sAdminPass) != 0 && nChoice == 1)
	{
		printf("Incorrect password.\n");
		printf("Press 1 to try again, or any other key to go back to main menu: ");
		scanf("%d", &nChoice);

		/* If user chooses to try again, prompt for password again */
		if (nChoice == 1)
		{
			printf("Enter admin password: ");
			nCount = 0;

			/* Gets password from user again */
			while ((cInput = getch()) != '\r' && nCount < MAX_PASS_LEN)
			{

				/* If user presses backspace, move back one character
				   and overwrite with a space */
				if (cInput == '\b' && nCount > 0)
				{
					printf("\b \b");
					nCount--;
				}

					/* If user inputs any other character besides backspace, tab or null,
					   print a * to screen and save to sPassword */
				else if (cInput != '\b' && cInput != '\t' && cInput != 0)
				{
					printf("*");
					sPassword[nCount++] = cInput;
				}
			}
			sPassword[nCount] = '\0';
			printf("\n");
		}
	}

	/* If the password entered is correct, login is successful
	   and user is directed to manageData */
	if (strcmp(sPassword, sAdminPass) == 0)
	{
		printf("Login successful!\n\n");

		/* Displays user-friendly interface for managing data */
		nRecords = manageData(nRecords, records);
	}
	else
	{
		printf("Going back to main menu.\n\n");

		/* Goes back to main menu */
		displayMenu();
	}

	/* Returns the number of records */
	return nRecords;
}


/* This function displays the user-friendly Manage Data UI and manages
   the question records of the game
   @param nRecords - number of records in the array
   @param records[MAX_RECORDS] - array containing the questions and answers
   @return number of records in the array
*/
int
manageData(int nRecords,
           struct question records [MAX_RECORDS])
{
	int nChoice;

	/* Loops until user chooses to go back to main menu */
	do
	{
		printf("MAIN MENU\n");
		printf("1. Add Record\n");
		printf("2. Edit Record\n");
		printf("3. Delete Record\n");
		printf("4. Import Data\n");
		printf("5. Export Data\n");
		printf("6. Go Back to Main Menu\n");

		printf("Enter choice: ");
		scanf("%d", &nChoice);

		/* Checks if input is within valid range */
		switch (nChoice)
		{

			/* Adds a new record */
			case 1:
				printf("Add Record selected.\n\n");

				/* Increases the number of records by 1 after adding the new record */
				nRecords = addRecord(records, nRecords);
				break;

				/* Edits an existing record */
			case 2:
				printf("Edit Record selected.\n\n");

				/* Calls the editRecord function to edit a record */
				editRecord(records, nRecords);
				break;

				/* Deletes an existing record */
			case 3:
				printf("Delete Record selected.\n\n");

				/* Calls the deleteRecord function to edit a record */
				nRecords = deleteRecord(records, nRecords);
				break;

				/* Imports data from a file */
			case 4:
				printf("Import Data selected.\n\n");

				/* Calls the importData function to import records from a file */
				nRecords = importData(records, MAX_RECORDS);
				break;

				/* Exports data to a file */
			case 5:
				printf("Export Data selected.\n\n");

				if (nRecords == 0)
				{
					/* Tells the user that export can't be done if there are no
					   records */
					printf("\nI'm sorry, but we cannot export any data");
					printf(" if there are no records. Try again later.\n\n\n");
				}
				else
				{

					/* Calls the exportData function to export records to a file */
					exportData(records, nRecords);
				}
				break;

				/* Goes back to the main menu */
			case 6:
				printf("Going back to main menu.\n\n");
				break;

				/* Invalid choice */
			default:
				printf("Invalid choice. Try again.\n\n");
		}
	} while (nChoice != 6);

	/* Returns the number of records */
	return nRecords;
}

/* This function removes questions that are duplicates of each other
   @param records[] - array of question records
   @param pCount - address of number of records in the array
*/
void
removeDuplicates(struct question records[MAX_RECORDS],
                 int* pCount)
{
	struct question uniqueRecords[MAX_RECORDS];
	int uniqueCount = 0;
	int i, j, isFound;

	/* Loops through the records array and checks if the current record
	   is a duplicate of any record in the uniqueRecords array */
	for (i = 0; i < *pCount; i++)
	{
		isFound = 0;
		for (j = 0; j < uniqueCount; j++)
		{
			if (strcmp(records[i].sTopic, uniqueRecords[j].sTopic) == 0 &&
			    strcmp(records[i].sQText, uniqueRecords[j].sQText) == 0 &&
			    strcmp(records[i].sChoices[0], uniqueRecords[j].sChoices[0]) == 0 &&
			    strcmp(records[i].sChoices[1], uniqueRecords[j].sChoices[1]) == 0 &&
			    strcmp(records[i].sChoices[2], uniqueRecords[j].sChoices[2]) == 0 &&
			    records[i].nCorrAns == uniqueRecords[j].nCorrAns)
			{
				isFound = 1;
			}
		}

		/* If the current record is not a duplicate, add it to the uniqueRecords
		   array */
		if (!isFound)
		{
			uniqueRecords[uniqueCount] = records[i];
			uniqueCount++;
		}
	}

	/* Copies the unique records to the records array */
	for (i = 0; i < uniqueCount; i++)
	{
		records[i] = uniqueRecords[i];
	}

	/* Updates the number of records */
	*pCount = uniqueCount;
}

/* This function finds a record with the given question text and answer
   @param records[MAX_RECORDS] - array of question records
   @param nCount - number of records
   @param questionText - the question text to search for
   @param answer - the answer to search for
   @return the index of the matching record, or -1 if no record is found
*/
int
findRecord(struct question records[MAX_RECORDS],
           int nCount,
           char* pQText,
           char* pAnswer)
{
	/* Initializes the variable to -1 */
	int nRecordInd = -1;
	int nIndex;

	/* Loops through the records and search for a match */
	for (nIndex = 0; nIndex < nCount; nIndex++)
	{
		if (strcmp(records[nIndex].sQText, pQText) == 0 &&
		    strcmp(records[nIndex].sChoices[records[nIndex].nCorrAns - 1], pAnswer) == 0)
		{

			/* Stores the index of the matching record */
			nRecordInd = nIndex;
		}
	}

	/* Returns the index of the matching record, or -1 if no record is found */
	return nRecordInd;
}

/* This function returns the last question number for a specified topic from the array of question records
   @param records[MAX_RECORDS] - array of question records
   @param nCount - number of records
   @param topic - the topic for which the last question number is to be found
   @return the last question number found for the specified topic
*/
int
getLastQNum(struct question records[MAX_RECORDS],
            int nCount,
            char* pTopic)
{
	int nLastQNum = 0;
	int nIndex;

	/* Loops through the records and search for a match */
	for (nIndex = 0; nIndex < nCount; nIndex++)
	{

		/* Checks if the record's topic matches the topic we're looking for */
		if (strcmp(records[nIndex].sTopic, pTopic) == 0)
		{
			/* Checks if the record's question number is greater than
			   the last question number found */
			if (records[nIndex].nQNum > nLastQNum)
			{
				/* Updates the last question number to the question number
				   of the current record */
				nLastQNum = records[nIndex].nQNum;
			}
		}
	}

	/* Returns the last question number found for the specified topic */
	return nLastQNum;
}


/* This function adds a question record to the structure of questions
   in the program
   @param question records[MAX_RECORDS] - question records
   @param nCount - number of records
   @return the number of records
*/

int
addRecord(struct question records[MAX_RECORDS],
          int nCount)
{
	/* Declares and initializes the necessary variables */
	str50 sTopic, sAnswer, sChoices[MAX_CHOICES];
	str200 sQText;
	int nCorrAns, nLastQNum, nRecordInd, nQNum, nChoiceInd;

	/* Gets the question and answer from the user */
	printf("\nEnter question: ");

	/* Removes the newline character from the input buffer */
	getchar();

	fgets(sQText, MAX_STR_LEN, stdin);
	removeNewLine(sQText);
	printf("Enter answer: ");
	fgets(sAnswer, MAX_STR_LEN, stdin);
	removeNewLine(sAnswer);

	/* Checks if the question-answer pair already exists */
	nRecordInd = findRecord(records, nCount, sQText, sAnswer);

	if (nRecordInd != -1)
	{
		printf("\nRecord already listed:\n");
		printf("Topic: %s\n", records[nRecordInd].sTopic);
		printf("Question: %s\n", records[nRecordInd].sQText);
		printf("Choices:\n");

		for (nChoiceInd = 0; nChoiceInd < MAX_CHOICES; nChoiceInd++)
		{
			printf("  %d. %s\n", nChoiceInd + 1, records[nRecordInd].sChoices[nChoiceInd]);
		}

		printf("Correct Answer: %d\n\n", records[nRecordInd].nCorrAns);
	}
	else
	{
		/* Gets the topic, choices, and correct answer from the user */
		printf("Enter topic: ");
		fgets(sTopic, MAX_STR_LEN, stdin);
		removeNewLine(sTopic);
		printf("Enter choice 1: ");
		fgets(sChoices[0], MAX_STR_LEN, stdin);
		removeNewLine(sChoices[0]);
		printf("Enter choice 2: ");
		fgets(sChoices[1], MAX_STR_LEN, stdin);
		removeNewLine(sChoices[1]);
		printf("Enter choice 3: ");
		fgets(sChoices[2], MAX_STR_LEN, stdin);
		removeNewLine(sChoices[2]);
		printf("Enter the correct choice number (1-3): ");
		scanf("%d", &nCorrAns);

		/* Gets the last question number of the given topic */
		nLastQNum = getLastQNum(records, nCount, sTopic);

		/* Assigns the next question number */
		nQNum = nLastQNum + 1;

		/* Adds the new record to the array */
		strcpy(records[nCount].sTopic, sTopic);
		strcpy(records[nCount].sQText, sQText);
		strcpy(records[nCount].sChoices[0], sChoices[0]);
		strcpy(records[nCount].sChoices[1], sChoices[1]);
		strcpy(records[nCount].sChoices[2], sChoices[2]);
		records[nCount].nCorrAns = nCorrAns;
		records[nCount].nQNum = nQNum;

		/* Increments the record count */
		nCount++;

		printf("\nRecord added successfully!\n\n");
	}

	/* Removes duplicate records */
	removeDuplicates(records, &nCount);

	/* Returns the number of records */
	return nCount;
}

/* This function removes the newline character from a given string, if it exists.
   The newline character is replaced with a null character ('\0').
   @param str - the string to remove the newline character from
*/
void
removeNewLine(char* pStr)
{
	/* Sets a pointer to the beginning of the string*/
	char* p = pStr;

	/* Iterates through each character in the string */
	while (*p != '\0')
	{

		/* If a newline character is found, replace it with a null terminator */
		if (*p == '\n')
		{
			*p = '\0';
		}
		p++;
	}
}

/* This function displays the unique topics of the questions in the records array.
   It checks if a topic is unique before displaying it. Topics are always the first string of each record in a file or in add record.
   @param question records[MAX_RECORDS] - question records
   @param nCount - the number of records in the records array
*/
void
displayTopics(struct question records[MAX_RECORDS],
              int nCount)
{
    int nIndex, nTopicInd, nFound, i;
    str50 arrTopics[MAX_RECORDS];

    /* Prints the topics of the questions in the question bank */
    printf("Topics:\n");
    for (nIndex = 0, nTopicInd = 0; nIndex < nCount; nIndex++)
    {
        nFound = 0;

        /* Checks if the topic of the current record is already in the array of topics */
        for (i = 0; i < nTopicInd; i++)
        {
            /* If the topic is already in the array, set nFound to 1 */
            if (strcmp(records[nIndex].sTopic, arrTopics[i]) == 0)
            {
                nFound = 1;
            }
        }

        /* If the topic is not in the array, print it and add it to the array */
        if (nFound == 0)
        {
            nTopicInd++;
            printf("%d. %s\n", nTopicInd, records[nIndex].sTopic);
            strcpy(arrTopics[nTopicInd-1], records[nIndex].sTopic);
        }
    }

    /* Print a message if no topics were found */
    if (nTopicInd == 0)
    {
        printf("No topics found\n");
    }

    printf("\n");
}

/* This function displays all the questions in the question bank
   under the specified topic
   @param records[MAX_RECORDS] - array of question records
   @param nCount - the number of question records in the array
   @param sTopic - topic to display questions for
   @param arrQstIndices - array to store the indices of questions under the specified topic
   @param nQstNum - pointer to an integer to store the number of questions under the specified topic
*/
void
displayQuestions(struct question records[MAX_RECORDS],
                 int nCount,
                 str50 sTopic,
                 int arrQstIndices[MAX_RECORDS],
                 int* pQstNum)
{
	int nIndex, i, nQstInd = 0;
	int nFound = 0;

	/* Iterates through each record in the records array */
	for (nIndex = 0; nIndex < nCount; nIndex++)
	{
		/* Checks if the topic of the current record matches the specified topic */
		if (strcmp(records[nIndex].sTopic, sTopic) == 0)
		{
			/* If the topic matches, add the index of the record to the array of indices */
			arrQstIndices[nQstInd] = nIndex;
			nFound = 1;
			nQstInd++;
		}
	}

	/* If the topic is found, display the questions */
	if (nFound == 1)
	{
		printf("\nQuestions:\n");
		for (i = 0; i < nQstInd; i++)
		{
			printf("  %d. %s\n", i + 1, records[arrQstIndices[i]].sQText);
		}
		printf("\n");
		*pQstNum = nQstInd;
	}
	else
	{
		printf("\nNo questions found for topic %s\n\n", sTopic);
	}
}

/* This function displays details of a question record in the question bank.
   @param record - the question record to display
*/
void
displayQuestion(struct question record)
{
	int nIndex;

	/* Displays the question details */
	printf("\nQuestion Details:\n");
	printf("  Topic: %s \n", record.sTopic);
	printf("  Question: %s \n", record.sQText);
	printf("  Choices: \n");

	/* Iterates over the question choices and prints them */
	for (nIndex = 0; nIndex < MAX_CHOICES; nIndex++)
	{
		printf("    %d. %s \n", nIndex + 1, record.sChoices[nIndex]);
	}

	printf("  Correct Answer: %d \n", record.nCorrAns);
	printf("  Question Number: %d \n", record.nQNum);
	printf("\n");
}

/* This function validates if a given answer is one of the valid choices for a given question.
   @param record - the question record to validate the answer for
   @param newAnswer - the new answer to validate
   @return 1 if the answer is valid, 0 otherwise
*/
int
validateAnswer(struct question record,
               str50 sNewAns)
{
	int nIndex;
	int nFoundIndex = -1;

	/* Iterates over the question choices and check if the new answer is valid */
	for (nIndex = 0; nIndex < MAX_CHOICES; nIndex++)
	{
		if (strcmp(record.sChoices[nIndex], sNewAns) == 0)
		{
			/* The answer is valid */
			nFoundIndex = nIndex;
		}
	}

	/* Returns the index of the found choice (or -1 if not found) */
	return nFoundIndex;
}

// NEEDS CHECKING
/* This function edits the chosen question record of a chosen topic.
   @param question records[MAX_RECORDS] - question records
   @param nCount - number of records
*/
void
editRecord(struct question records[MAX_RECORDS],
		   int nCount)
{
    int nTopicInd, nQstInd, nConfirm, nChoice, nIndex;
    int arrTopicIndices[MAX_RECORDS];
    int nQstIndices[MAX_RECORDS];
    str50 sTopic, sNewTopic, sNewQText, sNewChoice, sNewAns;
    int nNewAns;

    /* Displays available topics and ask for the topic index to edit */
    displayTopics(records, nCount);

    printf("Enter topic index: ");
    scanf("%d", &nTopicInd);

    /* Gets the selected topic and remove newline character */
    strcpy(sTopic, records[arrTopicIndices[nTopicInd - 1]].sTopic);

    removeNewLine(sTopic);

    /* Displays questions under the selected topic and ask for the question index to edit */
    displayQuestions(records, nCount, sTopic, nQstIndices, &nQstInd);
    printf("Enter question index: ");
    scanf("%d", &nQstInd);

    /* Displays the question details */
    displayQuestion(records[nQstIndices[nQstInd - 1]]);

    /* Asks for the field to edit */
    printf("What field do you want to edit?\n");
    printf("  1. Topic\n");
    printf("  2. Question\n");
    printf("  3. Choices\n");
    printf("  4. Answer\n");
    printf("Enter choice: ");
    scanf("%d", &nChoice);

    /* Edits the chosen field */
    switch (nChoice)
    {
    	case 1:
            /* Edits the topic */
            printf("Enter new topic: ");
            getchar();
            fgets(sNewTopic, sizeof(sNewTopic), stdin);
            removeNewLine(sNewTopic);
            strcpy(records[nQstIndices[nQstInd - 1]].sTopic, sNewTopic);
            break;
        case 2:
            /* Edits the question */
            printf("Enter new question: ");
            getchar();
            fgets(sNewQText, sizeof(sNewQText), stdin);
            removeNewLine(sNewQText);
            strcpy(records[nQstIndices[nQstInd - 1]].sQText, sNewQText);
            break;
        case 3:
            /* Edits a single choice */
            printf("Enter choice index to edit (1-3): ");
            scanf("%d", &nIndex);
            if (nIndex >= 1 && nIndex <= MAX_CHOICES)
            {
                printf("Enter new choice %d: ", nIndex);
                scanf("%s", sNewChoice);
                strcpy(records[nQstIndices[nQstInd - 1]].sChoices[nIndex - 1], sNewChoice);
            }
            else
            {
                printf("Invalid choice index!\n");
            }
            break;
        case 4:
            /* Edits the answer */
            printf("Enter new answer: ");
            getchar();
            fgets(sNewAns, sizeof(sNewAns), stdin);
            removeNewLine(sNewAns);
            nNewAns = validateAnswer(records[nQstIndices[nQstInd - 1]], sNewAns);
            if (nNewAns != -1)
            {
                records[nQstIndices[nQstInd - 1]].nCorrAns = nNewAns + 1;
            }
            else
            {
                printf("Invalid answer!\n");
            }
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}

/* This function deletes the chosen question record of a chosen topic
   @param question records[MAX_RECORDS] - question records
   @param nCount - number of records
*/
int
deleteRecord(struct question records[MAX_RECORDS],
             int nCount)
{
    int nTopicInd, nQstInd, nConfirm, nChoice, nIndex;
    int arrTopicIndices[MAX_RECORDS];
    int nQstIndices[MAX_RECORDS];
    str50 sTopic;

    do
	{
        // Displays available topics and ask for the topic index to delete
        //displayTopics(records, nCount, sTopic, &nTopicInd, arrTopicIndices);
		displayTopics(records, nCount);
        printf("Enter topic index: ");
        scanf("%d", &nTopicInd);

        // Gets the selected topic and remove newline character
        strcpy(sTopic, records[nTopicInd - 1].sTopic);
        removeNewLine(sTopic);

        // Displays questions under the selected topic and ask for the question index to delete
        displayQuestions(records, nCount, sTopic, nQstIndices, &nQstInd);
        printf("Enter question index: ");
        scanf("%d", &nQstInd);

        // Confirms if the admin wants to delete the selected record
        printf("Are you sure you want to delete this record? (1-Yes, 2-No): ");
        scanf("%d", &nConfirm);

        switch (nConfirm)
		{
            case 1:
                /* Shifts the records after the deleted record to the left */
                for (nIndex = nQstIndices[nQstInd - 1]; nIndex < nCount - 1; nIndex++)
				{
                    records[nIndex] = records[nIndex + 1];
                }

                /* Decrements the number of records */
                nCount--;

                /* Displays the remaining records */
                //displayTopics(records, nCount, sTopic, &nTopicInd,arrTopicIndices);
				displayTopics(records, nCount);
                displayQuestions(records, nCount, sTopic, nQstIndices, &nQstInd);
                printf("Record deleted successfully\n\n");

                /* Asks if the admin wants to delete another record or go back to the main menu */
                printf("Do you want to delete another record? (1-Yes, 2-No): ");
                scanf("%d", &nChoice);
                break;

            case 2:
                /* Asks if the admin wants to delete another record or go back to the main menu */
                printf("Do you want to delete another record? (1-Yes, 2-No): ");
                scanf("%d", &nChoice);
                break;

            default:
                printf("Invalid choice\n");

                /* Asks if the admin wants to delete another record or go back to the main menu */
                printf("Do you want to delete another record? (1-Yes, 2-No): ");
                scanf("%d", &nChoice);
                break;
        }

    } while (nChoice == 1);

	/* Returns the number of records */
    return nCount;
}

/* This function reads all questions to the end of a file from a file and stores them in a struct array.
   @param sFileName - the name of the file to read questions from
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nMaxQst - the maximum number of questions to read from the file
   @return the number of questions read from the file, or -1 if an error occurs
*/
int
readData(char* sFileName,
         struct question records[MAX_RECORDS],
         int nMaxQst)
{
	FILE *fptr;
	int nRecordInd = 0;
	int nChoiceInd, nQNum;
	str50 sTopic, sCorrAns;
	str50 sChoices[MAX_CHOICES];
	str200 sQText;

	/* Appends ".txt" extension to the filename */
	strcat(sFileName, ".txt");

	/* Opens file for reading */
	fptr = fopen(sFileName, "r");
	if (fptr == NULL)
	{
		printf("Failed to open file.\n");
	}
	else
	{
		/* Reads question records from file in specified format */
		while (nRecordInd < nMaxQst && !feof(fptr))
		{
			/* Reads topic */
			fgets(sTopic, MAX_STR_LEN, fptr);
			removeNewLine(sTopic);

			/* Reads question number */
			fscanf(fptr, "%d", &nQNum);
			fgetc(fptr);

			/* Reads question */
			fgets(sQText, MAX_QTEXT_LEN, fptr);
			removeNewLine(sQText);

			/* Reads choices */
			for (nChoiceInd = 0; nChoiceInd < 3; nChoiceInd++)
			{
				fgets(sChoices[nChoiceInd], MAX_STR_LEN, fptr);
				removeNewLine(sChoices[nChoiceInd]);
			}

			/* Reads correct answer in string then finds the choice number equivalent */
			fgets(sCorrAns, MAX_STR_LEN, fptr);
			removeNewLine(sCorrAns);
			for (nChoiceInd = 0; nChoiceInd < 3; nChoiceInd++)
			{
				if (strcmp(sCorrAns, sChoices[nChoiceInd]) == 0)
				{
					records[nRecordInd].nCorrAns = nChoiceInd + 1;
				}
			}

			/* Save the record to the struct */
			strcpy(records[nRecordInd].sTopic, sTopic);
			records[nRecordInd].nQNum = nQNum;
			strcpy(records[nRecordInd].sQText, sQText);
			for (nChoiceInd = 0; nChoiceInd < 3; nChoiceInd++)
			{
				strcpy(records[nRecordInd].sChoices[nChoiceInd], sChoices[nChoiceInd]);
			}

			nRecordInd++;
			/* Read the new line separating the previous record from the next one */
			fgetc(fptr);
		}

		/* Closes file */
		fclose(fptr);
	}

	/* Returns number of records read */
	return nRecordInd;
}

/* This function writes the question records to a file in the specified format.
   @param sFileName - the name of the file to read questions from
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nQCount - the number of question records to write
*/
void
writeData(str30 sFileName,
          struct question records[MAX_RECORDS],
          int nQCount)
{
	FILE *fptr;
	int nRecordInd, nChoiceInd;

	/* Appends ".txt" extension to the filename */
	strcat(sFileName, ".txt");

	/* Opens file for writing */
	fptr = fopen(sFileName, "w");
	if (fptr == NULL)
	{
		printf("Failed to open file.\n");
	}
	else
	{
		/* Writes question records to file in specified format */
		for (nRecordInd = 0; nRecordInd < nQCount; nRecordInd++)
		{
			fprintf(fptr, "%s\n%d\n%s\n", records[nRecordInd].sTopic,
			        records[nRecordInd].nQNum,
			        records[nRecordInd].sQText);

			/* Writes answer choices to file */
			for (nChoiceInd = 0; nChoiceInd < MAX_CHOICES; nChoiceInd++)
			{
				fprintf(fptr, "%s\n", records[nRecordInd].sChoices[nChoiceInd]);
			}

			/* Writes correct answer as a string */
			fprintf(fptr, "%s\n\n",
			        records[nRecordInd].sChoices[records[nRecordInd].nCorrAns - 1]);
		}

		/* Closes file */
		fclose(fptr);
	}
}

/* This function imports question records from a file given the filename. Should print if the file was successfully imported.
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nMaxQst - the maximum number of questions to read from the file
   @return the number of questions imported from the file, or -1 if an error occurs
*/
int
importData(struct question records[MAX_RECORDS],
           int nMaxQst)
{
	str30 sFileName;
	int nQCount;

	/* Removes new line entered */
	getchar();

	/* Prompts the user to enter the filename */
	printf("\nEnter filename (Do not include the file extension, e.g. .txt): ");
	fgets(sFileName, sizeof(sFileName), stdin);

	/* Removes the newline character from the filename */
	removeNewLine(sFileName);

	/* Reads data from file */
	nQCount = readData(sFileName, records, nMaxQst);

	/* Removes duplicate records */
	removeDuplicates(records, &nQCount);

	/* Checks if data was successfully imported */
	if (nQCount == -1)
	{
		printf("Failed to import data.\n\n");
	}
	else
	{
		printf("Successfully imported data to %s.\n\n", sFileName);
	}

	/* Returns number of records read */
	return nQCount;
}

/* This function exports the question records to a text file
   with the specified filename. The data in this exported file
   can be used in the import option.
   @param records[MAX_RECORDS] - an array of structs to be exported
   @param nQCount - the number of question records in the array
   @return the comparison result
*/
// int
// compareTopics(const void *a, const void *b)
// {
// 	int nResult;

// 	/* Compares the topics of the questions */
// 	struct question *qa = (struct question *)a;
// 	struct question *qb = (struct question *)b;
// 	nResult = strcmp(qa->sTopic, qb->sTopic);

// 	/* Returns the comparison result */
// 	return nResult;
// }

/* This function displays the topics of the questions in the question bank
   to be used in the game
   @param records[MAX_RECORDS] - an array of structs to be exported
   @param nQCount - the number of question records in the array
   @param sTopics[MAX_TOPICS] - an array of strings to store the topics in
   @param nTopicCount - the number of topics in the array
*/
void
displayGameTopics(struct question records[MAX_RECORDS],
				  int nQCount,
				  str50 sTopics[MAX_TOPICS],
				  int *nTopicCount)
{
    int nIndex, i, nFound;

    /* Prints the topics of the questions in the question bank */
    printf("Topics:\n");
    for (nIndex = 0; nIndex < nQCount; nIndex++)
    {
        nFound = 0;

        /* Checks if the topic of the current record is already in the array of topics */
        for (i = 0; i < *nTopicCount; i++)
        {
            /* If the topic is already in the array, set nFound to 1 */
            if (strcmp(records[nIndex].sTopic, sTopics[i]) == 0)
            {
                nFound = 1;
            }
        }

        /* If the topic is not in the array, print it and add it to the array */
        if (nFound == 0)
        {
            printf("%d. %s\n", *nTopicCount + 1, records[nIndex].sTopic);
            strcpy(sTopics[*nTopicCount], records[nIndex].sTopic);
            (*nTopicCount)++;
        }
    }

    /* Print a message if no topics were found */
    if (*nTopicCount == 0)
    {
        printf("No topics found\n");
    }

    printf("\n");
}

/* This function exports the question records to a text file
   with the specified filename. The data in this exported file
   can be used in the import option.
   @param records[MAX_RECORDS] - an array of structs to be exported
   @param nQCount - the number of question records in the array
*/
void
exportData(struct question records[MAX_RECORDS],
		   int nQCount)
{
	str30 sFileName;

	/* Removes new line entered */
	getchar();

	/* Prompts the user to enter the filename */
	printf("\nEnter filename (Do not include the file extension, e.g. .txt): ");
	fgets(sFileName, sizeof(sFileName), stdin);

	/* Removes the newline character from the filename */
	removeNewLine(sFileName);

	/* Sorts the records by topic */


	/* Writes data to file */
	writeData(sFileName, records, nQCount);

	/* Checks if data was successfully exported */
	if (nQCount == -1)
	{
		printf("Failed to export data.\n\n");
	}
	else
	{
		printf("Successfully exported data to %s.\n\n", sFileName);
	}
}

/* This function prompts the play game menu and calls the appropriate functions
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nQCount - the number of question records in the array
   @param scores[MAX_SCORES] - an array of structs to store the scores in
   @param pScoreCount - the number of scores in the array
*/
void
playGame(struct question records[MAX_RECORDS],
         int nQCount,
         struct score scores[MAX_SCORES],
         int *pScoreCount)
{
    str30 sPlayerName;
	int nQInd, nTopicInd, nRand, nAnswer, nQuestionsFound, i;
    int nChoice = -1;
    int nScore = 0;
    int nTopicCount = 0;
	int nFoundMatch = 0;
    int arrTopicIndices[MAX_RECORDS];
    str50 sTopics[MAX_TOPICS];

    /* Removes new line entered */
    getchar();

    /* Prompts the user to enter their name */
    printf("\nEnter your name: ");
    fgets(sPlayerName, sizeof(sPlayerName), stdin);

    /* Removes the newline character from the name */
    removeNewLine(sPlayerName);

    /* Displays the menu */
    printf("\nWelcome %s! Let's play!\n", sPlayerName);

    /* Displays the available topics */
    displayGameTopics(records, nQCount, sTopics, &nTopicCount);


    /* Loop until the user chooses to quit */
    while (nChoice != 0)
    {
        /* Prompts the user to choose a topic */
        printf("Enter a topic (0 to quit): ");
        scanf("%d", &nChoice);

        /* If the user enters an invalid choice, display an error message and continue */
        if (nChoice < 0 || nChoice > nTopicCount)
        {
            printf("Invalid choice\n");
        }

        /* Finds the questions with the chosen topic */
        nQuestionsFound = 0;
        for (nQInd = 0; nQInd < nQCount; nQInd++)
        {
            if (strcmp(records[nQInd].sTopic, sTopics[nChoice - 1]) == 0)
            {
                nQuestionsFound++;
            }
        }

        /* If there are no questions with the chosen topic, display an error message and continue */
        if (nQuestionsFound == 0)
		{
            printf("No questions found for this topic\n");
        }

		/* If there are questions with the chosen topic, play the game */
		else
		{
			/* Chooses a random question with the chosen topic */
        	srand(time(NULL));

        	nRand = rand() % nQuestionsFound;

        	for (nQInd = 0, nTopicInd = 0; nQInd < nQCount; nQInd++)
        	{
            	if (strcmp(records[nQInd].sTopic, sTopics[nChoice - 1]) == 0)
             	{
                	if (nTopicInd == nRand)
                	{
                    	/* Displays the question */
                    	printf("\n%s\n", records[nQInd].sQText);

                    	/* Displays the choices */
                    	printf("1. %s\n", records[nQInd].sChoices[0]);
                    	printf("2. %s\n", records[nQInd].sChoices[1]);
                    	printf("3. %s\n", records[nQInd].sChoices[2]);

                    	/* Prompts the user to enter an answer */
                    	printf("Answer: ");
                    	scanf("%d", &nAnswer);

                    	/* Checks if the answer is correct */
                    	if (nAnswer == records[nQInd].nCorrAns)
                    	{
                        	printf("Correct!\n");
                        	nScore++;
                    	}
                    	else
                    	{
                        	printf("Sorry, the correct answer is %d\n", records[nQInd].nCorrAns);
                    	}

                    	/* Displays the current score */
                    	printf("Score: %d\n", nScore);
               		}
                	nTopicInd++;
            	}
        	}
		}
    }

    /* Checks if the player's score is already in the scores array */
	for (i = 0; i < *pScoreCount; i++)
	{
    	if (strcmp(scores[i].sName, sPlayerName) == 0)
		{
			/* Adds the player's score to the existing score */
       		scores[i].nScore += nScore;

			/* Displays the player's new score */
			printf("\n%s's new score: %d\n\n", sPlayerName, scores[i].nScore);

			/* Sets the foundMatch flag to 1 */
       		nFoundMatch = 1;
   		}
	}
	
	/* Adds the player's score to the scores array if no match found */
	if (!nFoundMatch)
	{
    	strcpy(scores[*pScoreCount].sName, sPlayerName);
    	scores[*pScoreCount].nScore = nScore;
    	(*pScoreCount)++;

		/* Displays the player's score */
		printf("\n%s's score: %d\n\n", sPlayerName, nScore);
	}
}

/* This function displays the scores of the players in descending order.
   @param scores[MAX_SCORES] - an array of structs to store the scores in
   @param nTotalScores - the number of scores in the array
*/
void
viewScores(struct score scores[MAX_SCORES],
           int nTotalScores)
{
	int i, j;
	struct score temp;

	if (nTotalScores == 0)
	{
		printf("\nNo scores to display.\n\n");
	}
	else
	{
		/* Sorts scores in descending order */
		for (i = 0; i < nTotalScores - 1; i++)
		{
			for (j = i + 1; j < nTotalScores; j++)
			{
				if (scores[i].nScore < scores[j].nScore)
				{
					/* Swaps scores */
					temp = scores[i];
					scores[i] = scores[j];
					scores[j] = temp;
				}
			}
		}

		/* Displays scores in a table format */
		printf("\n");
		printf("Rank\tName\t\tScore\n");
		for (i = 0; i < nTotalScores; i++)
		{
			printf("%d\t%-15s\t%d\n", i+1, scores[i].sName, scores[i].nScore);
		}
		printf("\n");
	}
}

/* This function loads the scores of upon opening play game in the play menu.
   @param scores[MAX_SCORES] - an array of structs to store the scores in
   @return the number of scores loaded from the file, or -1 if an error occurs
*/
int
loadScores(struct score scores[MAX_SCORES])
{
	FILE *fptr;
	str50 sName;
	int nScore;
	int nReadInd = 0;

	/* Opens file for reading */
	fptr = fopen("score.txt", "r");

	/* Checks if the file exists */
	if (fptr == NULL)
	{
		printf("No scores found.\n");
	}

	/* Reads the name and score from the file */
	while (fgets(sName, MAX_STR_LEN, fptr) != NULL && nReadInd < MAX_SCORES)
	{
		/* Removes the newline character from the name */
		removeNewLine(sName);

		/* Reads the score */
		if (fscanf(fptr, "%d\n", &nScore) == 1)
		{
			/* Stores the name and score in the scores array */
			strcpy(scores[nReadInd].sName, sName);
			scores[nReadInd].sName[MAX_STR_LEN - 1] = '\0';
			scores[nReadInd].nScore = nScore;
			nReadInd++;
		}
	}

	fclose(fptr);

	/* Returns the number of scores read */
	return nReadInd;
}

/* This function saves the scores of the player upon exiting play game in the play menu.
    @param scores[MAX_SCORES] - an array of structs to store the scores in
    @param nCount - the number of scores in the array
*/
void
saveScores(struct score scores[MAX_SCORES],
           int nTotalScores)
{
	FILE *fptr;
	int nWriteInd;

	/* Opens file for writing */
	fptr = fopen("score.txt", "w");

	/* Checks if the file exists */
	if (fptr == NULL)
	{
		printf("Error writing scores.\n");
	}

	/* Writes the name and score to the file */
	for(nWriteInd = 0; nWriteInd < nTotalScores; nWriteInd++)
	{
		fprintf(fptr, "%s\n%d\n\n", scores[nWriteInd].sName, scores[nWriteInd].nScore);
	}

	fclose(fptr);
}

/* This function displays the main menu of the play mode of the program.
   The menu should have the following options:
   1. Play
   2. View Scores
   3. Exit
   The user should be able to choose from the options and the program should respond accordingly.
   The program should only exit when the user chooses the exit option.
*/
void
displayPlayMenu(struct question records[MAX_RECORDS],
                int nTotalRecords)
{
	int nChoice = 0;
	int nTotalScores = 0;

	/* Array of structs to store the scores */
	struct score scores[MAX_SCORES];

	/* Loads the scores from the file */
	nTotalScores = loadScores(scores);

	/* Displays the play menu */
	while (nChoice != 3)
	{
		printf("Choose an option:\n");
		printf("1. Play\n");
		printf("2. View Scores\n");
		printf("3. Exit\n");
		scanf("%d", &nChoice);

		switch(nChoice)
		{
			/* Selects play game option */
			case 1:
				playGame(records, nTotalRecords, scores, &nTotalScores);
				break;
				/* Selects view scores option */
			case 2:
				viewScores(scores, nTotalScores);
				break;
				/* Selects exit game option */
			case 3:
				saveScores(scores, nTotalScores);
				break;
				/* Displays error message if invalid choice is entered */
			default:
				printf("Invalid choice. Try again.\n");
				break;
		}
	}
}



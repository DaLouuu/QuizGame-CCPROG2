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
    printf("%c%*s%*s%c\n", 186, 36, "Dana Louise A. Guillarte", 12, " ", 186);
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
   @returns choice if the choice is in the range [min, max], else 0
   Precondition: min and max must be valid integers
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
   @returns number of records in the array
   Precondition: sAdminPass must be a valid array
*/
int
login(str20 sAdminPass,
      int nRecords,
      struct question records[MAX_RECORDS])
{
    char cInput;
    char sPassword[MAX_PASS_LEN + 1];
    int nCount = 0;
    int nChoice = 1;

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
        system("cls");
        
        printf("Incorrect password.\n");
        printf("Press 1 to try again, or any other key to go back to main menu: ");
        scanf("%d", &nChoice);

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

        /* Pauses the program and clears the screen */
        system("pause");
        system("cls");

        /* Displays user-friendly interface for managing data */
        nRecords = manageData(nRecords, records);
    }
    else
    {
        printf("Going back to main menu.\n\n");

        /* Pauses the program and clears the screen */
        system("pause");
        system("cls");
    }

    /* Returns the number of records in the array */
    return nRecords;
}


/* This function displays the user friendly Manage Data UI and manages
   the question records of the game
   @param nRecords - number of question records
   @param records[MAX_RECORDS] - array of question records
   Precondition: nRecords must be less than MAX_RECORDS
*/
int
manageData(int nRecords,
           struct question records[MAX_RECORDS])
{
    int nChoice;

    do
    {
        printf("MAIN MENU\n");
        printf("--------------------\n\n");
        printf("1. Add Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("4. Import Data\n");
        printf("5. Export Data\n");
        printf("6. Go Back to Main Menu\n");

        printf("Enter choice: ");
        scanf("%d", &nChoice);

        switch (nChoice)
        {

            /* Adds a new record */
            case 1:
                system("cls");

                printf("Add Record\n");
                printf("--------------------\n\n");

                /* Increases the number of records by 1 after adding the new record */
                nRecords = addRecord(records, nRecords);

                /* Pauses the program and clears the screen */
                system("pause");
                system("cls");

                break;

            /* Edits an existing record */
            case 2:
                system("cls");

                printf("Edit Record\n");
                printf("--------------------\n\n");

                /* Checks if there are records to edit */
                if(nRecords > 0)
                {
                    /* Calls the editRecord function to edit a record */
                    editRecord(records, nRecords);

                    /* Pauses the program and clears the screen */
                    system("pause");
                    system("cls");
                }
                else
                {
                    /* Tells the user that there are no records to edit */
                    printf("There are no records to edit.\n\n");

                    /* Pauses the program and clears the screen */
                    system("pause");
                    system("cls");
                }
                break;

            /* Deletes an existing record */
            case 3:
                system("cls");

                printf("Delete Record\n");
                printf("--------------------\n\n");

                /* Checks if there are records to edit */
                if(nRecords > 0)
                {
                    /* Calls the deleteRecord function to edit a record */
                    nRecords = deleteRecord(records, nRecords);
                }
                else
                {
                    /* Tells the user that there are no records to delete */
                    printf("There are no records to delete.\n\n");

                    /* Pauses the program and clears the screen */
                    system("pause");
                    system("cls");
                }
                break;

            /* Imports data from a file */
            case 4:
                system("cls");

                printf("Import Data\n");
                printf("--------------------\n\n");

                /* Calls the importData function to import records from a file */
                nRecords = importData(records, MAX_RECORDS, nRecords);

                /* Pauses the program and clears the screen */
                system("pause");
                system("cls");

                break;

            /* Exports data to a file */
            case 5:
                system("cls");

                printf("Export Data\n");
                printf("--------------------\n\n");

                if (nRecords > 0)
                {
                    /* Calls the exportData function to export records to a file */
                    exportData(records, nRecords);

                    /* Pauses the program and clears the screen */
                    system("pause");
                    system("cls");
                }
                else
                {
                    /* Tells the user that export can't be done if there are no
                       records */
                    printf("I'm sorry, but we cannot export any data");
                    printf(" if there are no records. Try again later.\n\n");

                    /* Pauses the program and clears the screen */
                    system("pause");
                    system("cls");
                }
                break;

            /* Goes back to the main menu */
            case 6:
                system("cls");

                printf("Going back to main menu.\n\n");

                /* Pauses the program and clears the screen */
                system("pause");
                system("cls");
                break;

            /* Invalid choice */
            default:
                system("cls");

                printf("Invalid choice. Try again.\n\n");

                /* Pauses the program and clears the screen */
                system("pause");
                system("cls");
        }
    } while (nChoice != 6);

    /* Returns the number of records */
    return nRecords;
}

/* This function finds a record with the given question text and answer
   @param records[MAX_RECORDS] - array of question records
   @param nCount - number of records
   @param pQText - the question text to search for
   @param pAnswer - the answer to search for
   @returns the index of the matching record, or -1 if no record is found
   Preconditions: records[MAX_RECORDS] is an array of question records
                  nCount is the number of records
                  pQText is the question text to search for
                  pAnswer is the answer to search for
*/
int
findRecord(struct question records[MAX_RECORDS],
		   int nCount,
		   char* pQText,
		   char* pAnswer)
{
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
   @returns the last question number found for the specified topic
   Precondition: The topic must be a valid topic
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
   @returns the number of records
   Preconditions: nCount < MAX_RECORDS
                  User is sure that he/she wants to add a new record
*/
int
addRecord(struct question records[MAX_RECORDS],
		  int nCount)
{
    str50 sTopic;
    str50 sAnswer;
    str50 sChoices[MAX_CHOICES];
    str200 sQText;
    int nCorrAns;
    int nLastQNum;
    int nRecordInd;
    int nQNum;
    int nChoiceInd;
    int nChoiceDup;

    /* Gets the question and answer from the user */
    printf("\nEnter question: ");
    getchar();
    fgets(sQText, sizeof(sQText), stdin);
    removeNewLine(sQText);
    printf("Enter answer: ");
    fgets(sAnswer, sizeof(sAnswer), stdin);
    removeNewLine(sAnswer);

    /* Checks if the question-answer pair already exists */
    nRecordInd = findRecord(records, nCount, sQText, sAnswer);

    if (nRecordInd >= 0)
    {
        system("cls");

        /* Prints the record if it already exists */
        printf("\nRecord Already Listed\n");
        printf("---------------------\n");
        printf("Topic: %s\n", records[nRecordInd].sTopic);
        printf("Question: %s\n", records[nRecordInd].sQText);
        printf("Choices:\n");

        for (nChoiceInd = 0; nChoiceInd < MAX_CHOICES; nChoiceInd++)
        {
            printf("  %d. %s\n", nChoiceInd + 1, records[nRecordInd].sChoices[nChoiceInd]);
        }

        printf("Correct Answer: %d\n\n", records[nRecordInd].nCorrAns);

        /* Pauses the program and clears the screen */
        system("pause");
        system("cls");
    }
    else
    {
        nChoiceDup = 0;

        /* Gets the topic from the user */
            printf("Enter topic: ");
            fgets(sTopic, MAX_STR_LEN, stdin);
            removeNewLine(sTopic);

        /* Gets the choices from the user */
        do
        {
            printf("Enter choice 1: ");
            fgets(sChoices[0], MAX_STR_LEN, stdin);
            removeNewLine(sChoices[0]);
            printf("Enter choice 2: ");
            fgets(sChoices[1], MAX_STR_LEN, stdin);
            removeNewLine(sChoices[1]);
            printf("Enter choice 3: ");
            fgets(sChoices[2], MAX_STR_LEN, stdin);
            removeNewLine(sChoices[2]);

            /* Checks for duplicates in the choices */
            if (strcmp(sChoices[0], sChoices[1]) == 0 ||
                strcmp(sChoices[0], sChoices[2]) == 0 ||
                strcmp(sChoices[1], sChoices[2]) == 0)
            {
                printf("\n\nChoices cannot be the same or have duplicates. Please try again.\n\n");
                nChoiceDup = 1;
            } 
            else
            {
                nChoiceDup = 0;
            }
        } while (nChoiceDup);

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
    }

    printf("\n");

    /* Returns the new record count */
    return nCount;
}

/* This function removes the newline character from a given string, if it exists.
   The newline character is replaced with a null character ('\0').
   @param str - the string to remove the newline character from
   Precondition: str is a valid string
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
   It checks if a topic is unique before displaying it.
   @param records[MAX_RECORDS] - question records
   @param nCount - the number of records in the records array
   @param sTopics[MAX_TOPICS] - array to store unique topics
   @param nTopicCount - pointer to store the number of unique topics found
   @param arrTopicIndices[MAX_RECORDS] - array to store the indices of the unique topics in the records array
   Preconditions: nCount < MAX_RECORDS
                  nTopicCount < MAX_TOPICS
*/
void
displayTopics(struct question records[MAX_RECORDS],
              int nQCount,
              str50 sTopics[MAX_TOPICS],
              int *nTopicCount,
              int arrTopicIndices[MAX_RECORDS])
{
    int i;
    int j;
    int nFound;

    *nTopicCount = 0;

    /* Prints the topics of the questions in the question bank */
    printf("Topics:\n");
    for (i = 0; i < nQCount; i++)
    {
        nFound = 0;

        /* Checks if the topic of the current record is already in the array of topics */
        for (j = 0; j < *nTopicCount; j++)
        {
            /* If the topic is already in the array, set nFound to 1 */
            if (strcmp(records[i].sTopic, sTopics[j]) == 0)
            {
                nFound = 1;
            }
        }

        /* If the topic is not in the array, print it and add it to the array */
        if (nFound == 0)
        {
            printf("%d. %s\n", *nTopicCount + 1, records[i].sTopic);
            strcpy(sTopics[*nTopicCount], records[i].sTopic);
            arrTopicIndices[*nTopicCount] = i;
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

/* This function displays all the questions in the question bank
   under the specified topic
   @param records - array of question records
   @param nCount - the number of question records in the array
   @param sTopic - topic to display questions for
   @param arrQstIndices - array to store the indices of questions under the specified topic
   @param pQstNum - pointer to an integer to store the number of questions under the specified topic
   Preconditions: The topic must be in the records array
                  The arrQstIndices array must be large enough to store the indices of all the questions
                  under the specified topic
*/
void
displayQuestions(struct question records[MAX_RECORDS],
                 int nCount,
                 str50 sTopic,
                 int arrQstIndices[MAX_RECORDS],
                 int* pQstNum)
{
    int i;
    int nQstInd = 0;
    int nFound = 0;

    /* Iterates through each record in the records array */
    for (i = 0; i < nCount; i++)
    {
        /* Checks if the topic of the current record matches the specified topic */
        if (strcmp(records[i].sTopic, sTopic) == 0)
        {
            /* If the topic matches, add the index of the record to the array of indices */
            arrQstIndices[nQstInd] = i;
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
   Precondition: record is a valid question record
*/
void
displayQuestion(struct question record)
{
    int i;

    /* Displays the question details */
    printf("\nQuestion Details:\n");
    printf("  Topic: %s \n", record.sTopic);
    printf("  Question: %s \n", record.sQText);
    printf("  Choices: \n");
    for (i = 0; i < MAX_CHOICES; i++)
    {
        printf("    %d. %s \n", i + 1, record.sChoices[i]);
    }
    printf("  Correct Answer: %d \n", record.nCorrAns);
    printf("  Question Number: %d \n", record.nQNum);
    printf("\n");
}

/* This function validates if a given answer is one of the valid choices for a given question.
   @param record - the question record to validate the answer for
   @param newAnswer - the new answer to validate
   @returns 1 if the answer is valid, 0 otherwise
   Precondition: record is a valid question record
*/
int
validateAnswer(struct question record,
               str50 sNewAns)
{
    int i;
    int nFoundIndex = -1;

    /* Iterates over the question choices and check if the new answer is valid */
    for (i = 0; i < MAX_CHOICES; i++)
    {
        if (strcmp(record.sChoices[i], sNewAns) == 0)
        {
            /* The answer is valid */
            nFoundIndex = i;
        }
    }

    /* Returns the index of the found choice (or -1 if not found) */
    return nFoundIndex;
}


/* This function edits the chosen question record of a chosen topic.
   @param question records[MAX_RECORDS] - question records
   @param nCount - number of records
   Precondition: User is always prompted to enter a valid index
                 User is sure that they want to edit the record
*/
void
editRecord(struct question records[MAX_RECORDS],
           int nQCount)
{
    int nTopicInd;
    int nQstInd;
    int nChoice; 
    int nEditChoice;
    int nValidChoice = 0;
    int nNewAns;
    int i;
    int j;
    int nEditAgain = 1;
    int arrTopicIndices[MAX_RECORDS];
    int nQstIndices[MAX_RECORDS];
    str50 sTopics[MAX_TOPICS];
    str50 sNewTopic;
    str200 sNewQText;
    str50 sNewChoice;
    str50 sNewAns;
    str50 sSelectedTopic;
    struct question transferQst;

    while (nEditAgain)
    {

        /* Displays available topics and ask for the topic index to edit */
        displayTopics(records, nQCount, sTopics, &nTopicInd, arrTopicIndices);
        printf("Enter topic index: ");
        scanf("%d", &nTopicInd);

        /* Gets the selected topic and remove newline character */
        strcpy(sSelectedTopic, records[arrTopicIndices[nTopicInd - 1]].sTopic);
        removeNewLine(sSelectedTopic);

        system("cls");

        /* Displays questions under the selected topic and ask for the question index to edit */
        displayQuestions(records, nQCount, sSelectedTopic, nQstIndices, &nQstInd);
        printf("Enter question index: ");
        scanf("%d", &nQstInd);

        system("cls");

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
                system("cls");

                printf("Edit Topic\n");
                printf("---------\n");

                /* Edits the topic */
                printf("Enter new topic: ");
                getchar();
                fgets(sNewTopic, sizeof(sNewTopic), stdin);
                removeNewLine(sNewTopic);

                /* Find the question to transfer */
                transferQst = records[nQstIndices[nQstInd - 1]];

                /* Remove the question from the current topic's question list */
                for (i = 0; i < nQCount; i++)
                {
                    if (strcmp(records[i].sTopic, sSelectedTopic) == 0 && records[i].nQNum == transferQst.nQNum)
                    {
                        for (j = i; j < nQCount - 1; j++)
                        {
                            records[j] = records[j + 1];
                        }
                        nQCount--;
                    }
                }

                /* Add the question to the end of the new topic's question list */
                strcpy(transferQst.sTopic, sNewTopic);
                transferQst.nQNum = nQCount + 1;
                records[nQCount] = transferQst;
                nQCount++;

                break;
            case 2:
                system("cls");

                printf("Edit Question\n");
                printf("---------\n");

                /* Edits the question */
                printf("Enter new question: ");
                getchar();
                fgets(sNewQText, sizeof(sNewQText), stdin);
                removeNewLine(sNewQText);
                strcpy(records[nQstIndices[nQstInd - 1]].sQText, sNewQText);
                break;
            case 3:
                /* Edits a single choice */
                do 
                {

                    printf("Enter choice index to edit (1-3): ");
                    scanf("%d", &nEditChoice);
        
                    if (nEditChoice < 1 || nEditChoice > MAX_CHOICES)
                    {
                        printf("Invalid choice index!\n");
                    }
                    /* Checks if the new choice is a duplicate */
                    else
                    {
                        /* Prompts for the new choice */
                        do
                        {
                            printf("Enter new choice %d: ", nEditChoice);
                            scanf("%s", sNewChoice);

                            /* Check if the new choice is a duplicate */
                            if (strcmp(records[nQstIndices[nQstInd - 1]].sChoices[0], sNewChoice) == 0 ||
                                strcmp(records[nQstIndices[nQstInd - 1]].sChoices[1], sNewChoice) == 0 ||
                                strcmp(records[nQstIndices[nQstInd - 1]].sChoices[2], sNewChoice) == 0)
                            {
                                printf("Choice cannot be a duplicate. Please try again.\n");
                            }
                            else
                            {
                                strcpy(records[nQstIndices[nQstInd - 1]].sChoices[nEditChoice - 1], sNewChoice);
                                nValidChoice = 1;
                            }
                        } while (!nValidChoice);
                    }
                } while (nEditChoice < 1 || nEditChoice > MAX_CHOICES);
                break;
            case 4:
                system("cls");

                printf("Edit Answer\n");
                printf("---------\n");
                
                /* Removes new line character then edits the answer */
                getchar();

                /* Edits the answer and asks for a new answer if the answer is invalid */
                do 
                {
                    printf("Enter new answer: ");
                    fgets(sNewAns, sizeof(sNewAns), stdin);
                    removeNewLine(sNewAns);

                    /* Validates the new answer */
                    nNewAns = validateAnswer(records[nQstIndices[nQstInd - 1]], sNewAns);

                    if (nNewAns == -1) 
                    {
                        printf("Invalid answer!\n");
                    }
                } while (nNewAns == -1);

                records[nQstIndices[nQstInd - 1]].nCorrAns = nNewAns + 1;
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }

        /* Asks if the user wants to edit another record */
        printf("Do you want to edit another record? (1 - Yes, 0 - No): ");
        scanf("%d", &nEditAgain);
    }
    printf("\n");
}

/* This function deletes the chosen question record of a chosen topic
   @param question records[MAX_RECORDS] - question records
   @param nCount - number of records
   @returns number of records after deletion
   Precondition: User is always prompted to enter a valid index
*/
int
deleteRecord(struct question records[MAX_RECORDS],
             int nCount)
{
    int nTopicInd;
    int nQstInd;
    int nConfirm;
    int nChoice;
    int i;
    int arrTopicIndices[MAX_RECORDS];
    int nQstIndices[MAX_RECORDS];
    str50 sTopics[MAX_TOPICS];
    str50 sSelectedTopic;

    do
    {
        /* Displays topics and asks for the topic index to delete */
        displayTopics(records, nCount, sTopics, &nTopicInd, arrTopicIndices);
        printf("Enter topic index: ");
        scanf("%d", &nTopicInd);

        /* Gets the selected topic and removes the newline character */
        strcpy(sSelectedTopic, records[arrTopicIndices[nTopicInd - 1]].sTopic);
        removeNewLine(sSelectedTopic);

        /* Displays questions of the selected topic and asks for the question index to delete */
        displayQuestions(records, nCount, sSelectedTopic, nQstIndices, &nQstInd);
        printf("Enter question index: ");
        scanf("%d", &nQstInd);

        /* Confirms the deletion of the record */
        printf("Are you sure you want to delete this record? (1-Yes, 2-No): ");
        scanf("%d", &nConfirm);

        switch (nConfirm)
        {
            /* Deletes the record if the user confirms */
            case 1:
                /* Shifts the records to the left to fill the gap of the deleted record */
                for (i = nQstIndices[nQstInd - 1]; i < nCount - 1; i++)
                {
                    records[i] = records[i + 1];
                }

                /* Decrements the number of records */
                nCount--;

                system("cls");

                /* Displays the topics and questions after the deletion */
                displayTopics(records, nCount, sTopics, &nTopicInd, arrTopicIndices);
                displayQuestions(records, nCount, sSelectedTopic, nQstIndices, &nQstInd);

                /* Asks if the admin wants to delete another record or go back to the main menu */
                printf("Do you want to delete another record? (1-Yes, 2-No): ");
                scanf("%d", &nChoice);

                system("cls");

                break;

            /* Cancels delete procedure */
            case 2:
                system("cls");
                /* Asks if the admin wants to delete another record or go back to the main menu */
                printf("Do you want to delete another record? (1-Yes, 2-No): ");
                scanf("%d", &nChoice);

                system("cls");
                break;

            /* Displays invalid choice */
            default:
                system("cls");

                printf("Invalid choice\n\n");

                /* Asks if the admin wants to delete another record or go back to the main menu */
                printf("Do you want to delete another record? (1-Yes, 2-No): ");
                scanf("%d", &nChoice);

                system("cls");
                break;
        }

    } while (nChoice == 1);

    printf("\n");

    /* Returns the number of records after deletion */
    return nCount;
}

/* This function reads all questions to the end of a file from a file and stores them in a struct array.
   @param sFileName - the name of the file to read questions from
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nMaxQst - the maximum number of questions to read from the file
   @param nRecords - the number of records in the array
   @returns the number of questions read from the file, or -1 if an error occurs
   Precondition: The file must be in the correct format (.txt file)
*/
int
readData(char* sFileName,
         struct question records[MAX_RECORDS],
         int nMaxQst,
         int nRecords)
{
    FILE *fptr;
    int nChoiceInd;
    int nQNum;
    int nRecordInd = nRecords;
    str50 sTopic;
    str50 sChoices[MAX_CHOICES];
    str50 sCorrAns;
    str200 sQText;

    /* Appends ".txt" extension to the filename */
    strcat(sFileName, ".txt");

    /* Opens file for reading */
    fptr = fopen(sFileName, "r");
    if (fptr == NULL)
    {
        char sDataPath[MAX_FILE_LEN + 10];
        sprintf(sDataPath, "data/%s", sFileName);
        fptr = fopen(sDataPath, "r");
    }

    if (fptr == NULL)
    {
        printf("Failed to open file.\n");
        nRecords = -1;
    }
    else
    {
        /* Reads question records from file in specified format */
        while (nRecordInd < nMaxQst && fgets(sTopic, MAX_STR_LEN, fptr) != NULL)
        {
            /* Reads topic */
            removeNewLine(sTopic);
            if (strlen(sTopic) == 0)
            {
                continue;
            }

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

        nRecords = nRecordInd - nRecords;
    }

    /* Returns number of records read */
    return nRecords;
}

/* This function writes the question records to a file in the specified format
   sorted by topic
   @param sFileName - the name of the file to read questions from
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nQCount - the number of question records to write
   Precondition: The file must be in the correct format (.txt file)
*/
void
writeData(str30 sFileName,
          struct question records[MAX_RECORDS],
          int nQCount)
{
    FILE *fptr;
    int i;
    int j;
    int nRecordInd;
    int nChoiceInd;
    int nMinIndex;
    struct question temp;

    /* Appends ".txt" extension to the filename */
    strcat(sFileName, ".txt");

    /* Sorts records by topic using selection sort */
    for (i = 0; i < nQCount - 1; i++)
    {
        nMinIndex = i;
        for (j = i + 1; j < nQCount; j++)
        {
            if (strcmp(records[j].sTopic, records[nMinIndex].sTopic) < 0)
            {
                nMinIndex = j;
            }
        }
        if (nMinIndex != i)
        {
            temp = records[i];
            records[i] = records[nMinIndex];
            records[nMinIndex] = temp;
        }
    }

    /* Opens file for writing */
    fptr = fopen(sFileName, "w");
    if (fptr == NULL)
    {
        char sDataPath[MAX_FILE_LEN + 10];
        sprintf(sDataPath, "data/%s", sFileName);
        fptr = fopen(sDataPath, "w");
    }

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


/* This function imports question records from a file given the filename
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nMaxQst - the maximum number of questions to read from the file
   @param nRecords - the number of records in the array
   @returns the number of questions imported from the file, or -1 if an error occurs
   Precondition: The file must be in the correct format (.txt file)
*/
int
importData(struct question records[MAX_RECORDS],
           int nMaxQst,
           int nRecords)
{
    str30 sFileName;
    int nQCount = 0;

    /* Removes new line entered */
    getchar();

    /* Prompts the user to enter the filename */
    printf("\nEnter filename (Do not include the file extension, e.g. .txt): ");
    fgets(sFileName, sizeof(sFileName), stdin);

    /* Removes the newline character from the filename */
    removeNewLine(sFileName);

    /* Reads data from file */
    nQCount += readData(sFileName, records, nMaxQst, nRecords);

    /* Checks if data was successfully imported */
    if (nQCount == -1)
    {
        printf("Failed to import data.\n\n");

        nQCount = nRecords;
    }
    else
    {
        printf("Successfully imported data to %s.\n\n", sFileName);
    }

    /* Returns number of records read */
    return nQCount;
}

/* This function exports the question records to a text file with the specified filename
   @param records[MAX_RECORDS] - an array of structs to be exported
   @param nQCount - the number of question records in the array
   Precondition: The file must be in the correct format (.txt file)
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
   @param pScoreCount - address of the number of scores in the array
   Precondition: The file must be in the correct format (.txt file)
*/
void
playGame(struct question records[MAX_RECORDS],
         int nQCount,
         struct score scores[MAX_SCORES],
         int *pScoreCount)
{
    int nQInd;
    int nTopicInd;
    int nRand;
    int nAnswer; 
    int nQuestionsFound;
    int i;
    int nFoundMatch = 0;
    int nChoice = -1;
    int nScore = 0;
    int nTopicCount = 0;
    int arrTopicIndices[MAX_RECORDS];
    str30 sPlayerName;
    str50 sTopics[MAX_TOPICS];

    /* Removes new line entered */
    getchar();

    /* Prompts the user to enter their name */
    printf("Enter your name: ");
    fgets(sPlayerName, sizeof(sPlayerName), stdin);

    /* Removes the newline character from the name */
    removeNewLine(sPlayerName);

    system("cls");

    /* Displays a welcome message */
    printf("\nWelcome %s! Let's play!\n\n", sPlayerName);

    /* Loop until the user chooses to quit */
    do
    {
        /* Displays the available topics */
        displayTopics(records, nQCount, sTopics, &nTopicCount, arrTopicIndices);

        /* Prompts the user to choose a topic */
        printf("Enter a topic (0 to quit): ");
        scanf("%d", &nChoice);

        /* If the user enters an invalid choice, display an error message and continue */
        if (nChoice < 0 || nChoice > nTopicCount)
        {
            printf("\nInvalid choice.\n\n");
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

        /* If there are questions with the chosen topic, play the game */
        if (nQuestionsFound > 0)
		{
            system("cls");

			/* Chooses a random question with the chosen topic */
        	srand(time(NULL));
        	nRand = rand() % nQuestionsFound;

            /* Displays the question record under topic */
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
                        	printf("\nCorrect!\n\n");
                        	nScore++;
                    	}
                    	else
                    	{
                        	printf("\nSorry, the correct answer is %d\n\n", records[nQInd].nCorrAns);
                    	}

                    	/* Displays the current score */
                    	printf("Score: %d\n\n", nScore);

                        /* Pauses the program then clears the screen */
                        system("pause");
                        system("cls");
               		}
                	nTopicInd++;
            	}
        	}
		}
    } while (nChoice != 0);

	/* Checks if the player's score is already in the scores array */
	for (i = 0; i < *pScoreCount; i++)
	{
    	if (strcmp(scores[i].sName, sPlayerName) == 0)
		{
			/* Adds the player's score to the existing score */
       		scores[i].nScore += nScore;

			/* Displays the player's new score */
			printf("\n%s's new score: %d\n\n", sPlayerName, scores[i].nScore);

			/* Sets the nFoundMatch flag to 1 */
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
   Precondition: The scores array contains accumulated scores
*/
void
viewScores(struct score scores[MAX_SCORES],
           int nTotalScores)
{
    int i;
    int j;
    struct score temp;

    if (nTotalScores == 0)
    {
        printf("\nNo scores to display.\n\n");

        /* Pauses the program then clears the screen */
        system("pause");
        system("cls");
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
        printf("LEADERBOARD\n\n");
        
        printf("Rank\tName\t\tScore\n");
        for (i = 0; i < nTotalScores; i++)
        {
            printf("%d\t%-15s\t%d\n", i+1, scores[i].sName, scores[i].nScore);
        }
        printf("\n");

        /* Pauses the program then clears the screen */
        system("pause");
        system("cls");
    }
}

/* This function loads the scores of upon opening play game in the play menu.
   @param scores[MAX_SCORES] - an array of structs to store the scores in
   @returns the number of scores loaded from the file, or -1 if an error occurs
*/
int
loadScores(struct score scores[MAX_SCORES])
{
    FILE *fptr;
    str50 sName;
    int nScore;
    int nReadInd = 0;

    /* Opens file for reading */
    fptr = fopen("data/score.txt", "r");
    if (fptr == NULL)
    {
        fptr = fopen("score.txt", "r");
    }

    /* Checks if the file exists */
    if (fptr == NULL)
    {
        printf("No scores found.\n\n");
        return 0;
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
    Precondition: The scores array contains accumulated scores
*/
void
saveScores(struct score scores[MAX_SCORES],
           int nTotalScores)
{
    FILE *fptr;
    int i;

    /* Opens file for writing */
    fptr = fopen("data/score.txt", "w");
    if (fptr == NULL)
    {
        fptr = fopen("score.txt", "w");
    }

    /* Checks if the file exists */
    if (fptr == NULL)
    {
        printf("Error writing scores.\n");
        return;
    }

    /* Writes the name and score to the file */
    for(i = 0; i < nTotalScores; i++)
    {
        fprintf(fptr, "%s\n%d\n\n", scores[i].sName, scores[i].nScore);
    }

    fclose(fptr);
}

/* This function displays the main menu of the play mode of the program.
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nTotalRecords - the number of questions in the array
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
    	system("cls");
    	
        printf("\nPLAY\n");
        printf("--------------------\n\n");

        printf("Choose an option:\n");
        printf("1. Play\n");
        printf("2. View Scores\n");
        printf("3. Exit\n");
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            /* Selects play game option */
            case 1:
                system("cls");

                /* Plays the game */
                playGame(records, nTotalRecords, scores, &nTotalScores);
                break;
            /* Selects view scores option */
            case 2:
                system("cls");

                /* Displays the scores */
                viewScores(scores, nTotalScores);
                break;
            /* Selects exit game option */
            case 3:
                system("cls");

                /* Saves the scores to the file */
                saveScores(scores, nTotalScores);
                break;
            /* Displays error message if invalid choice is entered */
            default:
                printf("\nInvalid choice. Try again.\n\n");
                break;
        }
    }
}



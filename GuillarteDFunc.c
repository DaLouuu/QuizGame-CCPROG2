#include "GuillarteDFunc.h"

/*This function displays the title screen when you start the game up.
*/
void
displayMenu()
{
    int nBorder;

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
   @param nRecords - total amount of records
   @return the total amount of records
*/
int
login(str20 sAdminPass,
      int nRecords)
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
        nRecords = manageData(nRecords);
    } 
    else
    {
        printf("Going back to main menu.\n\n");
        
        /* Goes back to main menu */
        displayMenu();
    }

    return nRecords;
}


/* This function displays the user friendly Manage Data UI and manages
   the question records of the game
   @param nRecords - total amount of records
   @return the total amount of records
*/
int
manageData(int nRecords)
{
    int nChoice;
    
    /* Array of question records */
    struct question arrRecords[MAX_RECORDS];
    
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
        
        switch (nChoice)
        {
        	
            /* Adds a new record */
            case 1:
                printf("Add Record selected.\n\n");
                
                /* Increases the number of records by 1 after adding the new record */
                nRecords = addRecord(arrRecords, nRecords);
                break;
                
            /* Edits an existing record */
            case 2:
                printf("Edit Record selected.\n\n");
                
                /* Calls the editRecord function to edit a record */
                editRecord(arrRecords, nRecords);
                break;
            
            /* Deletes an existing record */
            case 3:
                printf("Delete Record selected.\n\n");

                /* Calls the deleteRecord function to edit a record */
                nRecords = deleteRecord(arrRecords, nRecords);
                break;

            /* Imports data from a file */
            case 4:
                printf("Import Data selected.\n\n");

                /* Calls the importData function to import records from a file */
                nRecords = importData(arrRecords, MAX_RECORDS);
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
                    nRecords = exportData(arrRecords, nRecords);
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

    return nRecords;
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
*/
int
addRecord(struct question records[MAX_RECORDS],
		  int nCount)
{
    /* Declares and initializes the necessary variables */
    str50 sTopic, sAnswer, sChoices[MAX_CHOICES];
    str200 sQText;
    int nCorrAns, nLastQNum, nRecordInd, nQNum, nChoiceInd;
    char cNewLine;

    /* Gets the question and answer from the user */
    printf("\nEnter question: ");
    scanf("%c", &cNewLine);
    fgets(sQText, MAX_STR_LEN, stdin);
    removeNewLine(sQText);
    printf("Enter answer: ");
    fgets(sAnswer, MAX_STR_LEN, stdin);
    removeNewLine(sAnswer);

    /* Checks if the question-answer pair already exists */
    nRecordInd = findRecord(records, nCount, sQText, sAnswer);

    if (nRecordInd >= 0)
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
   It checks if a topic is unique before displaying it.
   @param question records[MAX_RECORDS] - question records
   @param nCount - the number of records in the records array
*/
void
displayTopics(struct question records[MAX_RECORDS],
              int nCount)
{
    int nIndex, nTopicInd, nFound;
    str50 arrTopics[MAX_RECORDS];

    /* Prints the topics of the questions in the question bank */
    printf("Topics:\n");
    for (nIndex = 0, nTopicInd = 0; nIndex < nCount; nIndex++)
    {
        nFound = 0;

        /* Checks if the topic of the current record is already in the array of topics */
        for (int i = 0; i < nTopicInd; i++)
        {
            /* If the topic is already in the array, set nFound to 1 */
            if (strcmp(records[nIndex].sTopic, arrTopics[i]) == 0)
            {
                nFound = 1;
                break;
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
   @param records - array of question records
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
    /* Declares and initializes the necessary variables */
    int nIndex, nQstInd = 0;
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
        for (int i = 0; i < nQstInd; i++)
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


/* This function displays details of a question record.
   @param record - the question record to display
*/
void
displayQuestion(struct question record)
{
    /* Declares and initializes the necessary variables */
    int nIndex;

    /* Displays the question details */
    printf("\nQuestion Details:\n");
    printf("  Topic: %s \n", record.sTopic);
    printf("  Question: %s \n", record.sQText);
    printf("  Choices: \n");


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

/* This function edits the chosen question record of a chosen topic
   @param question records[MAX_RECORDS] - question records
   @param nCount - number of records
*/
void
editRecord(struct question records[MAX_RECORDS],
                int nCount)
{
    int nTopicInd, nQstInd, nConfirm, nChoice, nIndex;
    int nQstIndices[MAX_RECORDS];
    str50 sTopic, sNewTopic, sNewQText, sNewChoice, sNewAns;
    int nNewAns;
    
    do
    {
        /* Displays available topics and ask for the topic index to edit */
        displayTopics(records, nCount);
        printf("Enter topic index: ");
        scanf("%d", &nTopicInd);
        
        /* Gets the selected topic and remove newline character */
        strcpy(sTopic, records[nTopicInd - 1].sTopic);
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
                scanf("%s", sNewTopic);
                strcpy(records[nQstIndices[nQstInd - 1]].sTopic, sNewTopic);
                break;
            case 2:
                /* Edits the question */
                printf("Enter new question: ");
                scanf("%s", sNewQText);
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
                scanf("%s", sNewAns);
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

        /* Asks for confirmation */
        printf("Do you want to edit another record? (1 - Yes, 0 - No): ");
        scanf("%d", &nConfirm);
    } while (nConfirm == 1);
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
    int nQstIndices[MAX_RECORDS];
    str50 sTopic;

    do
    {
        /* Displays available topics and ask for the topic index to delete */
        displayTopics(records, nCount);
        printf("Enter topic index: ");
        scanf("%d", &nTopicInd);

        /* Gets the selected topic and remove newline character */
        strcpy(sTopic, records[nTopicInd - 1].sTopic);
        removeNewLine(sTopic);

        /* Displays questions under the selected topic and ask for the question index to delete */
        displayQuestions(records, nCount, sTopic, nQstIndices, &nQstInd);
        printf("Enter question index: ");
        scanf("%d", &nQstInd);

        /* Confirms if the admin wants to delete the selected record */
        printf("Are you sure you want to delete this record? (1-Yes, 2-No): ");
        scanf("%d", &nConfirm);

        switch (nConfirm)
        {
            case 1:

                /* Shifts all records after the selected index one position to the left */
                for (nIndex = nQstInd - 1; nIndex < nCount - 1; nIndex++)
                {
                    records[nIndex] = records[nIndex + 1];
                }

                /* Decreases the total number of records by 1 */
                nCount--;

                /* Displays updated topics and questions and success message */
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

    return nCount;
}

/* This function reads questions from a file and stores them in a struct array.
   @param sFileName - the name of the file to read questions from
   @param records[MAX_RECORDS] - an array of structs to store the questions in
   @param nMaxQst - the maximum number of questions to read from the file
   @return the number of questions read from the file, or -1 if an error occurs
*/
int
readData(str30 sFileName,
         struct question records[MAX_RECORDS],
         int nMaxQst)
{
    FILE *fptr;
    int nRecordInd = 0, nChoiceInd, nQNum;
    str50 sTopic, sChoices[MAX_CHOICES], sCorrAns;
    str200 sQText;

    /* Appends ".txt" extension to the filename */
    strcat(sFileName, ".txt");

    /* Opens file for reading */
    fptr = fopen(sFileName, "r");
    if (fptr == NULL)
    {
        printf("Failed to open file.\n");
        return -1;
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

        /* Returns number of records read */
        return nRecordInd;
    }
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

/* This function imports question records from a file given the filename
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
    if (nQCount == -1)
    {
        printf("Failed to import data.\n\n");
    }
    else
    {
        printf("Successfully imported data.\n\n");
    }

    return nQCount;
}

/* This function exports the question records to a text file
   with the specified filename. The data in this exported file
   can be used in the import option.
   @param records[MAX_RECORDS] - an array of structs to be exported
   @param nQCount - the number of question records in the array
   @return the number of question records exported
*/
int
exportData(struct question records[MAX_RECORDS],
           int nQCount)
{
    str30 sFileName;
    FILE* fptr;

    /* Removes new line entered */
    getchar();

    /* Prompts the user to enter the filename */
    printf("\nEnter filename: ");
    fgets(sFileName, sizeof(sFileName), stdin);

    /* Removes the newline character from the filename */
    removeNewLine(sFileName);

    /* Opens the file */
    fptr = fopen(sFileName, "w");
    if (fptr == NULL)
    {
        printf("Failed to open file.\n\n");
    }
    else 
    {

        /* Writes question records to file using writeData function */
        writeData(sFileName, records, nQCount);

        /* Closes the file */
        fclose(fptr);

        /* Prints a success message if the data was exported successfully */
        printf("Data successfully exported to %s.\n\n", sFileName);
    }

    /* Returns the number of questions imported */
    return nQCount;
}

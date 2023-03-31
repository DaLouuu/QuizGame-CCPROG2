#include "GuillarteDFunc.h"

/*This function displays the title screen when you start the game up.
*/
void
titleScreen()
{
    int i;

    //Prints top border of title screen
    for(i = 0; i < 50; i++)
    {
        if(i == 0)
            printf("%c", 201); //prints ╔
        else if (i == 49)
            printf("%c", 187); //prints ╗
        else
            printf("%c", 205); //prints ═
    }

    //Prints program title and author information
    printf("\n%c%*s%*s%c\n", 186, 38, "~General Knowledge Quiz Game~", 10, " ", 186); //186 here is ║
    printf("%c%*s%*s%c\n", 186, 36, "Dana Louise A. Guillarte", 12, " ", 186); //186 here is ║
    printf("%c%*s%*s%c\n", 186, 25, "S23A", 23, " ", 186); //186 here is ║

    //Prints divider
    for(i = 0; i < 50; i++)
    {
        if (i == 0)
            printf("%c", 204); //Prints ╠
        else if (i == 49)
            printf("%c", 185); //Prints ╣
        else
            printf("%c", 205); //Prints ═
    }

    //Prints game options and exit
    printf("\n%c%*s%*s%c", 186, 27, "[1] Play", 21, " ", 186); //186 here is ║
    printf("\n%c%*s%*s%c", 186, 30, "[2] Manage Data", 18, " ", 186); //186 here is ║
    printf("\n%c%*s%*s%c\n", 186, 27, "[3] Exit", 21, " ", 186); //186 here is ║

    //Prints bottom border
    for(i = 0; i < 50; i++)
    {
        if (i == 0)
            printf("%c", 200); //prints ╚
        else if (i == 49)
            printf("%c\n", 188); //prints ╝
        else
            printf("%c", 205); //prints ═
    }
}

/* This function checks if the scanned entry of the user is within the range that is accepted
   @param min - minimum accepted value
   @param max - maximum accepted value
   @return choice if the choice is in the range [min, max], else 0
*/
int
promptChoice(int min,
			 int max)
{
    int choice;

        //Determines if user input is valid or invalid
        do 
        {
                //Asks user for their choice
                scanf("%d", &choice);

                if (!(choice >= min && choice <= max))
                {
                    printf ("Invalid input!\n");
                    printf ("Enter valid choice [%d - %d]: \n", min, max);
                }
        } while(!(choice >= min && choice <= max));

        return choice;
}

/* This function accepts the password entered by the user and checks if correct
   @param adminPass - array containing the admin password for checking
*/
void login(str20 adminPass)
{
    char password[MAX_PASS_LEN + 1];
    char ch;
    int i = 0, choice = 1;
    
    printf("Enter admin password: ");
    
    //Gets password from user
    while((ch = getch()) != '\r' && i < MAX_PASS_LEN)
    {
        if(ch == '\b' && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else if(ch != '\b' && ch != '\t' && ch != 0)
        {
            printf("*");
            password[i++] = ch;
        }
    }
    password[i] = '\0';
    printf("\n");
    
    while(strcmp(password, adminPass) != 0 && choice == 1)
    {
        printf("Incorrect password.\n");
        printf("Press 1 to try again, or any other key to go back to main menu: ");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            printf("Enter admin password: ");
            i = 0;
            //Gets password from user again
            while((ch = getch()) != '\r' && i < MAX_PASS_LEN)
            {
                if(ch == '\b' && i > 0)
                {
                    printf("\b \b");
                    i--;
                }
                else if(ch != '\b' && ch != '\t' && ch != 0)
                {
                    printf("*");
                    password[i++] = ch;
                }
            }
            password[i] = '\0';
            printf("\n");
        }
    }
    
    if (strcmp(password, adminPass) == 0)
    {
        printf("Login successful!\n\n");
        //Displays user-friendly interface for managing data
        manageData();
    } 
    else
    {
        printf("Going back to main menu.\n\n");
        //Goes back to main menu
        titleScreen();
    }

}


/* This function displays the user friendly Manage Data UI and manages
   the question records of the game
*/
void
manageData()
{
	int choice;
	//Initial number of records to be modified
	int numRecords = 7;
	struct question records[MAX_RECORDS];
	
    do
	{
        printf("MAIN MENU\n");
        
        printf("1. Add Record\n");
        printf("2. Edit Record\n");
        printf("3. Import Data\n");
        printf("4. Export Data\n");
        printf("5. Go Back to Main Menu\n");
        
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice)
		{
            case 1:
                printf("Add Record selected.\n\n");
                numRecords = addRecord(records, numRecords);
                break;
            case 2:
                printf("Edit Record selected.\n\n");
                editRecord(records, numRecords);
                break;
            case 3:
                printf("Import Data selected.\n\n");
                break;
            case 4:
                printf("Export Data selected.\n\n");
                break;
            case 5:
                printf("Going back to main menu.\n\n");
                break;
            default:
                printf("Invalid choice. Try again.\n\n");
        }
    } while(choice != 5);
}

/* This function adds a question record to the structure of questions
   in the program
   @param question records[MAX_RECORDS] - question records
   @param count - number of records
*/
int
addRecord(struct question records[MAX_RECORDS],
		  int count) 
{
	str200 questionText;
	str50 answer, topic, choices[MAX_CHOICES];
	int recordInd, choiceInd, correctAns, topicInd = -1, questionNum = 1, found = 0;
	char newLine;
	
	//Asks first for question and answer
	printf("Enter question: ");
	scanf("%c", &newLine);
	fgets(questionText, MAX_QTEXT, stdin);
	printf("Enter answer: ");
	fgets(answer, MAX_TOPIC_LEN, stdin);
	
	//Checks if the question and answer is found in records
	for(recordInd = 0; recordInd < count && !found; recordInd++)
	{
		if(strcmp(records[recordInd].questionText, questionText) == 0 && strcmp(records[recordInd].choices[records[recordInd].correctAns - 1], answer) == 0)
		{
			found = 1;
			
			printf("Record already exists. It is found below:\n");
			printf("Question: %s\n", records[recordInd].questionText);
			printf("Answer: %s\n", records[recordInd].choices[records[recordInd].correctAns - 1]);
			printf("Topic: %s\n", records[recordInd].topic);
			printf("Choices:\n");
			
			for(choiceInd = 0; choiceInd < MAX_CHOICES; choiceInd++)
				printf("(%d) %s\n", choiceInd + 1, records[recordInd].choices[choiceInd]);
		}
	}
	
	//Asks for the rest of the details (topic, choices, and correct answer) then adds them as a record
	if(!found)
	{
		printf("Enter topic: ");
		fgets(topic, MAX_TOPIC_LEN, stdin);
		
		printf("Enter choice 1: ");
		fgets(choices[0], MAX_TOPIC_LEN, stdin);
		printf("Enter choice 2: ");
		fgets(choices[1], MAX_TOPIC_LEN, stdin);
		printf("Enter choice 3: ");
		fgets(choices[2], MAX_TOPIC_LEN, stdin);
		
		printf("Enter correct answer (1 - 3): ");
		scanf("%d", &correctAns);
		scanf("%c", &newLine);
		
		if(strcmp(records[recordInd].topic, topic) == 0) 
		{
            if(records[recordInd].number >= questionNum)
            {
                questionNum = records[recordInd].number + 1;
                topicInd = recordInd;
            }
        }
        
        if (topicInd == -1)
            questionNum = 1;

        //Stores the information in the record and increment the number of records
        records[count].number = questionNum;
        strcpy(records[count].topic, topic);
        strcpy(records[count].questionText, questionText);
        strcpy(records[count].choices[0], choices[0]);
        strcpy(records[count].choices[1], choices[1]);
        strcpy(records[count].choices[2], choices[2]);
        records[count].correctAns = correctAns;
        count++;

        printf("Record added successfully.\n");
    }
    
    printf("\n");
		
	return count;
}

/* This function edits a question record in the structure of questions
   in the program
   @param question records[MAX_RECORDS] - question records
   @param count - number of records
*/
void
editRecord(struct question records[MAX_RECORDS],
		   int count)
{
    char uniqueTopics[MAX_TOPICS][MAX_TOPIC_LEN];
	int nUnique = 0, topicInd, currInd, topicChoice, questionChoice, found;

	//Loops through all questions and add unique topics to the list
	for (topicInd = 0; topicInd < count; topicInd++)
	{
    	char* current = records[topicInd].topic;
    	//Resets found flag for next iteration
    	found = 0;

    	//Checks if current is already in uniqueTopics
    	for(currInd = 0; currInd < nUnique; currInd++) 
        	if (strcmp(current, uniqueTopics[currInd]) == 0) 
                //Topic already in list, so don't add it again
            	found = 1;

    	//If not found, add it to the list
    	if(!found)
    	{
        	strcpy(uniqueTopics[nUnique], current);
        	nUnique++;
    	}
	}

	//Displays the unique topics
	printf("Available topics:\n");
	
	for (topicInd = 0; topicInd < nUnique; topicInd++)
    	printf("(%d) %s\n", topicInd + 1, uniqueTopics[topicInd]);

	//Lets the admin choose a topic
	printf("Enter the number of the topic you want to edit: ");
	scanf("%d", &topicChoice);
	
	printf("Questions in topic \"%s\":\n", uniqueTopics[topicChoice - 1]);
	
	for (int i = 0; i < count; i++)
    	if (strcmp(records[i].topic, uniqueTopics[topicChoice - 1]) == 0)
        	printf("%d. %s\n", records[i].number, records[i].questionText);

	//Lets the admin choose a question to edit
	printf("Enter the number of the question you want to edit: ");
	scanf("%d", &questionChoice);


}


void 
deleteRecord()
{
	
}

void
importData()
{
	FILE *fptr;
	
	
	
}

void
exportData()
{
	
}
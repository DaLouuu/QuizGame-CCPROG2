#include "GuillarteDFunc.h"

/*This function displays the title screen when you start the game up.
*/
void
titleScreen()
{
    int i;

    //prints top border of title screen
    for(i = 0; i < 50; i++)
    {
        if(i == 0)
            printf("%c", 201); //prints ╔
        else if (i == 49)
            printf("%c", 187); //prints ╗
        else
            printf("%c", 205); //prints ═
    }

    //prints game title and author information
    printf("\n%c%*s%*s%c\n", 186, 38, "~General Knowledge Quiz Game~", 10, " ", 186); //186 here is ║
    printf("%c%*s%*s%c\n", 186, 36, "Dana Louise A. Guillarte", 12, " ", 186); //186 here is ║
    printf("%c%*s%*s%c\n", 186, 25, "S23A", 23, " ", 186); //186 here is ║

    //prints divider
    for(i = 0; i < 50; i++)
    {
        if (i == 0)
            printf("%c", 204); //prints ╠
        else if (i == 49)
            printf("%c", 185); //prints ╣
        else
            printf("%c", 205); //prints ═
    }

    //prints game options and exit
    printf("\n%c%*s%*s%c", 186, 27, "[1] Play", 21, " ", 186); //186 here is ║
    printf("\n%c%*s%*s%c", 186, 30, "[2] Manage Data", 18, " ", 186); //186 here is ║
    printf("\n%c%*s%*s%c\n", 186, 27, "[3] Exit", 21, " ", 186); //186 here is ║

    //prints bottom border
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

        //determines if user input is valid or invalid
        do 
        {
                //asks user for their choice
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
void
login(char adminPass[])
{
    char password[MAX_PASSWORD_LENGTH], ch;
    int i = 0;
    int choice = 1;
    
    printf("Enter admin password: ");
    
    // get password from user
    while (fgets(&ch, 2, stdin) != '\0' && ch != '\n')
	{
        // handle backspace/delete key
        if (ch == 127 || ch == 8)
		{
            if (i > 0)
			{
                i--;
                
                printf("\b \b"); // overwrite the character with space and move the cursor back
            }
        }
		else if (i < MAX_PASSWORD_LENGTH - 1 && ch >= 32 && ch <= 126)
		{
            password[i++] = ch;
            
            printf("*"); // display asterisks instead of characters
        }
    }
    
    password[i] = '\0';
    printf("\n");
    
    // check if password is correct and allow user to retry if incorrect
    while (strcmp(password, adminPass) != 0 && choice == 1)
	{
        printf("Incorrect password.\n");
        printf("Press 1 to try again, or any other key to go back to main menu: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            printf("Enter admin password: ");
            i = 0;
            // get password from user again
            while (fgets(&ch, 2, stdin) != '\0' && ch != '\n')
			{
                // handle backspace/delete key
                if (ch == 127 || ch == 8) {
                    if (i > 0) {
                        i--;
                        
                        printf("\b \b"); // overwrite the character with space and move the cursor back
                    }
                }
				else if (i < MAX_PASSWORD_LENGTH - 1 && ch >= 32 && ch <= 126)
				{
                    password[i++] = ch;
                    
                    printf("*"); // display asterisks instead of characters
                }
            }
            
            password[i] = '\0';
            printf("\n");
        }
    }
    
    if (strcmp(password, adminPass) == 0)
	{
        printf("Login successful!\n");
        // display user-friendly interface for managing data
        manageData();
    } 
	else
	{
        printf("Going back to main menu.\n");
        // go back to main menu
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
        
        switch (choice)
		{
            case 1:
                printf("Add Record selected.\n");
                addRecord(question[] records, &numRecords);s
                break;
            case 2:
                printf("Edit Record selected.\n");
                break;
            case 3:
                printf("Import Data selected.\n");
                break;
            case 4:
                printf("Export Data selected.\n");
                break;
            case 5:
                printf("Going back to main menu.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

/* This function adds a question record to the structure of questions
   in the program
   @param question[] records - stored question records
   @param *numRecords - address of numRecords for modification
*/
void
addRecord(struct question[] records, int* numRecords)
{
	char questionText[200];
    char answer[50];
    int i, j, found, topicIndex, questionNumber;

    // Prompt user for the question and answer pair
    printf("Enter question: ");
    fgets(questionText, 200, stdin);
    printf("Enter answer: ");
    fgets(answer, 50, stdin);

    // Check if the question-answer pair already exists in the records
    found = 0;
    for (i = 0; i < *numRecords && !found; i++)
	{
    	if (strcmp(records[i].questionRext, questionText) == 0 && strcmp(records[i].choices[records[i].correctAns - 1], answer) == 0)
    	{
        	found = 1;
        	
        	printf("Record already exists:\n");
        	printf("Question: %s", records[i].questionText);
        	printf("Answer: %s", records[i].choices[records[i].correctAns - 1]);
       		printf("Topic: %s\n", records[i].topic);
        	printf("Choices:\n");
        	
        	for (j = 0; j < 3; j++)
            	printf("%d. %s", j+1, records[i].choices[j]);
        	printf("\n");
    	}
	}

    if (!found)
	{
        // Prompt user for the remaining inputs
        printf("Enter topic: ");
        fgets(records[*numRecords].topic, 50, stdin);
        printf("Enter choice 1: ");
        fgets(records[*numRecords].choices[0], 50, stdin);
        printf("Enter choice 2: ");
        fgets(records[*numRecords].choices[1], 50, stdin);
        printf("Enter choice 3: ");
        fgets(records[*numRecords].choices[2], 50, stdin);

        // Assign the question number by finding the last question number of the given topic
        topicIndex = -1;
        questionNumber = 1;
        for (i = 0; i < *numRecords; i++)
		{
            if (strcmp(records[i].topic, records[*numRecords].topic) == 0)
			{
                if (records[i].number >= questionNumber)
                    question_number = records[i].number + 1;
                    
                topicIndex = i;
            }
        }
        if (topicIndex == -1) {
            questionNumber = 1;
        }

        // Store the information in the record and increment the number of records
        records[*numRecords].number = question_number;
        strcpy(records[*numRecords].questionText, questionText);
        strcpy(records[*numRecords].choices[2], answer);
        records[*numRecords].correctAns = 3;
        (*numRecords)++;

        printf("Record added successfully.\n");
    }

    printf("\n");
}

void 
editRecord()
{
	
}

void 
deleteRecord()
{
	
}

void
importData()
{
	
}

void
exportData()
{
	
}
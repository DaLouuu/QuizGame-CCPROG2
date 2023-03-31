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
login(str20 adminPass)
{
    char ch;
    str20 password;
    int i = 0, choice = 1;
    
    printf("Enter admin password: ");
    
    // get password from user
    fgets(password, MAX_PASS_LEN, stdin);
    scanf("%c", &ch);
    
    while(strcmp(password, adminPass) != 0 && choice == 1)
    {
    	printf("Incorrect password.\n");
        printf("Press 1 to try again, or any other key to go back to main menu: ");
        scanf("%d", &choice);
        
        if(choice == 1)
		{
            printf("Enter admin password: ");
            fgets(password, MAX_PASS_LEN, stdin);
    		scanf(&ch, 1, stdin);
        }
	}
	
//    while(fgets(ch, 2, stdin) != '\0' && ch != '\n')
//	{
//        // handle backspace/delete key
//        if (ch == 127 || ch == 8)
//		{
//            if (i > 0)
//			{
//                i--;
//                
//                printf("\b \b"); // overwrite the character with space and move the cursor back
//            }
//        }
//		else if (i < MAX_PASS_LEN - 1 && ch >= 32 && ch <= 126)
//		{
//            password[i++] = ch;
//            
//            printf("*"); // display asterisks instead of characters
//        }
//    }
//    
//    password[i] = '\0';
//    printf("\n");
//    
//    // check if password is correct and allow user to retry if incorrect
//    while(strcmp(password, adminPass) != 0 && choice == 1)
//	{
//        printf("Incorrect password.\n");
//        printf("Press 1 to try again, or any other key to go back to main menu: ");
//        scanf("%d", &choice);
//        
//        if(choice == 1)
//		{
//            printf("Enter admin password: ");
//            i = 0;
//            // get password from user again
//            while(fgets(&ch, 2, stdin) != '\0' && ch != '\n')
//			{
//                // handle backspace/delete key
//                if (ch == 127 || ch == 8)
//				{
//                    if (i > 0)
//					{
//                        i--;
//                        
//                        printf("\b \b"); // overwrite the character with space and move the cursor back
//                    }
//                }
//				else if(i < MAX_PASS_LEN - 1 && ch >= 32 && ch <= 126)
//				{
//                    password[i++] = ch;
//                    
//                    printf("*"); // display asterisks instead of characters
//                }
//            }
//            
//            password[i] = '\0';
//            printf("\n");
//        }
//    }
    
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
        
        switch (choice)
		{
            case 1:
                printf("Add Record selected.\n");
                numRecords = addRecord(records, numRecords);
                break;
            case 2:
                printf("Edit Record selected.\n");
                editRecord(records, numRecords);
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
   @param question records[] - question records
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
	

	printf("Enter question: ");
	scanf("%c", &newLine);
	fgets(questionText, MAX_QTEXT, stdin);
	printf("Enter answer: ");
	fgets(answer, MAX_TOPIC_ANS, stdin);
	
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
	
	if(!found)
	{
		printf("Enter topic: ");
		fgets(topic, MAX_TOPIC_ANS, stdin);
		
		printf("Enter choice 1: ");
		fgets(choices[0], MAX_TOPIC_ANS, stdin);
		printf("Enter choice 2: ");
		fgets(choices[1], MAX_TOPIC_ANS, stdin);
		printf("Enter choice 3: ");
		fgets(choices[2], MAX_TOPIC_ANS, stdin);
		
		printf("Enter correct answer (1 - 3): ");
		scanf("%d", &correctAns);
		scanf("%c", &newLine);
		
		if(strcmp(records[recordInd].topic[topicInd + 1], topic) == 0) 
		{
            if(records[recordInd].number >= questionNum)
            {
                questionNum = records[recordInd].number + 1;
                topicInd = recordInd;
            }
        }
        
        if (topicInd == -1)
            questionNum = 1;

        // Store the information in the record and increment the number of records
        records[count].number = questionNum;
        strcpy(records[count].topic[topicInd], topic);
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
   @param question records[] - question records
   @param count - number of records
*/
void
editRecord(struct question records[MAX_RECORDS],
		   int count)
{
    int number, found = 0, topicInd, topicNum = 0;
    char choice;
    str50 newTopic;
    str200 newQuestionText;
    str50 newChoice;
    int newCorrectAns;
    
    printf("Unique Topics:\n");
    
    for(topicInd = 0; topicInd < MAX_TOPIC; topicInd++)
    {
    	if(strcmp(records[topicInd].topic[topicNum], records[topicInd + 1].topic[topicNum + 1]) != 0)
    	{
    		printf("(%d) %s\n", topicNum + 1, records[topicInd].topic);
    		topicNum++;
		}
	}
	
//    printf("\nEnter the question number to edit: ");
//    scanf("%d", &number);
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
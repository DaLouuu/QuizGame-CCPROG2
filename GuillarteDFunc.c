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
addRecord(struct question records[],
		  int *count) 
{
    int i, j, found, topicIndex, questionNumber;
    str50 topic, choices[3], answer;
	str200 questionText;
    int correctAns;

    // Prompt user for the question and answer pair
    printf("Enter question: ");
    fgets(questionText, 200, stdin);
    printf("Enter answer: ");
    fgets(answer, 50, stdin);

    // Check if the question-answer pair already exists in the records
    found = 0;
    for (i = 0; i < *count && !found; i++) 
	{
        if (strcmp(records[i].questionText, questionText) == 0 && strcmp(records[i].choices[records[i].correctAns - 1], answer) == 0) 
		{
            found = 1;

            printf("Record already exists.:\n");
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
        fgets(topic, 50, stdin);
        printf("Enter choice 1: ");
        fgets(choices[0], 50, stdin);
        printf("Enter choice 2: ");
        fgets(choices[1], 50, stdin);
        printf("Enter choice 3: ");
        fgets(choices[2], 50, stdin);
        printf("Enter correct answer (1-3): ");
        scanf("%d", &correctAns);
        getchar(); // consume newline character

        // Assign the question number by finding the last question number of the given topic
        topicIndex = -1;
        questionNumber = 1;
        for (i = 0; i < *count; i++) 
		{
            if (strcmp(records[i].topic, topic) == 0) 
			{
                if (records[i].number >= questionNumber)
                    questionNumber = records[i].number + 1;
                topicIndex = i;
            }
        }
        
        if (topicIndex == -1)
            questionNumber = 1;

        // Store the information in the record and increment the number of records
        records[*count].number = questionNumber;
        strcpy(records[*count].topic, topic);
        strcpy(records[*count].questionText, questionText);
        strcpy(records[*count].choices[0], choices[0]);
        strcpy(records[*count].choices[1], choices[1]);
        strcpy(records[*count].choices[2], choices[2]);
        records[*count].correctAns = correctAns;
        (*count)++;

        printf("Record added successfully.\n");
    }
    printf("\n");
}


void
editRecord(struct question records[],
		   int count)
{
    int number, found = 0, i;
    char choice;
    str50 newTopic;
    str200 newQuestionText;
    str50 newChoice;
    int newCorrectAns;
    
    printf("\nEnter the question number to edit: ");
    scanf("%d", &number);
    
    for (i = 0; i < count; i++) {
        if (records[i].number == number) {
            found = 1;
            printf("\nEditing record #%d:\n", number);
            printf("Topic: %s", records[i].topic);
            printf("Question text: %s", records[i].questionText);
            printf("Choice A: %s", records[i].choices[0]);
            printf("Choice B: %s", records[i].choices[1]);
            printf("Choice C: %s", records[i].choices[2]);
            printf("Correct answer: %d\n", records[i].correctAns);
            
            printf("\nEnter the new topic of the question: ");
            scanf("%s", newTopic);
            printf("Enter the new question text: ");
            getchar();
            fgets(newQuestionText, sizeof(newQuestionText), stdin);
            printf("Enter the new choice A: ");
            fgets(newChoice, sizeof(newChoice), stdin);
            printf("Enter the new choice B: ");
            fgets(newChoice, sizeof(newChoice), stdin);
            printf("Enter the new choice C: ");
            fgets(newChoice, sizeof(newChoice), stdin);
            printf("Enter the new number of the correct answer (1-3): ");
            scanf("%d", &newCorrectAns);
            
            printf("\nCurrent record:\n");
            printf("Topic: %s", records[i].topic);
            printf("Question text: %s", records[i].questionText);
            printf("Choice A: %s", records[i].choices[0]);
            printf("Choice B: %s", records[i].choices[1]);
            printf("Choice C: %s", records[i].choices[2]);
            printf("Correct answer: %d\n", records[i].correctAns);
            
            printf("\nWhich field would you like to edit?\n");
            printf("1. Topic\n");
            printf("2. Question text\n");
            printf("3. Choices\n");
            printf("4. Correct answer\n");
            printf("5. Cancel\n");
            printf("Enter your choice: ");
            scanf(" %c", &choice);
            
            switch(choice) {
                case '1':
                    strcpy(records[i].topic, newTopic);
                    break;
                case '2':
                    strcpy(records[i].questionText, newQuestionText);
                    break;
                case '3':
                    printf("Enter the new choice A: ");
                    fgets(records[i].choices[0], sizeof(records[i].choices[0]), stdin);
                    printf("Enter the new choice B: ");
                    fgets(records[i].choices[1], sizeof(records[i].choices[1]), stdin);
                    printf("Enter the new choice C: ");
                    fgets(records[i].choices[2], sizeof(records[i].choices[2]), stdin);
                    break;
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
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

void
manageData()
{
	int choice;
	
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
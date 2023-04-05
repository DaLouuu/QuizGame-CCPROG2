/*
Description: The program is a general knowledge quiz game that offers a venue
			 for people to test their general knowledge.
Programmed by: Dana Louise A. Guillarte S23A
Last modified: April 5, 2023
Version: 9
Acknowledgements:  
*/

/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Dana Louise Guillarte, DLSU ID# 12207101
*********************************************************************************************************/

#include "GuillarteDFunc.c"

int
main()
{
	/* Sets password for manage data */
	str20 adminPass = "admin123";
	
	/* Choice to start program */
	int nMenuChoice = 100;

    /* Initial number of records to be modified */
    int nRecords = 0;
    
    do
    {
        /* Ensures that the title screen won't keep popping up after invalid input */
        if (nMenuChoice == 100)
            displayMenu();
        
        /* Gets main choice from user input */
        nMenuChoice = promptChoice(1, 3);
            
        /* Determines the mode depending on the choice made by the user */
        switch (nMenuChoice)
        {
        	
        	/* Selects play game */
            case 1:

                if (nRecords == 0)
                {
                    printf("\nSorry, you can't play without records. ");
                    printf("Add records first, then try again later.\n\n");
                }
                else
                {
                    printf("\nYou have selected play mode\n\n");
                }
                nMenuChoice = 100;
                break;
            
            /* Selects manage data */
            case 2:
                printf("\nYou have selected manage data mode\n\n");
                nRecords = login(adminPass, nRecords);
                nMenuChoice = 100;
                break;
                
            /* Selects exit games */
            case 3:
                printf("\nSee you next time!");
                break;
            
            /* Invalid input */
            default:
			    printf("\n\nInvalid input. Please enter a valid choice.\n\n");
			    nMenuChoice = 100;
			break;
        }
    } while (nMenuChoice != 3);
}
/******************************************
File Name: GuillarteD.c
Author: Dana Louise A. Guillarte
Section: S23A
Last Update: April 10, 2023
The program is a general knowledge quiz game that offers a venue
for people to test their general knowledge.
Version: 2.0
Acknowledgements:
******************************************/

/************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in
studying and applying the concepts learned. I have constructed the functions and
their respective algorithms and corresponding code by myself. The program was run,
tested, and debugged by my own efforts. I further certify that I have not copied in
part or whole or otherwise plagiarized the work of other students and/or persons.
                                             Dana Louise Guillarte, DLSU ID# 12207101
*************************************************************************************/

#include "GuillarteDFunc.c"

int main()
{
    /* Sets password for manage data */
    str20 adminPass = "admin123";

    /* Initial choice to start program */
    int nMenuChoice = 0;

    /* Initial number of records to be modified */
    int nRecords = 0;

    /* Array of question records */
    struct question arrRecords[MAX_RECORDS];

    do
    {
        /* Ensures that the title screen won't keep popping up after invalid input */
        if (nMenuChoice == 0)
        {
            displayMenu();
        }

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

                    /* Pauses the program and clears the screen */
                    system("pause");
                    system("cls");
                }
                else
                {
                    system("cls");
                    
                    /* Displays the menu for the game */
                    displayPlayMenu(arrRecords, nRecords);
                }
                nMenuChoice = 0;
                break;

            /* Selects manage data */
            case 2:
                system("cls");
                printf("\nMANAGE DATA\n");
                printf("--------------------\n\n");

                /* Logs in to the manage data menu */
                nRecords = login(adminPass, nRecords, arrRecords);
                nMenuChoice = 0;
                break;

            /* Selects exit games */
            case 3:
                system("cls");
                printf("\nSee you next time!");
                break;

            /* Invalid input */
            default:
                system("cls");
                printf("\n\nInvalid input. Please enter a valid choice.\n\n");
                nMenuChoice = 0;
                break;
        }
    } while (nMenuChoice != 3);
}

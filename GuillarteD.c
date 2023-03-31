/*
Description: The program is a general knowledge quiz game that offers a venue
			 for people to test their general knowledge.
Programmed by: Dana Louise A. Guillarte S23A
Last modified: March 27, 2023
Version: 5
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
	//set password for manage data
	str20 adminPass = "admin123";
	//choice to start program
	int progChoice = 100; 
    
    do
    {
        //ensures that the title screen won't keep popping up after invalid input
        if(progChoice == 100)
            titleScreen();
        
        //gets main choice from user input
        progChoice = promptChoice(1, 3);
            
        //determines the game mode depending on the choice made by the user
        switch(progChoice)
        {
            case 1:
                printf("You have selected play mode\n");
                progChoice = 100;
                break;
            case 2:
                printf("You have selected manage date mode\n");
                //login(adminPass);
                manageData();
                progChoice = 100;
                break;
            case 3:
                printf("See you next time!");
                break;
        }
    } while(progChoice != 3);
}
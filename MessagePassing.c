/*  
    Group C
    Jeremiah Pete
    jeremiah.pete@okstate.edu
*/
#include "MessagePassing.h"

//  function to display the menu to the client side
void menu() {
    // initialize variables to handle selection of user choice
    int selection; 

    printf("Main Menu:\nPlease select an option below -\n\n");
    // display option choices to user
    printf("1. Send the data to the server\n");
    printf("2. Receive the file from the server\n");
    printf("3. Terminate\n");

    // Receive user's selection
    printf("Selection: ");
    scanf("%d", &selection);

    // upon the selection, determine which function to perform through switch
    switch(selection) {
        case 1:
            messagePass();
        case 2:
            // here is where the function to receive files will be placed
        case 3:
            printf("Program Terminated\n");
            exit(0);
        default:
            printf("Please select a proper choice!\n");
    }
}

//  function to perform message passing in Option 1 of assignment
void messagePass() {

}

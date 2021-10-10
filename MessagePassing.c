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

    printf("Main Menu:\n\nPlease select an option below -\n\n");
    // display option choices to user
    while(1) {
        printf("1. Send the data to the server\n");
        printf("2. Receive the file from the server\n");
        printf("3. Terminate\n");

        // Receive user's selection
        printf("Selection: ");
        scanf("%d", &selection);

        // upon the selection, determine which function to perform through switch
        switch (selection) {
            case 1: // go to messagePass
                messagePass();
            case 2: // receive file from server
                /* *** here is where the function to receive files will be placed *** */
            case 3: // exit program
                printf("\nProgram Terminated\n");
                exit(0);
            default: // handles when user inputs value not available
                printf("\nPlease select a proper choice!\n\n");
        }
    }
}

/*  function to perform message passing in Option 1 of assignment
    Process A will be the parent function in this case, and Process B will be the child
    returns menu when finished   */
void messagePass() {
    // initialize variables
    char message[100]; // made the size large for longer input cases
    pid_t pid = fork(); // initialize the child Process B

    // Process A writes the message the user wants to input
    if (pid > 0) {
        printf("\nWhat message would you like to send?\n");
        printf("Message: ");
        scanf("%s", message);
        wait(NULL); // wait for child process to die
        printf("\nMessage scanned!\n\n"); // used as notification of child process being killed
        return menu(); // display the menu once again when finished
    }
    else if (pid == 0) { // Process B scans the text written in Process A
        /* *** here is where the method to scan what is written in Process A should be *** */
        exit(0);
    }
    else 
        printf("Child process couldn't be created\n\n");
}

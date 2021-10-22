/*  
    Group C
    Jeremiah Pete
    jeremiah.pete@okstate.edu
*/
#include "MessagePassing.h"
#include "clientHelper.h"
#include "HunterHolstead.h" // for checking errors and encrypting messages

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
                receiveFile();
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
    int p[2]; // p[0] is for reading (Process B), p[1] is for writing (Process A)

    char message[100]; // made the size large for longer input cases
    pid_t pid; // for handling processes
    

    if (pipe(p) == -1) { // case when the pipe cannot be instantiate 
        fprintf(stderr, "Pipe Couldn't be Made");
        exit(2);
    }
    
    pid = fork(); // initialize the child Process B
    // pid > 0 is parent process, pid == 0 is child process
    if (pid > 0) { // Process A writes the message the user wants to input
        close(p[0]); // close reading end of pipe

        printf("\nWhat message would you like to send?\n");
        printf("Message: ");
        scanf("%s", message); // get user input

        write(p[1], message, sizeof(message)); // write the message to the pipe and close the write end of pipe
        close(p[1]); // close writing end of pipe

        wait(NULL); // wait for child process to die
    }
    else if (pid == 0) { // Process B reads the text written in Process A
        close(p[1]); // close writing end
        // read the message made in Process A from the pipe 
        read(p[0], message, sizeof(message));
        printf("\nMessage received is: %s\n\n", message); // test to make sure IPC functions properly
        /* *** here is where the method to scan what is written in Process A should be *** */
        close(p[0]); // close reading end

        exit(0); // kill child process at the end
    }
    else // if child process can't be created
        printf("Child process couldn't be created\n\n");
    return menu(); // display the menu once again when finished
}

/*  function to put together everything that should take place in option 2 */
void receiveFile() {
    // connect to server
    clientStarter();
    return menu();
}
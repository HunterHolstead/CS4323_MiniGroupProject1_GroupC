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
    int q = Random(); // for encryption
    int p[2]; // p[0] is for reading (Process B), p[1] is for writing (Process A)

    char message[200]; // made the size large for longer input cases

    getMessage(message); // retrieve message user wants to send
    char* temp = lowerCase(message, temp); // make message lowercase for checking
    printf("Lower: %s\n", temp);

    pid_t pid; // for handling processes
    
    if (pipe(p) == -1) { // case when the pipe cannot be instantiate 
        fprintf(stderr, "Pipe Couldn't be Made");
        exit(2);
    }

    pid = fork(); // initialize the child Process B
    // pid > 0 is parent process, pid == 0 is child process
    if (pid > 0) { // Process A writes the message the user wants to input
        close(p[0]); // close reading end of pipe

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
        checkWord(temp);
        printf("\nEncrypting...\n");
        getEncryption(message, q); // encrypt string
        printf("\nDecrypting...\n");
        getDecryption(message, q); // decrypt string
        close(p[0]); // close reading end

        printf("\n"); // formatting
        exit(0); // kill child process at the end
    }
    else // if child process can't be created
        printf("Child process couldn't be created\n\n");
    return menu(); // display the menu once again when finished
}

/*  function to get message input from user
    params: char message[] (initialized in menu function)
    returns: stdin string message */
char* getMessage(char message[]) {
    printf("\nWhat message would you like to send?\n");
    printf("Message: ");
    scanf(" %[^\n]", message);
    return message;
}

/*  function to make message input all lowercase in order for checkWord to work
    params: char message[] 
    returns: all lowercase version of message (temp) */
char* lowerCase(char message[], char temp[]) {
    for (int i = 0; i < strlen(message) + 1; i++) {
        temp[i] = tolower(message[i]);
    }

    return temp;
}

char* getEncryption(char message[], int q) {
    printf("The value of q is %d\n", q);
    char* messageEncrypt = Encrypt(message, strlen(message) + 1, q);
    printf("The encrypted string - %s\n\n", messageEncrypt);
    sleep(3);

    return messageEncrypt;
}

char* getDecryption(char message[], int q) {
    char* messageDecrypt = Decrypt(message, strlen(message) + 1, q);
    printf("The decrypted string - %s\n\n", messageDecrypt);
    sleep(3);
    return messageDecrypt;
}

// test case 
int main() {
    menu();
    return 0;
}
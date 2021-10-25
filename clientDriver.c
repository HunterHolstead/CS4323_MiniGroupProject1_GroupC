//  Group C client driver
// to compile use command gcc -o client clientDriver.c MessagePassing.c -lpthread
#include "MessagePassing.h"
#include "clientHelper.h"

/**
 * Arguments:
 *      void
 * Description:
 *      main driver file aka client that runs the program
 * Return type:
 *      void
*/
int main() {
    int socket_client = clientStarter();

    while (1) {
        int threadNumber = 0;
        recv(socket_client, &threadNumber, sizeof(threadNumber), 0);
        if(threadNumber < 3){ 
            printf("DISPLAY MENU\n");
            menu(socket_client); // begin by displaying the menu to the user 
        } else {
            printf("Unable to help client - Threads are full.\n");
            break;
        }
    }

    close(socket_client);
    exit(1);
    return 0;
}
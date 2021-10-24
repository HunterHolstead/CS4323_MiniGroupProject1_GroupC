//  Group C client driver

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "MessagePassing.h"
#include "clientHelper.h"
#include "HunterHolstead.h"
//#include "ProcessB_ThreadManagement.c"
//#include "clientDriver.c"
//#include "serverDriver.c"

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

    while (1)
    {

        int threadNumber = 0;
        recv(socket_client, &threadNumber, sizeof(threadNumber), 0);
        if(threadNumber < 3){ 
            /* code for program */
            
            printf("DISPLAY MENU\n");
            //menu(); // begin by displaying the menu to the user - not working "undefined reference"
        } else {
            printf("Unable to help client - Threads are full.\n");
            break;
        }
    }

    close(socket_client);
    exit(1);
    return 0;
}

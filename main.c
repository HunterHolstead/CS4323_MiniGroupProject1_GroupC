//  Group C Driver File
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "MessagePassing.c"
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

    while (1)
    {
        /* code for program */
        menu(); // begin by displaying the menu to the user
    }

    close(socket_client);

    return 0;
}

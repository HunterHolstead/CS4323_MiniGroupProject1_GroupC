#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 4444

/**
 * Arguments:
 *      int
 *      const char
 *      int
 * Description:
 *      uses given int to see if an error happened by seeing if value is negative. 
 *      prints out given error message if an error happened
 * Return type:
 *      void
*/
void errorCheck (int dataToCheck, const char *errorMessage, int socket_client){
    if (dataToCheck < 0){
        printf("%s\n", errorMessage);
        close(socket_client);
        exit(1);
    }
}

/**
 * Arguments:
 *      void
 * Description:
 *      creates and initializes all of the startup tasts for the client
 *      returns the value of the client socket 
 * Return type:
 *      int
*/
int clientStarter(){

    int socket_client;
    
    struct sockaddr_in address_server;
    
    //initialize client socket
    socket_client = socket(AF_INET, SOCK_STREAM,0);

    errorCheck(socket_client, "Connection error.\n", socket_client);

    memset(&address_server, '\0', sizeof(address_server));

    //initialize server struct
    address_server.sin_family = AF_INET;
    address_server.sin_port = htons(PORT);
    address_server.sin_addr.s_addr = INADDR_ANY;

    //connect client socket to server
    errorCheck(connect(socket_client, (struct sockaddr*) &address_server, sizeof(address_server)), "Failed to connect to server.\n", socket_client);

    return socket_client;
}
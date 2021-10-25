//  Group C server driver
// to compile use command gcc -o server serverDriver.c -lpthread
#include <pthread.h>
#include "clientHelper.h"
#include "HunterHolstead.h"

// file uses main method of MiniProject_Cook_Isabell.c

/**
 * Arguments:
 *      void
 * Description:
 *      server process that uses a threadpool to handle client interactions
 * Return type:
 *      void
*/
void main(){
    int socket_server;
    int socket_client;
    socklen_t address_size;
    struct sockaddr_in address_server;
    struct sockaddr_in address_client;
    int ret;

    //initialize/create threadPool
    for(int i = 0; i < THREAD_COUNT; i++){
        pthread_create(&threadPool[i], NULL, threadTask, NULL);
        printf("Thread %d has been created\n", i+1);
    }


    //create server socket
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    errorCheck(socket_server, "Error in creating server socket\n", socket_client);

    //initialize server struct
    address_size = sizeof(struct sockaddr_in);
    address_server.sin_family = AF_INET;
    address_server.sin_port = htons(PORT);
    address_server.sin_addr.s_addr = INADDR_ANY;

    //bind server to port
    errorCheck(bind(socket_server, (struct sockaddr*) &address_server, sizeof(address_server)), "Binding error\n", socket_client);

    //Listen for connections
    errorCheck(listen(socket_server, CLIENT_QUEUE+THREAD_COUNT), "Listen Queue Full Error\n", socket_client);

    //continueously listen and add clients to a queue
    while(1){
        
        printf("Waiting for clients to connect.\n");
        
        socket_client = accept(socket_server, (struct sockaddr*) &address_client, &address_size);
        errorCheck(socket_client, "Failed to accept client.\n", socket_client);
        printf("Connected\n");

        //add client address to queue to have threads deal with
        addQueue(socket_client);

        //send client a message of the thread number it is using
        printf("\n \nThreads in Use %d \n Queue Count is %d\n\n", threadsInUse, queueCount);
        send(socket_client, &totalClients, sizeof(totalClients), 0);
        totalClients++;
    }
    close(socket_server);
}
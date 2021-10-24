
//  Group C server driver
/**
 * Group C
 * Isabell Cook
 * Icook@okstate.edu
*/

//in order to compile: "gcc -o server MiniProject_Cook_Isabell.c -lpthread"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 4444

//Method declarations
void addQueue(int address_client);
void errorCheck (int dataToCheck, const char *errorMessage, int socket_client);
void destroyThread();
int removeFromQueue();
void * threadTask();
void *threadHandleClient (int *address_client);

//initialize a mutex lock for thread synchronization
pthread_mutex_t lockThread;
pthread_mutex_t lockQueue;

//define a number of threads to create
#define THREAD_COUNT 3
#define CLIENT_QUEUE 50

//declare a Queue of clients with a queue limit of 50-random default value
int clientQueue[CLIENT_QUEUE] = {0};
//number of clients waiting
int queueCount = 0;

//Thread Pool with "THREAD_COUNT" threads
pthread_t threadPool[THREAD_COUNT];
//Number of active threads
int threadsInUse = -1;
//clients connected to server
int totalClients = 0;

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
        printf("\n \nThreads in Use %d \n Queue Count is%d\n\n", threadsInUse, queueCount);
        send(socket_client, &totalClients, sizeof(totalClients), 0);
        totalClients++;
    }
    close(socket_server);
}

/**
 * Arguments:
 *      int
 *      const char
 * Description:
 *      uses given int to see if an error happened by seeing if value is negative. 
 *      prints out given error message if an error happened
 * Return type:
 *      void
*/
void errorCheck (int dataToCheck, const char *errorMessage, int socket_client){
    if (dataToCheck < 0){
        printf("%s\n", errorMessage);
        destroyThread();
        close(socket_client);
        close(dataToCheck);
        exit(1);
    }
}

/**
 * Arguments:
 *      void
 * Description:
 *      Used for closing program. Correctly exits all multithread related processes
 * Return type:
 *      void
*/
void destroyThread(){
    for(int i = 0; i < THREAD_COUNT; i++){
        if (pthread_join(threadPool[i], NULL) != 0){
            printf("Thread %d was unable to be destroyed.\n", i+1);
        }   
        printf("Thread %d has been Destroyed\n", i+1);
    }
    pthread_mutex_destroy(&lockThread);
    pthread_mutex_destroy(&lockQueue);
}

/**
 * Arguments:
 *      void
 * Description:
 *      This is where each thread gets its directions after being created. 
 *      This function takes a client off the queue, and if it is an acutal client it send the thread to the 
 *          client handler function
 * Return type:
 *      void
*/
void * threadTask(){
    //continuously loop, thread is not destroyed but reused after each interaction
    while(1){
        //remove said client from queue
        int client = removeFromQueue();

        //if there is a client take care of it
        if (client != 0){
            //increase active thread count - lock so nothing else can change thread at the same time
            pthread_mutex_lock(&lockThread);
                threadsInUse++;
            pthread_mutex_unlock(&lockThread);

            printf("Client assigned to Thread\n");

            //perform client tasks
            threadHandleClient(&client);

            //decrease active thread count - lock so nothing else can change thread at the same time
            pthread_mutex_lock(&lockThread);
                threadsInUse--;
            pthread_mutex_unlock(&lockThread);
        }
        
    }
}

/**
 * Arguments:
 *      int *address_client
 * Description:
 *      This function is where the server interacts with the client
 *      Uses argument to close client socket when finished.
 * Return type:
 *      void
*/
void *threadHandleClient (int *socket_client){
    //DEBUG LINE: busy wait 
    while(1){
        pause();
    }
    //close client when done:
    close(*socket_client);
    printf("closing connection\n");
}

/**
 * Arguments:
 *      int socket_client
 * Description:
 *      adds the passed in client to the queue
 * Return type:
 *      void
*/
void addQueue(int socket_client){
    //Lock out other processes from adding requests to queue
    pthread_mutex_lock(&lockQueue);
        //add request to Queue
        clientQueue[queueCount] = socket_client;
        queueCount++;
    pthread_mutex_unlock(&lockQueue);
    //Now that the request has been added other processes can access this section - unlock

    printf("Client added to Queue\n");
}

/**
 * Arguments:
 *      void
 * Description:
 *      removes the first index of the clientQueue to return.
 *      Moves the rest of the clients up in the queue.
 * Return type:
 *      int
*/
int removeFromQueue(){
    int address_client = 0;

    pthread_mutex_lock(&lockQueue);
        address_client = clientQueue[0];
        if(clientQueue[0] != 0){
            for (int i = 0; i < queueCount; i++){
                clientQueue[i] = clientQueue[i+1];
            }
            queueCount--;
            printf("Client Removed from Queue\n");
        }
    pthread_mutex_unlock(&lockQueue);
    return address_client;
}

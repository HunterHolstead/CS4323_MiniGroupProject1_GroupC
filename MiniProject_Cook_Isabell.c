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
void addToQueue(int client);
void errorCheck (int dataToCheck, const char *errorMessage);
void removeFromQueue();
void createThreads();
void destroyThread();
void *assignThread();
void messageClientToPerformTask(int socketclient);


//declare a Queue of clients
int clientQueue[50];
int queueCount = 0;

//initialize a mutex lock for thread synchronization
pthread_mutex_t mutexLock;
//initialize a condition for signaling when a task is created
pthread_cond_t signalCondition;

//define a number of threads to create
#define THREAD_COUNT 3

//Thread Pool
pthread_t threadPool[THREAD_COUNT];

int socket_server;
int socket_client;

/**
 * Arguments:
 *      void
 * Description:
 *      server process that uses a threadpool to handle client interactions
 * Return type:
 *      void
*/
void main(){
    //int socket_server;
    //int socket_client;
    int address_size;
    struct sockaddr_in address_server;
    struct sockaddr_in address_client;

    //create threadPool
    createThreads();

    //create server socket
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    errorCheck(socket_server, "Error in connecting to client socket\n");

    //initialize server struct
    address_server.sin_family = AF_INET;
    address_server.sin_port = htons(PORT);
    address_server.sin_addr.s_addr = INADDR_ANY;

    //bind server to port
    errorCheck(bind(socket_server, (struct sockaddr*) &address_server, sizeof(address_server)), "Binding error\n");

    //Listen for connections
    errorCheck(listen(socket_server, *clientQueue), "Listen error\n");

    while(1){
        printf("Waiting for clients to connect.\n");
        address_size = sizeof(struct sockaddr_in);
        //accept clients
        socket_client = accept(socket_server, (struct sockaddr*)&address_client, (socklen_t*)&address_size);
        errorCheck(socket_client, "Failed to accept client.\n");
        printf("Connected\n");

        //queue client
        int clientPointer = malloc(sizeof(int));
        clientPointer = socket_client;
        addToQueue(clientPointer);

        if(queueCount > 3){
            printf("Waiting for a thread to free up.\n");
        }
    }
    close(socket_client);
    close(socket_server);
    destroyThread();

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
void errorCheck (int dataToCheck, const char *errorMessage){
    if (dataToCheck < 0){
        printf("%s\n", errorMessage);
        destroyThread();
        close(socket_client);
        close(socket_server);
        exit(1);
    }
}

/**
 * Arguments:
 *      int client
 * Description:
 *      Adds a clients request to a the bottom of a list "queue"
 * Return type:
 *      void
*/
void addToQueue(int client){
    //Lock out other processes from adding requests to queue
    pthread_mutex_lock(&mutexLock);
    //add request to Queue
    clientQueue[queueCount] = client;
    queueCount++;
    printf("Client added to queue\n");
    //Now that the request has been added other processes can access this section - unlock
    pthread_mutex_unlock(&mutexLock);
    //signal to server that a queue has been added
    pthread_cond_signal(&signalCondition);
}

/**
 * Arguments:
 *      void
 * Description:
 *      Removes the top [0] index request from queue, and resets queues to start at [0] 
 * Return type:
 *      void
*/
void removeFromQueue(){
    //is called from inside mutex locks, so they are not needed here
    //Recenter requests in queue
    for (int i = 0; i < queueCount; i++){
        clientQueue[i] = clientQueue[i+1];
    }
    queueCount--;
}

/**
 * Arguments:
 *      void
 * Description:
 *      Used to create a specified amount of threads to make up the thread pool.
 *      Should only be called on program start up.
 * Return type:
 *      void
*/
void createThreads(){
    //initialize lock and condition
    pthread_mutex_init(&mutexLock, NULL);
    pthread_cond_init(&signalCondition, NULL);

    //initialize/create threadPool
    for(int i = 0; i < THREAD_COUNT; i++){
        if (pthread_create(&threadPool[i], NULL, &assignThread, NULL) != 0){
            printf("Thread %d was unable to be created.\n", i+1);
        }
        printf("Thread %d has been created\n", i+1);
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
    pthread_cond_destroy(&signalCondition);
    pthread_mutex_destroy(&mutexLock);
}

/**
 * Arguments:
 *      void
 * Description:
 *      Thread gets assigned and preforms a task from the task queue or waits until there is a task
 *      to be preformed. 
 * Return type:
 *      void
*/
void *assignThread(){
    while(1){
        //Lock out other processes from adding requests to queue
        pthread_mutex_lock(&mutexLock);
        //keep threads from searching for requests when there are none
        while (queueCount == 0){
            pthread_cond_wait(&signalCondition, &mutexLock);
        }

        int client = clientQueue[0];
        removeFromQueue();

        //Now that the request has been added other processes can access this section - unlock
        pthread_mutex_unlock(&mutexLock);
        messageClientToPerformTask(client);
    }
}

/**
 * Arguments:
 *      int socketclient
 * Description:
 *      uses the given socket to send messages to the client to preform tasks
 * Return type:
 *      void
*/
void messageClientToPerformTask(int socketclient){
    /*
    Thread T implementation 
    or
    send message to client to preform task
    */
   sleep(5);
   printf("Perform some task\n");
}
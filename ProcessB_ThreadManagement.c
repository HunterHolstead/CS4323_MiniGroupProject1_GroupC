// Author: Kyle Kentner
// Date: 10/19/2021
// Program: manageThreads, which creates Thread T for Process B to facilitate encryption and client/server communications

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "HunterHolstead.h"

// Defining a struct for the word to encrypt (needed in pthread_create)
struct theMessage {
	// Message variables
	char* msg; // The message to encrypt
	int size; // The size of the message
	int key; // The key q which will be used
	
	// Thread variable
	pthread_t* mThread; // Pointer to Thread T; used to put it to sleep
};

// Create a pthread mutex which will be used by Thread T; this should be initialized prior to calling manageThreads
pthread_mutex_t mutex;

// Flag to reuse Thread T
int reuse = 0;
int threadBusy = 0;

// Based on add_threads.c POSIX demonstration by Dr. Shital Joshi
void manageThreads(pthread_t** ptrThreadT, char* msgToEncrypt, int msgSize, int encryptKey);

// Function for Thread T to run (string, size, and key sent via struct)
char* EncryptAndSend(struct theMessage* encryptMsg) {
	struct theMessage myMsg = *encryptMsg;

	// Dereference encryptMsg's members to get encryptString, size, and q
	char* stringToEncrypt = myMsg.msg;
	int msgSize = myMsg.size;
	int msgKey = myMsg.key;
	
	// Call Encrypt to get the encrypted string
	const char* encryptedString = Encrypt(stringToEncrypt, msgSize, msgKey);
	
	// TODO: Send the string to the server and receive the filename in return
	char* fileName = (char*) 0xDEADBEEF; // = sendMessageToServer() // This value will be returned by the thread once Process B terminates
	
	// Free the heap memory associated with the struct
	free(encryptMsg);

	// TODO: Disconnect from the server and go to sleep
	// Wait for Process B to unlock the mutex before proceeding
	printf("Locking thread...\n");
	threadBusy = 0;
	pthread_mutex_lock(&mutex);
	printf("Thread unlocked\n");	

	return fileName;
}

// Make a function which performs the add_thread operation iff Thread T does not already exist
//	 Send the thread to sleep after receiving response from server
//	 Send the signal for the thread to wake up after initial creation
void manageThreads(pthread_t** ptrThreadT, char* msgToEncrypt, int msgSize, int encryptKey) {
	// Create a pointer to a theMessage struct and initialize
	struct theMessage* args = (struct theMessage*) malloc(sizeof(char*) + sizeof(int) + sizeof(int) + sizeof(pthread_t*));
	args->msg = msgToEncrypt;
	args->size = msgSize;
	args->key = encryptKey;
	
	// The "global" Thread T pointer, which either needs to be created or awoken
	args->mThread = NULL;

	// If Thread T has not yet been created, ptrThreadT should be null
	if (*ptrThreadT == NULL) {
		// Allocate heap memory for a persistent pthread_t
		args->mThread = (pthread_t*) malloc(sizeof(pthread_t));
		
		// Set ptrThreadT to this heap address to pass the pointer back by reference (alias)
		*ptrThreadT = args->mThread;
		printf("New thread: %p\n", args->mThread);
		threadBusy = 1;		

		// Create Thread T, which will use the encryption function as its main function
		if (pthread_create(args->mThread, NULL, (void*) &EncryptAndSend, args) != 0) {
			printf("Error: Unable to create Thread T.\n");
		}
	}
	else { // Thread T has been created
		// Currently entering busy wait until Thread T is asleep (let Thread T complete its work)
		while(threadBusy);

		// Thread T is asleep; wake it up
		pthread_mutex_unlock(&mutex);

		// Set mThread to Thread T's pointer
		args->mThread = *ptrThreadT;
		
		// Reuse thread
		// printf("Trying it...\n");
		// sleep(3);

		// Reset the lock and set threadBusy back to 1
		threadBusy = 1;
		
		// Reuse Thread T by sending its pointer back to pthread_create (recycle the resources)
		if (pthread_create(args->mThread, NULL, (void*) &EncryptAndSend, args) != 0) {
			printf("Error: Unable to create Thread T.\n");
		}

		// Validation that this is the same thread as before
		printf("Existing thread: %p\n", args->mThread);
	}
}

//	Commented out main function for compiling (Jeremiah)
// Dummy driver function
int main() {
	// Pointer to the filename returned by the server
	char* serverFileName;
	
	// Declare a pointer to Thread T
	pthread_t* ptrThreadT = NULL;
	
	// Run-time initialization of the pthread mutex with default attributes
	if (pthread_mutex_init(&mutex, NULL) != 0) {
		return 1;
	}
	
	// Lock the mutex initially; disallow the thread from returning the file name until Process B terminates
	pthread_mutex_lock(&mutex);
	
	// Hunter: The following method will test the encryption method
	const char testString[] = "MEET YOU IN THE PARK";
	size_t sizeOfArray = sizeof(testString)/sizeof(testString[0]);
	char* heapString = (char*) malloc(sizeOfArray);
	strcpy(heapString, testString);
	printf("String: %s\n", heapString);
	printf("Pointer: %p\n", heapString);

	// Test manageThreads (ptrThreadT passed back by reference)
	manageThreads(&ptrThreadT, heapString, sizeOfArray, 3);

	// Test case in which Thread T's pointer has been initialized
	manageThreads(&ptrThreadT, heapString, sizeOfArray, 3);
	
	// Unlock the mutex to return the filename for the encrypted message
	printf("Unlocking mutex...\n");
	pthread_mutex_unlock(&mutex);

	// Get the filename (address) from Thread T and destroy the thread (this should occur prior to terminating Process B)
	pthread_join(*ptrThreadT, (void**) &serverFileName);
	printf("Server file address: %p\n", serverFileName);
	
	// Free the heap memory associated with the thread pointer
	printf("Freeing memory for pointer %p...\n", ptrThreadT);
	free(ptrThreadT);

	// Free the heap memory associated with the string pointer
	printf("Freeing memory for pointer %p...\n", heapString);
	free(heapString);
	
	// Destroy the lock
	if (pthread_mutex_destroy(&mutex) != 0) {
		return 1;
	}
	
	return 0;
}
//
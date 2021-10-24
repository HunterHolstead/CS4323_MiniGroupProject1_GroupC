// Author: Kyle Kentner
// Date: 10/19/2021
// Program: manageThreads, which creates Thread T for Process B to facilitate encryption and client/server communications

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_FNAME 64

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

// Get a unique filename for saving (uses Random from HunterHolstead.h)
char* getFileName(const char* strPrefix) {
	// Allocate space for the new filename and apply the prefix
	char* fileName = (char*) malloc(sizeof(char) * MAX_FNAME);
	strcpy(fileName, strPrefix);
	
	// Skip over the initialized characters
	int i = 0;
	while (fileName[i] != '\0') {
		i++;
	}
	
	// Append random letters to the end of the filename
	while (i < MAX_FNAME - 4) {
		// Get a random letter
		fileName[i] = (char) (65 + rand() % 26);
		i++;
	}

	// Append the file extension
	fileName[i++] = '.';
	fileName[i++] = 't';
	fileName[i++] = 'x';
	fileName[i] = 't';
	
	return fileName;
}


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

// Function for Thread T to run (string, size, and key sent via struct)
char* SendAndDecrypt(struct theMessage* decryptMsg) {
	struct theMessage myMsg = *decryptMsg;

	// Dereference encryptMsg's members to get encryptString, size, and q
	char* stringToDecrypt = myMsg.msg;
	int msgSize = myMsg.size;
	int msgKey = myMsg.key;
	
	// Call Encrypt to get the encrypted string
	const char* decryptedString = Decrypt(stringToDecrypt, msgSize, msgKey);
	
	// TODO: Send the string to the server and receive the filename in return
	char* fileName = (char*) 0xDEADBEEF; // = sendMessageToServer() // This value will be returned by the thread once Process B terminates
	
	// Free the heap memory associated with the struct
	free(decryptMsg);

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
		if (pthread_create(args->mThread, NULL, (void*) &SendAndDecrypt, args) != 0) {
			printf("Error: Unable to create Thread T.\n");
		}

		// Validation that this is the same thread as before
		printf("Existing thread: %p\n", args->mThread);
	}
}
//
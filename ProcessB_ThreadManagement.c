#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Based on add_threads.c POSIX demonstration by Dr. Shital Joshi
void* manageThreads(void* ptrThreadT);

// Test function; the "main" function for Thread T
//	Calls manageThreads again and checks if Thread T exists and (if so) if it is asleep
void* fnName(void* ptrThreadT) {
	// Call manageThreads using the pointer sent by the thread
	manageThreads(ptrThreadT);
}

// Make a function which performs the add_thread operation iff Thread T does not already exist
//	 Send the thread to sleep after receiving response from server
//	 Send the signal for the thread to wake up after initial creation
void* manageThreads(void* ptrThreadT) {
	pthread_t* threadTPtrOG = NULL;
	
	// If Thread T has not yet been created, ptrThreadT should be null
	if (ptrThreadT == NULL) {
		// Allocate heap memory for a persistent pthread_t
		threadTPtrOG = (pthread_t*) malloc(sizeof(pthread_t));
		
		// Create Thread T
		printf("Creating a new thread:\n");
		if (pthread_create(threadTPtrOG, NULL, &fnName, (void*) threadTPtrOG) != 0) {
			printf("Error: Unable to create Thread T.\n");
		}
	}
	else { // Thread T has beend created
		// TODO: Check if Thread T is awake
		printf("Reusing an old thread:\n");
		
		//threadT = *((pthread_t*) ptrThreadT); // Dereference a cast of ptrThreadT to pthread_t*
		
		return ptrThreadT;
	}
	
	// Get the thread's return value and destroy the thread
	void* threadTPtr;
	pthread_join(*((pthread_t*) ptrThreadT), &threadTPtr);
	
	// Make sure the address is the same as the initial address
	printf("OG: %p\nFinal: %p\n", threadTPtrOG, threadTPtr);
	
	// Free the heap memory associated with the pointer
	free(threadTPtrOG);
	threadTPtrOG = NULL;
	threadTPtr = NULL; // The other pointer should be an alias
	ptrThreadT = NULL; // ...As should this pointer
	
	return NULL;
}

int main() {
	// Test manageThreads
	manageThreads(NULL);
	
	return 0;
}
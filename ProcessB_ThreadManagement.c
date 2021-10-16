// Author: Kyle Kentner
// Date: 10/15/2021
// Program: manageThreads, which creates Thread T for Process B to facilitate encryption and client/server communications

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Based on add_threads.c POSIX demonstration by Dr. Shital Joshi
void* manageThreads(void* ptrThreadT);

// Test function; the "main" function for Thread T
//	Calls manageThreads again and checks if Thread T exists and (if so) if it is asleep
void* fnName(void* ptrThreadT) {
	// Call manageThreads using the pointer sent by the thread
	printf("Thread T sending its own pointer to a new manageThreads call...\n");
	manageThreads(ptrThreadT);
}

// Make a function which performs the add_thread operation iff Thread T does not already exist
//	 Send the thread to sleep after receiving response from server
//	 Send the signal for the thread to wake up after initial creation
void* manageThreads(void* ptrThreadT) {
	// The "global" Thread T pointer, which either needs to be created or awoken
	pthread_t* g_ptrThreadT = NULL;
	
	// If Thread T has not yet been created, ptrThreadT should be null
	if (ptrThreadT == NULL) {
		// Allocate heap memory for a persistent pthread_t
		g_ptrThreadT = (pthread_t*) malloc(sizeof(pthread_t));
		
		// Create Thread T, which will use the encryption function as its main function
		printf("Creating a new thread...\n");
		if (pthread_create(g_ptrThreadT, NULL, &fnName, (void*) g_ptrThreadT) != 0) {
			printf("Error: Unable to create Thread T.\n");
		}
	}
	else { // Thread T has been created
		// TODO: Check if Thread T is awake
		// For now, this is executed by the thread itself, and the thread returns its own pointer
		printf("Returning Thread T to the calling function...\n");
		return ptrThreadT;
	}
	
	// Get the thread's return value and destroy the thread
	void* ptrCheckThreadT;
	pthread_join(*g_ptrThreadT, &ptrCheckThreadT);
	
	// TESTING VALIDATION: Make sure the address is the same as the initial address
	printf("Global: %p\nReturned by Thread T: %p\n", g_ptrThreadT, ptrCheckThreadT);
	
	// Set other pointers to NULL
	ptrCheckThreadT = NULL; // This pointer is an alias
	ptrThreadT = NULL; // ...As is this pointer
	
	// TODO: Determine if g_ptrThreadT needs to be passed back via reference instead
	return g_ptrThreadT;
}

/*	Commented out main function for compiling (Jeremiah)
// Dummy driver function
int main() {
	// Test manageThreads
	pthread_t* ptrThreadT = manageThreads(NULL);
	
	// Free the heap memory associated with the pointer
	printf("Freeing memory for pointer %p...\n", ptrThreadT);
	free(ptrThreadT);
	return 0;
}
*/
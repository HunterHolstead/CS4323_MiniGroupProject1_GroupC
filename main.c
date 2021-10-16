//  Group C Driver File
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "MessagePassing.h"
#include "clientHelper.h"
#include "HunterHolstead.h"
#include "ProcessB_ThreadManagement.c"

/**
 * Arguments:
 *      void
 * Description:
 *      main driver file aka client that runs the program
 * Return type:
 *      void
*/
int main() { 
    // this is just a test to show the progress made so far. Final program will not appear this way 
    // and will tie everything included together

    // The following lines test the Random method for generating a q
	int q = Random();
	printf("%s\n", "The value for q is:");
	printf("%d\n", q);

	//the following method will test the MapCharToP method
	char testC = 'C';
	int testP = MapCharToP(testC);
	printf("%s\n", "The char mapped value for p is:");
	printf("%d\n", testP);
	
	//the following method will test the MapPToChar method
	char testChar = MapPToChar(testP);
	printf("%s\n", "The p value mapped to the char:");
	printf("%c\n", testChar);
	
	//the following method will test the encryption method
	char testString[] = "MEET YOU IN THE PARK";
	size_t sizeOfArray = sizeof(testString)/sizeof(testString[0]);
	const char *testEncrypt = Encrypt(testString, sizeOfArray, 3);
	printf("%s\n", "The encrypted String:");
	printf("%s\n", testEncrypt);
	
	//the following method will test the decryption method
	const char *testDecrypt = Decrypt(testEncrypt, sizeOfArray, 3);
	printf("%s\n", "The decrypted String:");
	printf("%s\n", testDecrypt);

    printf("\n\n"); // separate the test functions

    // Test manageThreads
	pthread_t* ptrThreadT = manageThreads(NULL);
	
	// Free the heap memory associated with the pointer
	printf("Freeing memory for pointer %p...\n", ptrThreadT);
	free(ptrThreadT);

    int socket_client = clientStarter();
    close(socket_client);

    printf("\n\n"); // separate test functions

    while (1)
    {
        /* code for program */
        menu(); // begin by displaying the menu to the user
    }


    return 0;
}

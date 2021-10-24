/*  Jeremiah Pete
    Header file for my functions    */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// define functions
void menu(); // menu function at the beginning of program
void messagePass(); // to handle message passing requirements
void receiveFile(); // function to handle option 2

int accessPBThreadManage(char message[]); // access the necessary info from Kyle's file

char* getMessage(char message[]); // retrieve user message 
char* lowerCase(char message[], char temp[]); // convert message to all lower case
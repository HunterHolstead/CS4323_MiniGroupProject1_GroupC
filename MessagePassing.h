/*  Jeremiah Pete
    Header file for my functions    */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// define the file to read/write from
#define MESSAGE "messageInfo.txt"

// define functions
void menu(); // menu function at the beginning of program
void messagePass(); // to handle message passing requirements
void receiveFile(); // function to handle option 2

char* getMessage(char message[]);
char* lowerCase(char message[], char temp[]);
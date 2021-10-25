//Hunter Holstead
//Operating Systems Mini Group Project Group C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h> // included for compilation (Jeremiah)
#define SIZE 1024 //size of the data sent through file
#define MAX_FNAME 64 //Kyle

char** generateDictionary(int wordslength, int listlength);
void freeArray(char** dictionary, int listlength);
char *invalidWord(char *wrongWord);
char *Encrypt(char *encryptString, int size, int q);
char *Decrypt(char *decryptString, int size, int q);

int Random()
{
	time_t t;
	
	srand((unsigned) time(&t));
	
	int random = (rand() % 20)+1;
	
	//print statement for testing purposes
	/*printf("%s\n", "Random Number generated:");
	printf("%d\n", random);*/
	
	return random;
}

//Kyle
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

int MapCharToP(char c)
{
	//Array that maps char to int p
	char lookup[53] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
		'S','T','U','V','W','X','Y','Z',' ','a','b','c','d','e','f','g','h','i',
		'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	};
	
	
	for(int i = 0; i < 53; i = i + 1)
	{
		if(c == lookup[i])
		{
			
			int p = i;
			
			//print statement for testing purposes
			/*printf("%s\n", "char c is equal to p value:");
			printf("%d\n", p);*/
			
			return p;
		}
	}
	
	return 0;
}

char MapPToChar(int p)
{
	//Array that maps char to int p
	char lookup[53] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
		'S','T','U','V','W','X','Y','Z',' ','a','b','c','d','e','f','g','h','i',
		'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	};
	
	char mappedChar = lookup[p];
	
	return mappedChar;
}

char *Encrypt(char *encryptString, int size, int q)
{
	printf("%s\n", "String before Encryption:");
	printf("%s\n", encryptString);
	
	size = size -1;
	printf("%s\n", "The size of the array:");
	printf("%d\n", size);
	
	int encryptValues[size];
	int p;
	
	for(int i = 0; i < size; i++)
	{
		p = MapCharToP(encryptString[i]);
		encryptValues[i] = (p+q) % 54;
		encryptString[i] = MapPToChar(encryptValues[i]);
	}
	
	return encryptString;
}

char *Decrypt(char *decryptString, int size, int q)
{
	printf("%s\n", "String before Decryption:");
	printf("%s\n", decryptString);
	
	size = size -1;
	printf("%s\n", "The size of the array:");
	printf("%d\n", size);
	
	int decryptValues[size];
	int p;
	
	for(int i = 0; i < size; i++)
	{
		p = MapCharToP(decryptString[i]);
		decryptValues[i] = (p - q) % 54;
		decryptString[i] = MapPToChar(decryptValues[i]);
	}

	return decryptString;
}

// Compare strings without case sensitivity
int strCompare(char* a, char* b, int flag) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			// Check if either character is lowercase, in which case there may be a case discrepancy
			if (a[i] > 96 && a[i] < 123) {
				// a[i] is lowercase
				if (b[i] + 32 != a[i]) {
					return 0; // Not the same letter
				}
			}
			else if (b[i] > 96 && b[i] < 123) {
				// b[i] is lowercase
				if (a[i] + 32 != b[i]) {
					return 0; // Not the same letter
				}
			}
			else {
				return 0; // Not the same letter
			}
		}		

		i++;
	}
	
	// If here, no discrepancies were found; check that the strings are the same length
	if (a[i] < 32 && b[i] < 32) {
		return 1; // Terminate at same index; equivalent
	}
	else {
		printf("a: %s, b: %s\n", a, b);
		return 0;
	}
}

int checkWord(char *test)
{
	int listlength = 58122;
	int wordslength = 45; //Longest possible word in english dictionary is 45 letters long
	
    char** dictionary = generateDictionary(listlength, wordslength);
	//char test[] = "apple";//*word;
	char* result;
	int intResult;
	int isIn;

    for(int i=0;i<58122;i++)
	{
		//result = strstr(dictionary[i],test);
		intResult = strCompare(dictionary[i], test, i);		
		if(intResult)
		{
			isIn=1;
			break;
		}
		else
		{
			isIn=0;
		}
			
    }
	
		if(isIn)
		{
			printf("%s\n","It is in the dictionary");
		}
		else
		{
			printf("%s\n","It is not in the dictionary");
			//char *correction = invalidWord(test);
			//printf("%s\n","The corrected word is:");
			//printf("%s", correction);
			
		}

    freeArray(dictionary, listlength);
	
	return isIn;
}

/*
char *invalidWord(char *wrongWord)
{
	char correction[45]; //set to 45 because that is the longest word in the english dictionary
	printf("%s", wrongWord);
	printf("%s", " was detected to be an invalid word.");
	printf("%s\n", "Please enter the corrected word:");
	scanf("%s", correction);
	printf("%s\n", "You entered:");
	printf("%s\n",correction);
	
	return *correction;
}
*/

int getNumberOfWords(char *sentence)
{
	char sentence2[45];
	strcpy(sentence2, sentence);
	int numberOfWords = 0;
	printf("%s\n", sentence2);
	char* tok = strtok(sentence2, " ");
	
	while (tok != NULL) 
	{
		printf("%s\n", tok);
		tok = strtok(NULL, " ");
		numberOfWords++;
    }
	
	printf("%s\n", sentence);
	printf("%s\n", "The number of words is: ");
	printf("%d\n", numberOfWords);
	
	return numberOfWords;
}

char* getNextWord(char* word, char* sentence, int* startIndex) {
	// Temp variable for the word
	char tempWord[64];

	// Ignore starting spaces
	int i = *startIndex;
	while (sentence[i] != '\0' && (sentence[i] < 65 || sentence[i] > 122 ||
		(sentence[i] > 90 && sentence[i] < 97))) {
		i++;
	}
	
	// Return NULL if the end of the string is reached before processing characters
	if (sentence[i] == '\0') {
		return NULL;
	}	

	// Iterate until a space is found
	while (sentence[i] > 32) {
		// Update word via reference
		printf("%c\n", sentence[i]); 
		tempWord[i] = sentence[i];
		i++;
	}
	
	// Handle incorrect terminating characters
	if (tempWord[i] != '\0') {
		tempWord[i] = '\0';
	}

	// Copy the tempWord into word
	memset(word, 0, 64);
	strcpy(word, tempWord);
	*startIndex = i;	

	printf("%s, %s\n", word, tempWord);

	return word;
}


char** generateSentenceArray(char* sentence, int numberOfWords, int maxLength)
{	
	char sentence2[45];
	strcpy(sentence2, sentence);
	printf("%s\n", sentence);
	
	
	char** sentenceArray = (char**)malloc(numberOfWords * sizeof(char*));
	
	for(int i = 0; i < numberOfWords; i++) 
	{
        sentenceArray[i] = (char*)malloc((numberOfWords + 1) * sizeof(char));
    }
	
	int i = 0;
	int curSpace = 0;
	char* word = strtok(sentence2, " ");
	printf("THE FIRST WORD: %s\n", word);

	while (curSpace > -1) 
	{
		//char* word = strtok(sentence2, " ");
		//printf("%s\n", word);
		sentenceArray[i] = word;
		printf("%s\n", "elements of the sentence array");
		printf("%s\n", sentenceArray[i]);
		while(!checkWord(sentenceArray[i])) {
			printf("\nWord %s not found; please re-enter: ", sentenceArray[i]);
			scanf("%s", sentenceArray[i]);
			word = strtok(NULL, " ");
			i++;
		}
		word = getNextWord(word, sentence, &curSpace);
		printf("Next word: %s", word);
    }
	
	return sentenceArray;
}


void freeArray(char** array, int length) //This frees the memory allocated by generateDictionary and sentenceSplit
{
    for(int i=0; i<length; i++)
	{
        free(array[i]);
    }
    free(array);
}

char** generateDictionary(int listlength, int wordslength) //this generates a char[] that is equal to the dictionary
{
    char** dictionary = malloc(listlength * sizeof(char*));

	FILE* infile = fopen("dictionary.txt", "r");

    for(int i = 0; i < listlength; i++) 
	{
        dictionary[i] = malloc((wordslength + 1) * sizeof(char));
    }

    for(int i = 0; i < listlength; i++) 
	{
        fgets(dictionary[i], wordslength + 1, infile);
    }

    fclose(infile);

    return dictionary;
}

void sendFileToServer(FILE *file, int socketclient)
{
  char buffer[SIZE] = {0};

  while(fgets(buffer, SIZE, file) != NULL) 
  {
    if (send(socketclient, buffer, sizeof(buffer), 0) == -1) 
	{
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(buffer, SIZE);
  }
}

void sendMessageToServer(int socketclient, char *encryptedMessage, int q)
{
	send(socketclient, q, sizeof(int),0);
	send(socketclient, encryptedMessage, sizeof(char),0);
}

void receiveMessageFromClient(int socketclient, const char* strPrefix)
{
  FILE *file;
  char *filename = getFileName(strPrefix);
  int nbytes;
  char buffer[SIZE];

  file = fopen(filename, "w");
  
  while (1) 
  {
    nbytes = recv(socketclient, buffer, SIZE, 0);
    
	if (nbytes <= 0)
	{
      break;
    }
    
	fprintf(file, "%s", buffer);
    bzero(buffer, SIZE);
  }
  
  return;
}

void sendFileToClient(FILE *file, int socketclient)
{
  char buffer[SIZE] = {0};

  while(fgets(buffer, SIZE, file) != NULL) 
  {
    if (send(socketclient, buffer, sizeof(buffer), 0) == -1) 
	{
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(buffer, SIZE);
  }
}

void receiveFileFromServer(int socketclient, const char* strPrefix)
{
  FILE *file;
  char *filename = getFileName(strPrefix);
  int nbytes;
  char buffer[SIZE];

  file = fopen(filename, "w");
  
  while (1) 
  {
    nbytes = recv(socketclient, buffer, SIZE, 0);
    
	if (nbytes <= 0)
	{
      break;
    }
    
	fprintf(file, "%s", buffer);
    bzero(buffer, SIZE);
  }
  
  return;
}

void receiveFileFromClient(int socketclient, const char* strPrefix)
{
  FILE *file;
  char *filename = getFileName(strPrefix);
  int nbytes;
  char buffer[SIZE];

  file = fopen(filename, "w");
  
  while (1) 
  {
    nbytes = recv(socketclient, buffer, SIZE, 0);
    
	if (nbytes <= 0)
	{
      break;
    }
    
	fprintf(file, "%s", buffer);
    bzero(buffer, SIZE);
  }
  
  return;
}

/*
Method to send and receive information:
Client sending file to Server:
client runs: SendMessageToServer()
server runs: receiveMessageFromClient()
server runs: sendFileToClient()
client runs: receiveFileFromServer()

Server sending file to Client:
client runs: sendFileToServer();
server runs: receiveFileFromClient();
server runs: sendFileToClient();
client runs: receiveFileFromServer();
*/



//This main method is just a series of tests written for each method
int main()
{
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
	char *testEncrypt = Encrypt(testString, sizeOfArray, q);
	printf("%s\n", "The encrypted String:");
	printf("%s\n", testEncrypt);
	
	//the following method will test the decryption method
	char *testDecrypt = Decrypt(testEncrypt, sizeOfArray, q);
	printf("%s\n", "The decrypted String:");
	printf("%s\n", testDecrypt);
	
	//the following method will test the dictionary method
	//set to 45 because that is the longest word in the english dictionary
	char dictionaryTest[] = "apple";
	printf("%s\n", "Dictionary test for apple:");
	
	// Kyle: New string for testing
	char* dynString = (char*) malloc(sizeof(char) * 45);
	strcpy(dynString, dictionaryTest);
	printf("String: %s Pointer: %p\n", dynString, dynString);
	
	// Kyle: Loop while incorrect
	while(!checkWord(dynString)) {
		printf("\nWord %s not found; please re-enter: ", dynString);
		scanf("%s", dynString);
	}
	
	printf("%s\n", "Dictionary test for applez:");
	char dictionaryTest2[] = "applez";
	
	// Kyle: Reinitialize dynString for the second test
	strcpy(dynString, dictionaryTest2);
	
	// Kyle: Loop while incorrect
	while(!checkWord(dynString)) {
		printf("\nWord %s not found; please re-enter: ", dynString);
		scanf("%s", dynString);
	}
	
	// Kyle: This should be the corrected word
	printf("Corrected word: %s\n", dynString);
	free(dynString);
	
	//This is a test for sentence splitting
	char testSentence[] = ("How many times can I split the string");
	int testWordNumber = getNumberOfWords(testSentence);
	printf("%s\n", testSentence);
	char** sentenceArray = generateSentenceArray(testSentence,testWordNumber,46);
	for(int i = 0; i < testWordNumber; i++)
	{
			printf("%s\n", sentenceArray[i]);
	}
	printf("%s\n", testSentence);
	free(sentenceArray);
	
	return 0;
}

/*left to do:
Break a sentence up into words.
Pass each word into checkword
fix invalidword method to return char[]

Communication between server and client
To Do:
SendMessagetoServer()
receiveFile()
messageClientToPerformTask()
*/
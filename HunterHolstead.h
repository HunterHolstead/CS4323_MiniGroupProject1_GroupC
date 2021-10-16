//Hunter Holstead
//Operating Systems Mini Group Project Group C

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // included here for compilation reasons (Jeremiah)

int Random()
{
	time_t t;
	
	srand((unsigned) time(&t));
	
	int random = rand();
	
	//print statement for testing purposes
	/*printf("%s\n", "Random Number generated:");
	printf("%d\n", random);*/
	
	return random;
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

const char *Encrypt(char *encryptString, int size, int q)
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
		encryptValues[i] = (p+q) % 52;
		encryptString[i] = MapPToChar(encryptValues[i]);
	}
	
	return encryptString;
}

const char *Decrypt(char *decryptString, int size, int q)
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
		decryptValues[i] = (p - q) % 52;
		decryptString[i] = MapPToChar(decryptValues[i]);
	}

	return decryptString;
}

/*
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
	const char *testEncrypt = Encrypt(testString, sizeOfArray, 3);
	printf("%s\n", "The encrypted String:");
	printf("%s\n", testEncrypt);
	
	//the following method will test the decryption method
	const char *testDecrypt = Decrypt(testEncrypt, sizeOfArray, 3);
	printf("%s\n", "The decrypted String:");
	printf("%s\n", testDecrypt);
	
	return 0;
}
*/
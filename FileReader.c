#include <stdio.h>
#include <stdlib.h>

char** generateDictionary(int rows, int col);
void freeArray(char** dictionary, int listlength);

int checkWord()
{
	int listlength = 58122;
	int wordslength = 45; //Longest possible word in english dictionary is 45 letters long
	
    char** dictionary = generateDictionary(listlength, wordslength);
	char test[] = "kangaroo";
	char* result;
	int isIn;

    for(int i=0;i<58122;i++)
	{
		result = strstr(dictionary[i],test);
		
		if(result)
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
			printf("%s","It is in the dictionary");
		}
		else
		{
			printf("%s","It is not in the dictionary");
		}

    freeArray(dictionary, listlength);
}


char** generateDictionary(int listlength, int wordslength) 
{
    char** dictionary = malloc(sizeof(char*) * listlength);

    for (int i = 0; i < listlength; i++) 
	{
        dictionary[i] = malloc(sizeof(char) * (wordslength + 1));
    }

    FILE* infile = fopen("dictionary.txt", "r");

    for (int i = 0; i < listlength; i++) 
	{
        fgets(dictionary[i], wordslength + 1, infile);
    }

    fclose(infile);

    return dictionary;
}

void freeArray(char** dictionary, int listlength)
{
    for(int i=0; i<listlength; i++)
	{
        free(dictionary[i]);
    }
    free(dictionary);
}

int main()
{
	return 0;
}
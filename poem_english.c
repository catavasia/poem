//created by Dana 

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "engletter.h"

const int ERRORPTR = 4;
const int PTROK = 5;
const int ERRORPTRMASS = 6;
const int ERRORNUMOFLINES = 7;
const int POEMNOTOPEN = 8;
const int ERRORFILEOPEN = 9;
const int OK = 10;
const int SORTEDPOEMNOTOPEN = 11;
const int ERRORPTRCOPY = 12;

int CheckPtr();
char* ReadFile();
long long CleanString();
char** CreateMassivPtr();
int CompareStr();
void PrintPoem();
long long CountSize();
char** CreateCopy();
void Reverse();
void Swap();
int CheckFile();

int main() 
{
	FILE *f = fopen("poem_english.txt", "rb");
	int result1 = CheckFile(f);
	if( result1!= OK)
	{
		fclose(f);
		return POEMNOTOPEN;
	}
	long long size = CountSize();
	char* poem = ReadFile(f, size);
	fclose(f);
	printf("size is %lld\n",size);
	long long lines = CleanString(poem);
	if (lines <= 0)
	{
		printf("Number of lines is < 0\n");
		return ERRORNUMOFLINES;
	}
	//printf("lines %lld\n", lines);
	int i = 0;
	char** masptr = CreateMassivPtr(poem, lines);
	if(CheckPtr(masptr) == ERRORPTR)
		return ERRORPTRMASS;
	Reverse(masptr, lines);
	char** copy = CreateCopy(masptr, lines);
	if(CheckPtr(copy) == ERRORPTR)
		return ERRORPTRCOPY;
	/*for ( i = 0; i < lines ; i++)
	{
		printf("%s\n", *(masptr+i));
	}*/
	FILE* f2 = fopen("sorted poem.txt", "w");
	int result2 = CheckFile(f2);
	if(result2!= OK)
	{
		fclose(f2);
		return SORTEDPOEMNOTOPEN;
	}
	qsort(masptr, lines, sizeof(char*), CompareStr);
	Reverse(masptr, lines);
	fprintf(f, "RHYNESORTED POEM\n\n");
	PrintPoem(masptr, lines, f2);
	qsort(masptr, lines, sizeof(char*), CompareStr);
	fprintf(f, "SORTED POEM\n\n");
	PrintPoem(masptr, lines, f2);
	fprintf(f, "ORIGINAL POEM\n\n");
	PrintPoem(copy, lines, f2);
	fclose(f2);
	printf("Sorted poem was printed\n");
	/*for (int i = 0; i < lines ; i++) // печать отсортированного текста
	{
		printf("%s\n", *(nol+i));
	}*/
	free(poem);
	free(masptr);
	free(copy);
	return 0;
}

char* ReadFile(FILE* f, long long a)
{
	//printf("Size of the poem is: %lld\n", a);
	char *W = (char*) calloc(a, sizeof(char));
	if(fread(W, sizeof(char), a, f)!= a)
       {
        if(feof(f))
            printf("End of file");
        else
            printf("File read error");
       }
	return W;
}

long long CleanString(char* poem)
{
	long long lines = 0;
	int i = 0;
	while(poem[i] != '\0')
	{
		if (poem[i] == '\n')
		{
			poem[i] = '\0';
			lines++;
		}
		i++;
		//printf("i is %d\n", i);	
	}
	poem[i] = '\n';
	return lines;
}

char** CreateMassivPtr(char* poem, long long lines)
{
	char** masptr = (char**)calloc(lines, sizeof(char*));
	int i = 1;
	int k = 1;
	masptr[0] = &poem[0];
	while(*(poem+i) != '\n' && k < lines)
    {
		if (poem[i] == '\0')
		{
			masptr[k] = &poem[i+1];
			//printf("OK");
			k++;
			i++;
			printf("i is %d\n",i);
		}
		else
			i++;
		
	}
	return masptr;
}

int CompareStr( const void* p1, const void* p2)
{
	const char* s1 = *(char**)p1;
	const char* s2 = *(char**)p2;
	while( *s1 != '\0' || *s2 != '\0')
	{
		//printf("ptr s1 %d\n", *s1);
		while (EngLetter(*s1) == NOTLETTER)
		{
			s1++;
		}
		int c1 = EngLetter(*s1);	
		while(EngLetter(*s2) == NOTLETTER)
		{
			s2++;
		}
		int c2 = EngLetter(*s2);
		if(c1 != c2)
			return c1-c2;
		s1++;
		s2++;
	}	
	if (*s1 == '\0' && *s2 != '\0')
		return -1;
	if (*s2 == '\0' && *s1 != '\0')
		return 2;
	if (*s1 == '\0' && *s2 == '\0')
		return 0;
}

int CheckPtr(void* ptr)
{
	char** s = (char**)ptr;
    if(ptr == NULL)
    {
        printf("Pointer is NULL\n");
		return ERRORPTR;
    }
    return PTROK;
}

void PrintPoem(char** masptr, int lines, FILE* f)
{
    for (int i = 0; i < lines; i++)
    {
		fprintf(f, "%s\n", *(masptr+i));
	}
}

long long CountSize(FILE* f)
{
	struct stat st = {};
	stat("poem_english.txt", &st);
	long long a = st.st_size;
	return a+1;
}

char** CreateCopy(char** masptr, long long lines)
{
	char** copy = (char**)calloc(lines, sizeof(char*));
	for( long long i = 0; i < lines; i++)
	{
		copy[i] = masptr[i];
	}
	return copy;
}

void Swap( char* a, char* b)
{
	char c = *a;
	*a = *b;
	*b = c;
}
	
int CheckFile(FILE* f)
{
	if(f == NULL) 
	{
		printf("Cannot open file \n");
		return ERRORFILEOPEN;
	}
	else
		return OK;
}

void Reverse(char** masptr, long long lines)
{
	for(long long i = 0; i < lines; i++)
	{
		int k = 0; 
		while((*(*(masptr+i)+k)) != '\0') 
		{
			k++;
		}
		for(int j = 0; j < k/2; j++) 
		{
			Swap((*(masptr+i)+j),(*(masptr+i)+k-1-j));
		}
		//printf("%s\n", *(masptr+i));
	}
}


			
			


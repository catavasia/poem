//created by Dana 

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const int NOTLETTER = -2;
const int ENDOFSTRING = 3;
const int ERRORPTR = 4;
const int PTROK = 5;
const int ERRORPTRMASS = 6;
const int ERRORNUMOFLINES = 7;

int CheckPtr();
char* ReadFile();
long long StringClean();
char** CreateMassivPtr();
//void Swap();
int FindLetter(char s);
int CompareStr();
void PrintPoem();

int main() 
{
	char* text = ReadFile();
	long long lines = StringClean(text);
	if (lines <= 0)
	{
		printf("Number of lines is < 0\n");
		return ERRORNUMOFLINES;
	}
	//printf("lines %lld\n", lines);
	int i = 0;
	/*while(text[i] != '\n')
	{
		printf("%c", text[i]);
		i++;
	}
	printf("All done\n");*/
	char** nol = CreateMassivPtr(text, lines);
	if(CheckPtr(nol) == ERRORPTR)
	{
		printf(" Error in massiv of pointers");
		return ERRORPTRMASS;
	}
	/*for (int i = 0; i < lines ; i++)
	{
		printf("%s\n", *(nol+i));
	}*/
	qsort(nol, lines, sizeof(char*), CompareStr);
	PrintPoem(nol, lines);
	printf("Sorted poem was printed\n");
	/*for (int i = 0; i < lines ; i++) // печать отсортированного текста
	{
		printf("%s\n", *(nol+i));
	}*/
	free(text);
	free(nol);
	return 0;
}

char* ReadFile()
{
	FILE *f = fopen("poem.txt", "rb");
	struct stat st = {};
	if(f == NULL) 
	{
		printf("Cannot open poem \n");
		return NULL;
	}
	stat("poem.txt", &st);
	long long a = st.st_size;
	//printf("Size of the poem is: %lld\n", a);
	char *W = (char*) calloc(a, sizeof(char));
	if(fread(W, sizeof(char), a, f)!= a)
       {
        if(feof(f))
            printf("End of file");
        else
            printf("File read error");
       }
	fclose(f);
	return W;
}

long long StringClean(char* text)
{
	long long lines = 0;
	int i = 0;
	while(text[i] != '\0')
	{
		if (text[i] == '\n')
		{
			text[i] = '\0';
			lines++;
		}
		i++;	
	}
	text[i+1] = '\n';
	return lines;
}

char** CreateMassivPtr(char* text, long long lines)
{
	char** nol = (char**)calloc(lines, sizeof(char*));
	int i = 0;
	int k = 0;
	while((*(text+i) != '\n'))
    {
		if (text[i] == '\0')
			{
				nol[k] = &text[i+1];
				printf("OK %d\n", i);
				k++;
				i++;
			}
			else
		i++;
	}
	return nol;
}

/*void Swap( char** s1, char** s2)
{
	char *temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}
*/

int FindLetter(char s)
{
	char Alph[] = "ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\0";
	for (int i = 0; i < 53; )
	{
		if (s == Alph[i])
			return i;
		i++;
	}
	if (s == '\0')
		return ENDOFSTRING;
	return NOTLETTER;
}

	
int CompareStr( const void* p1, const void* p2)
{
	const char *s1 = *(char**)p1;
	const char *s2 = *(char**)p2;
	while( *s1 != '\0' || *s2 != '\0')
	{
		//printf("ptr s1 %d\n", *s1);
		while (FindLetter(*s1) == NOTLETTER)
		{
			s1++;
		}
			int c1 = FindLetter(*s1);
			
		while(FindLetter(*s2) == NOTLETTER)
		{
			s2++;
		}
			int c2 = FindLetter(*s2);
			//printf("%d  %d\n", c1, c2);
			return (c1 - c2);
		
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

int CheckPtr(char** ptr)
{
    if(ptr == NULL)
    {
        printf("Pointer is NULL\n");
		return ERRORPTR;
    }
    return PTROK;
}

void PrintPoem(char** nol, int lines)
{
	FILE* f2 = fopen("sorted poem.txt", "w");
    if (f2 == NULL)
    {
        printf("could not open sorted poem\n");
        fclose(f2);
		return ;
    }
    for (int i = 0; i < lines; i++)
    {
		fprintf(f2, "%s\n", *(nol+i));
	}
    fclose(f2);
}



			
			


#include <string.h>

const int NOTLETTER = -2;
const int ENDOFSTRING = 3;
int EngLetter(char s)
{
	static char Alph[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	static int size = 0;
	if(size==0)
	{
	size = strlen(Alph);
	}
	for (int i = 0; i < size; )	
	{
		if (s == Alph[i])
			return i;
		i++;
	}
	if (s == '\0')
		return ENDOFSTRING;
	return NOTLETTER;
}

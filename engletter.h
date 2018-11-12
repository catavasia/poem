const int NOTLETTER = -2;
const int ENDOFSTRING = 3;
int EngLetter(char s)
{
	char Alph[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < 52; )	
	{
		if (s == Alph[i])
			return i;
		i++;
	}
	if (s == '\0')
		return ENDOFSTRING;
	return NOTLETTER;
}

#define STRING_OPERATIONS_LIB_FILE_NAME "string_operations_lib.h"

#define NAME_CHECK_LENGTH 5


int betweenAlphabets(char c)
{
	return (c>='A' && c<='Z') || (c>='a' && c<='z') ? 1 : 0;
}

int betweenDigits(char c)
{
	return (c>='0' && c<='9') ? 1 : 0;
}

int betweenLetterDigits(char c)
{
	return (betweenAlphabets(c) || betweenDigits(c)) ? 1 : 0;
}

void delete_unnecessary_spaces(char *string)
{
	int length = strlen(string);
	int space = 0;
	int i=0, s;
	
	
	for(i=0; string[i] == ' ' && i<length; i++);
	for(s = 0; i<length; i++)
	{
		if(betweenLetterDigits(string[i]))
		{
			if(!space)	space = 1;
			string[s++] = string[i];
		}
		else if(space)
		{
			space = 0;
			string[s++] = ' ';
		}
	}
	for(i=s-1; string[i]==' ' && i>=0; i--);
	string[i+1] = 0;
}
			

void namify(char *name)
{
	delete_unnecessary_spaces(name);
	
	int is_first = 1;
	for(int i=0; name[i]!=0; i++)
	{
		if(betweenLetterDigits(name[i]))
		{
			if(is_first)
			{
				is_first = 0;
				if(name[i]>='a' && name[i]<='z')
					name[i] = name[i]-'a' + 'A';
			}
		}
		else is_first = 1;
	}
}

int check_name(char *name)
{
	int length = strlen(name);
	if(length < NAME_CHECK_LENGTH) return 0;
	
	for(int i=0; name[i]!=0; i++)
		if(!(betweenLetterDigits(name[i]) || name[i] == ' ')) return 0;
	return 1;
}

//Function to convert integer into a string.
void integerNumberIntoString(int number, char string[])
{
	int total_digits = log10(number)+1;
	string[total_digits] = 0;
	for(int i=total_digits-1; i>=0; i--)
	{
		string[i] = number % 10 + '0';
		number /= 10;
	}
}

// Encoding every character of the string to it's 3 left character.
void encode_by_3_left(char *string)
{
	for(int i=0; string[i] != 0; i++)
		string[i] = string[i]-3;
}

// Encoding every character of the string to it's 3 right character.
void encode_by_3_right(char *string)
{
	for(int i=0; string[i] != 0; i++)
		string[i] = string[i]+3;
}



void lowerify(char *string)
{
	for(int i=0; string[i]!=0; i++)
		if(string[i]>='A' && string[i]<='Z') string[i] = string[i] - 'A' + 'a';
}

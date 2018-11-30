#define INTERACTIVE_SCANNING_LIB_FILE_NAME "interactive_scanning_lib.h"

int get_char(char *string)
{
	printf("%s: ", string);
	getchar();
	return getchar();
}

int get_int(char *string)
{
	int var;
	printf("%s: ", string);
	scanf("%d", &var);
	return var;
}

double get_double(char *string)
{
	double var;
	printf("%s: ", string);
	scanf("%lf", &var);
	return var;
}


void get_string(char *p_string, char *string)
{
	printf("%s: ", p_string);
	scanf(" %[^\n]", string);
}


int getCommand(char *string)
{
	return get_char(string);
}

int getiCommand(char *string)
{
	return get_int(string);
}


void getsCommand(char *p_string, char *string)
{
	get_string(p_string, string);
}



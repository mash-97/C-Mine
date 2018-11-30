#define FILE_AND_FOLDER_LIB_FILE_NAME "file_and_folder_lib.h"

#define FAILED_TO_CREATE_FOLDER 	1051
#define SUCCESS_TO_CREATE_FOLDER 	1052
#define FAILED_TO_CREATE_FILE 		1061
#define SUCCESS_TO_CREATE_FILE 		1062
#define FAILED_TO_APPEND_MESSAGE 	1063
#define SUCCESS_TO_APPEND_MESSAGE 	1064
#define FAILED_TO_BURN_MESSAGE		1065
#define SUCCESS_TO_BURN_MESSAGE 	1066
#define FAILED_TO_KEEN_MESSAGE  	1067
#define SUCCESS_TO_KEEN_MESSAGE		1068
#define PATH_SEPERATOR "/"

void join_as_path(char *pathous, char *patheus)
{
	strcat(pathous, PATH_SEPERATOR);
	strcat(pathous, patheus);
}

void make_as_path(char *pathous, char *path, char *patheus)
{
	strcpy(pathous, path);
	join_as_path(pathous, patheus);
}

int makeFolder(char *folder_name)
{
	int status = mkdir(folder_name, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
	
	if(status==0)	return SUCCESS_TO_CREATE_FOLDER;
	
	return FAILED_TO_CREATE_FOLDER;
}

int makeFile(char *file_name)
{
	FILE *file = fopen(file_name, "w");
	if(file!=NULL)
	{
		fclose(file);
		return SUCCESS_TO_CREATE_FILE;
	}
	fclose(file);
	return FAILED_TO_CREATE_FILE;
}

int appendMessageInto(char *file_path, char *message)
{
	FILE *file = fopen(file_path, "a");
	if(file == NULL) return FAILED_TO_APPEND_MESSAGE;
	fputs(message, file);
	fputs("\n", file);
	fclose(file);
	return SUCCESS_TO_APPEND_MESSAGE;
}

int burnMessageInto(char *file_path, char *message)
{
	FILE *file = fopen(file_path, "w");
	if(file == NULL) return FAILED_TO_BURN_MESSAGE;
	fputs(message, file);
	fputs("\n", file);
	fclose(file);
	return SUCCESS_TO_BURN_MESSAGE;
}


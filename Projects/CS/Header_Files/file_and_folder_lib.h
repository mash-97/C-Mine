#define FILE_AND_FOLDER_LIB_FILE_NAME "file_and_folder_lib.h"


#define __FIL__       2
#define __DIR__ 	  1
#define __UNKNOWN__   0


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


int ftype(const char * path)
{
	struct stat status;
	stat(path, &status);
	
	if(S_ISREG(status.st_mode) == 1)	
		return __FIL__;
	if(S_ISDIR(status.st_mode) == 1)
		return __DIR__;
	return __UNKNOWN__;
}

int isExist(const char * path)
{
	return (access(path, F_OK) != -1) ? 1 : 0;
}

int isFile(const char *path)
{
	return (ftype(path) == __FIL__) ? 1 : 0;
}

int isDirectory(const char *path)
{
	return (ftype(path) == __DIR__) ? 1 : 0;
}


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

void readFile(char *file_path)
{
	if(isFile(file_path))
	{
		FILE * file = fopen(file_path, "r");
		char c;
		while((c = getc(file)) != EOF) printf("%c", c);
		fclose(file);
	}
}

int deleteFile(const char * file_path)
{
	 return (isFile(file_path)) ? (unlink(file_path) == 0) : 0;
}

int deleteDir(const char * dir_path)
{
	int deletes_count = 0;
	if(!isDirectory(dir_path)) return 0;
	
	size_t dir_path_length = strlen(dir_path);
	DIR * dir;
	struct dirent * entry;
	
	if( ( dir = opendir(dir_path)) == NULL)
	{
		fstderr((char *) dir_path, "opendir()", FILE_AND_FOLDER_LIB_FILE_NAME, "deleteDir", "1");
		perror(FILE_AND_FOLDER_LIB_FILE_NAME);
		exit(1);
	}
	
	char *new_path;
	while( ( entry = readdir(dir) ) != NULL)
	{
		if( !strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") ) continue;
		
		new_path = (char *) calloc( (dir_path_length+strlen(entry->d_name)+1), sizeof(char));
		
		make_as_path(new_path, (char *)dir_path, (char *)entry->d_name);
		
		if(isDirectory(new_path)) deletes_count += deleteDir(new_path);
		if(isFile(new_path)) deletes_count += deleteFile(new_path);
		
	}
	
	deletes_count += (rmdir(dir_path)==0);
	
	closedir(dir);
	
	return deletes_count;
}

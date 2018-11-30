#define ENU_LIB_FILE_NAME "ENU_lib.h"

int get_enu(char *enu_file_path)
{
	FILE *file = fopen(enu_file_path, "r");
	if(file == NULL)
	{
		fprintf(file, "Failed to open the file :%s in read mode! (inside: get_enu())\n", enu_file_path);
		exit(1);
	}
	int enu;
	fscanf(file, "%d", &enu);
	fclose(file);
	
	return enu;
}

void set_enu(char *enu_file_path, int enu)
{
	FILE *file = fopen(enu_file_path, "w");
	if(file == NULL)
	{
		fprintf(stderr, "Failed to open the file :%s in write mode! (inside: set_enu())\n", enu_file_path);
		exit(1);
	}
	
	fprintf(file, "%d\n", enu);
	fclose(file);
}

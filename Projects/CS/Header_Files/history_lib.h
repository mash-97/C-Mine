#define HISTORY_LIB  "history_lib.h"
#define HISTORY_PATH "./History"
#define HISTORY_ENU  "./History/history.enu"
#define HISTORY_HIF  "./History/history.hif"


void save_a_history(Match * match)
{
	int enu = get_enu(HISTORY_ENU);
	enu++;
	
	// add history.hif
	FILE * f = fopen(HISTORY_HIF, "a+");
	fprintf(f, "%d %s\n", enu, match->name);
	fclose(f);
	//////////////////
	
	set_enu(HISTORY_ENU, enu);
	
	char enu_s[11];
	integerNumberIntoString(enu, enu_s);
	
	char * file_path = (char *) calloc( strlen(HISTORY_PATH)+strlen(enu_s)+3, sizeof(char));
	
	make_as_path(file_path, HISTORY_PATH, enu_s);
	
	burn_a_match_summary(match, file_path);
}

int does_a_match_name_exist(char * match_name)
{
	FILE * f = fopen(HISTORY_HIF, "r");
	int enu = get_enu(HISTORY_ENU);
	int file_no;
	char name[51];
	
	for(int i=1; i<=enu; i++)
	{
		fscanf(f, "%d %[^\n]", &file_no, name);
		if(!strcmp(match_name, name)) return file_no;
	}
	
	return 0;
}

void show_a_history(int file_no)
{
	if(file_no<=0) return;
	char file_nos[11]; 
	integerNumberIntoString(file_no, file_nos);
	
	char *file_path = (char *) calloc(strlen(HISTORY_PATH)+strlen(file_nos)+3, sizeof(char));
	make_as_path(file_path, HISTORY_PATH, file_nos);
	readFile(file_path);
}




void history()
{
	clrscr();
	printf("================================================================================\n");
	printf("================================== History =====================================\n");
	printf("================================================================================\n");
	
	char match_name[51];
	int file_no;
	int flag = 1;
	
	get_match_name:
		newl;
		get_string("Enter the corresponding match name:", match_name);
		if(!strcmp(match_name, "back")) return;
		namify(match_name);
		if(!check_name(match_name)) goto get_match_name;
		if(!(file_no = does_a_match_name_exist(match_name)))
		{
			printf("Doesn't exist in the history !!!\n\n");
			goto get_match_name;
		}
	
	print_newls(30);
	clrscr();
	show_a_history(file_no);
	newl;
	pause();
	if(flag) printf("Again ! :: type 'back' to get back :)\n\n");
	pause();
	history();
}

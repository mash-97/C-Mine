#define INTERACTIVE_PRINTING_LIB_FILE_NAME "interactive_printing_lib.h"

#define newl puts("");
#define s4	printf("    ")



void fstderr(char *file_path, char *mode, char *in_file_name, char *scope_name, char *no)
{
	fprintf(stderr, "Failed to open the file: %s in '%s' mode !!! # In %s :: %s : %s\n", file_path, mode, in_file_name, scope_name, no);
}

void print_spaces(int total)
{
	for(int i=1; i<=total; i++) printf(" ");
}


void fprint_spaces(FILE **file, int total)
{
	for(int i=1; i<=total; i++) fprintf(*file, " ");
}


void print_divider_label(int total_underscore)
{
	for(int i=1; i<=total_underscore; i++)
		printf("_");
	newl;newl;
}


void fprint_divider_label(FILE **file, int total_underscore)
{
	for(int i=1; i<=total_underscore; i++)
		fprintf(*file, "_");
	fprintf(*file, "\n\n");
}


void print_instructions()
{
	print_divider_label(80);
	printf("\t\t\t1 Run              --> 1/one\n");
	printf("\t\t\t2 Runs             --> 2/two\n");
	printf("\t\t\t3 Runs             --> 3/three\n");
	printf("\t\t\t4 Runs             --> 4/four\n");
	printf("\t\t\t6 Runs             --> 6/six\n");
	printf("\t\t\tSwap               --> 7/swap\n");
	printf("\t\t\tExtra              --> e/extra\n");
	printf("\t\t\tWide               --> w/wide\n");
	printf("\t\t\tOut                --> o/out\n");
	printf("\t\t\tOver               --> ov/over\n");
	printf("\t\t\tShow Scoreboard    --> ss\n");
	printf("\t\t\tInnings Declared   --> declared\n");
	printf("\t\t\tHelp           ======> h/help\n");
	print_divider_label(80);
}



void fprint_names_runs_label(FILE **file, int max_len)
{
	fprint_spaces(file, 5); fprintf(*file, "Names"); fprint_spaces(file, (max_len-5)+4+7+4); fprintf(*file, "Runs\n\n");
}

void print_names_runs_label(int max_len)
{
	print_spaces(5); printf("Names"); print_spaces((max_len-5)+4+7+4); printf("Runs\n\n");
}

void print_newls(int total)
{
	static int i = 0;
	if(i==total)
	{
		i=0;
		return;
	}
	newl;
	i++;
	print_newls(total);
	
}

void print_player_registration_label()
{
	printf("================================================================================\n");
	printf("==========================    Player Registration   ============================\n");
	printf("================================================================================\n");
}

void print_team_registration_label()
{
	printf("================================================================================\n");
	printf("===========================  Team Registration  ================================\n");
	printf("================================================================================\n");
}


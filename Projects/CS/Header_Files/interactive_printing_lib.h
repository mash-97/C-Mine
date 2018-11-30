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


void print_instructions()
{
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
	newl;
}

void print_names_runs_label(int max_len)
{
	printf("Names"); print_spaces((max_len-5)+4+7+4); printf("Runs\n");
}

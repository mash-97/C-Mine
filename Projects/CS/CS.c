#include "./necessary_C_header_files.h"
#include "./builded_header_files.h"

#define ABOUT_FILE "./about.txt"
#define NEW_MATCH	  1
#define NEW_TEAM 	  2
#define NEW_PLAYER    3
#define HISTORY		  4
#define SEARCH		  5
#define ABOUT		  6
#define EXIT 		  7


void welcome()
{
	printf("\n\n\n                                     Welcome\n");
	print_spaces(30+10);
	getchar();
}


void firstPage(int last_match_flag)
{
	int c = 0;
	clrscr();
	printf("================================================================================\n");
	printf("============================ Cricket Scoreboard ================================\n");
	printf("================================================================================\n");
	newl;
	
	if(last_match_flag)
	printf("\t%d. Last Match Summary\n", ++c);
		
	printf("\t     %d. New Match",  NEW_MATCH+c);
	printf("                        %d. New Team\n\n",   NEW_TEAM+c);
	printf("\t     %d. New Player", NEW_PLAYER+c);
	printf("                       %d. History\n\n",    HISTORY+c);
	printf("\t     %d. Search",     SEARCH+c);
	printf("                           %d. About\n\n",      ABOUT+c);
	printf("                               %d. Exit\n",       EXIT+c);
	newl;
}



void about()
{
	readFile(ABOUT_FILE);
}

int main(int arg, char **argv)
{
	int commando;
	Match * new_match;

	in_first_page:
	firstPage(0);

	get_first_command:
		print_newls(2);
		commando = getiCommand("                               :");

	switch(commando)
	{
		case NEW_MATCH:	clrscr();
			
			new_match = get_a_new_match();
			new_match = simulate_the_match(new_match);
			
			if(new_match == NULL) goto in_first_page;
			
			burn_a_match_summary(new_match, "bufferMatchSummary.txt");
			
			// Match Summary:
			clrscr(); print_match_header(new_match);
			readFile("./bufferMatchSummary.txt");
			deleteFile("./bufferMatchSummary.txt");
			newl;
			getchar();
			
			in_match_save_confirmation_command:
				commando = getiCommand("Save this match: (1:0) :");
				if(commando == 1) 
				{
					save_a_history(new_match);
					printf("\n\nSaved :: To see search by name in the history\n\n");
				}
				else if(commando != 0) goto in_match_save_confirmation_command;
			goto in_first_page;
		break;

		case NEW_TEAM:
			clrscr();
			register_a_team();
			goto in_first_page;
		break;

		case NEW_PLAYER:
			clrscr();
			register_a_player_in_a_team();
			goto in_first_page;
		break;

		case SEARCH:
			search();
			goto in_first_page;
		break;

		case HISTORY:
			print_newls(25);
			clrscr();
			history();
			getchar();
			goto in_first_page;
		break;
		
		case ABOUT:
			clrscr();
			about();
			pause();
			goto in_first_page;
		break;

		case EXIT:
			return 0;
		break;

		default:
			printf("Wrong Command! Try again!\n");
			goto get_first_command;
		break;
	}

	return 0;
}

#define SEARCH_LIB "search_lib.h"

#define SEARCH_MATCH  1
#define SEARCH_TEAM   2
#define SEARCH_PLAYER 3
#define BACK          4

void print_search_page_label()
{	printf("================================================================================\n");
	printf("=================================== SEARCH =====================================\n");
	printf("================================================================================\n");
}

void print_search_page_menus()
{
	printf("\t\t     %d. Match",  SEARCH_MATCH);
	printf("                     %d. Team\n\n", SEARCH_TEAM);
	printf("\t\t     %d. Player", SEARCH_PLAYER);
	printf("                    %d. Back\n", BACK);
}

void search()
{
	in_search_page:
	clrscr();
	print_search_page_label();
	newl;
	print_search_page_menus();
	newl;
	newl;
	
	int commando;
	char team_name[51];
	char team_password[21];
	int  team_folder_no;
	Team * team = NULL;
	char *file_path;
	char team_folder_string[20];
				
		commando = getiCommand("                                    :");
		switch(commando)
		{
			case SEARCH_TEAM:
				get_team(team_name, team_password, ' ', &team_folder_no);
				integerNumberIntoString(team_folder_no, team_folder_string);
				file_path = (char *) calloc(strlen(TEAMS_PATH)+strlen(team_folder_string)+3, sizeof(char));
				make_as_path(file_path, TEAMS_PATH, team_folder_string);
				team = load_a_team(file_path);
				if(team == NULL)
				{
					printf("ERROR: Couldn't load the team from : %s !!!\n", file_path);
					exit(1);
				}
				
				display_a_team(team);
				getchar();
				
				newl;
				newl;
				commando = getiCommand("Do you want to delete this team? ( 1:0 ) :");
				if(commando == 1)
				{
					commando = getiCommand("Are you sure? (1:0) : ");
					if(commando == 1)
					{
							get_string("Enter password:", team_password);
							encode_by_3_left(team_password);
							if(!strcmp(team->encoded_password, team_password)) 
							{
								deleteDir(file_path);
								newl;
								printf("Successfull Deleted !\n");
								getchar();
								goto in_search_page;
							}
							else
							{
								newl;
								printf("Wrong Password !\n");
								getchar();
								goto in_search_page;
							}
					}
					else goto in_search_page;
				}
				goto in_search_page;
			break;
			
			case SEARCH_PLAYER:
				clrscr();
				newl;
				printf("Sorry this feature is not yet developed !\n");
				newl;
				getchar();
				goto in_search_page;
			break;
			
			case SEARCH_MATCH:
				clrscr();
				newl;
				printf("Sorry this feature is not yet developed !\n");
				printf("You can look in the history.\n");
				newl;
				getchar();
				getchar();
				goto in_search_page;
			break;
			
			case BACK:
				return;
			break;
			
			default:
				goto in_search_page;
			break;
		}
}
				
					
	

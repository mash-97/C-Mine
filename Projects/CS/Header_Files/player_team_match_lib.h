#define PLAYER_TEAM_MATCH_LIB_FILE_NAME "player_team_match_lib.h"

#define NORMAL				101

int get_team(char *name, char *password, char team, int *team_folder_no)
{
	int check_status;
	get_team:
		get_team_name:
		newl; s4;
			
			printf("Name of the Team %c: ", team);
			scanf(" %[^\n]", name);
			namify(name);
			if(!checkExistenceOfTheTeam(name))
			{
				newl; 
				s4;print_divider_label(strlen(name)+34);
				s4;printf("The team: %s doesn't exist -_- !!!\n", name);
				s4;print_divider_label(strlen(name)+34);
				newl;
				goto get_team_name;
			}
			if(!check_name(name)) goto get_team_name;
			newl;
			
		get_password:
		newl; s4;
		
			printf("Password (type 'u' to go up): ");
			scanf(" %[^\n]", password);
			namify(password);
			if(strlen(password)==1 && password[0] == 'U')	goto get_team;
			encode_by_3_left(password);
			if(betweenAlphabets(password[0])) password[0] = password[0]-'A'+'a';
			if(strlen(password) != 4) goto get_password;
			check_status = checkIfThePasswordMatch(name, password);
			if(!check_status)
			{
			newl;
				s4;printf("_________________________\n\n");
				s4;printf(" | Password Incorrect !|\n");
				s4;printf("_________________________\n");
				goto get_team;
			}
			newl;
			
	*team_folder_no = check_status;
	return NORMAL;
}

Player * auto_players_for(Team *team, int NOPIET)
{
	Player * current_player = reverse_player_list(insertion_sort_by_av(team->players));
	Player * players = NULL;
	Player * player = NULL;
	
	for(int i=1; i<=NOPIET; i++)
	{
		if(current_player == NULL) 
		{
			fprintf(stderr, "Team has not %d players !!!\n", NOPIET);
			exit(1);
		}
		player = copy_player(current_player);
		player->out_or_not = NOT_OUT;
		players = prepend_player(players, player);
		current_player  = current_player->next;
	}
	
	return players;
}

Player * get_players_for(Team * team, int NOPIET)
{
	team->players = reverse_player_list(insertion_sort_by_av(team->players));
	
	char player_name[51];
	Player *players = NULL;
	Player *player  = NULL;

newl; s4;	
	printf("Name of the %s's players:\n", team->name);
newl; s4;
	printf("(To see all the players in the team has, type 'show players'.)\n\n");
	for(int i=1; i<=NOPIET; i++)
	{
	
		get_player_name:
			newl; s4;
			printf("%2d: ", i);
			scanf(" %[^\n]", player_name);
			if(i==1 && !strcmp(player_name, "auto")) return(auto_players_for(team, NOPIET));
			
			namify(player_name);
			if(!strcmp(player_name, "Show Players")) 
			{newl;
				display_players(team->players);
				goto get_player_name;
			}
			
			if(!check_name(player_name)) goto get_player_name;
			
			player = search_a_player_by_name(team->players, player_name);
			if(player == NULL)
			{
			newl; s4;
				printf("The player name: %s not found in the team: %s\n", player_name, team->name);
			newl; s4;
				printf("You have to register in the team for new player !!!\n");
				goto get_player_name;
			}
			player = copy_player(player);
			player->out_or_not = NOT_OUT;
			players = prepend_player(players, player);
	}
	return players;
}


int register_a_player_in_a_team()
{
	char commando;
	char name[51];
	char password[5];
	char player_name[51];
	char players_folder_path[511];
	char number_string[11];
	int team_folder_no;
	
	print_player_registration_label();
	get_team(name, password, ':', &team_folder_no);
	
	integerNumberIntoString(team_folder_no, number_string);
	make_as_path(players_folder_path, TEAMS_PATH, number_string);
	join_as_path(players_folder_path, PLAYERS_FOLDER_NAME);
	
	Player * existed_players = load_players(players_folder_path);
	Player * player = NULL;
	
	get_the_player_name:
	newl; s4;
	
		printf("New Player's Name: ");
		scanf(" %[^\n]", player_name);
		namify(player_name);
		if(!check_name(player_name)) goto get_the_player_name;
		player = search_a_player_by_name(existed_players, player_name);
		if(player != NULL)
		{
		newl; s4;
			
			printf("Player named: %s already exist in the database !!!\n", player->name);
			goto get_the_player_name;
		}
	
	get_confirm_command:
	newl; s4;
	
		commando = getCommand("Do you confirm? (Y:N)-> (1:0) :: for quit press 'q'\n    :");
		if(commando == 'q') return QUIT;
		if(commando == '0') return REGISTRATION_NOT_CONFIRMED;
		if(commando != '1') goto get_confirm_command;
		
	player = create_player(player_name, 0, 0, 0, NULL);
	char enu_file_path[1010];
	make_as_path(enu_file_path, players_folder_path, PLAYERS_ENU_FILE_NAME);
	int enu = get_enu(enu_file_path);
	integerNumberIntoString(enu+1, number_string);
	
	char file_path[1010];
	make_as_path(file_path, players_folder_path, number_string);
	burn_a_player_infos_into_the_file(player, file_path);
	set_enu(enu_file_path, enu+1);
	
	return REGISTRATION_CONFIRMED;
}



Match * get_a_new_match()
{
	// Part 1:
	clrscr();
	printf("================================================================================\n");
	printf("============================      New Match     ================================\n");
	printf("================================================================================\n");

	char name_of_the_match[51];
	char team_name_A[51];	char password_A[5];   int team_A_folder_no;	char A_folder_no_string[11]; char A_folder_path[1010];
	char team_name_B[51];	char password_B[5];	  int team_B_folder_no;	char B_folder_no_string[11]; char B_folder_path[1010];
	int total_overs;
	int nopiet;
	
	get_match_name:
		if(get_enu(TEAM_ENU_PATH) == 0) 
		{
			print_newls(7);
			print_spaces(20);
			printf("There are no team in the storage !!!\n\n");
			print_spaces(22);
			printf("Register a new team...\n\n\n");
			pause();
			return NULL;
		}
		if(get_enu(TEAM_ENU_PATH) == 1)
		{
			print_newls(7);
			print_spaces(20);
			printf("There are only one team in the storage !!!\n\n");
			print_spaces(22);
			printf("Register an another team to continue...\n\n\n");
			pause();
			return NULL;
		}
		
	newl; s4;
		printf("Name Of The Match: ");
		scanf(" %[^\n]", name_of_the_match);
		
		if(name_of_the_match[0]=='#')	nopiet = 5;
		else nopiet = 11;
		namify(name_of_the_match);
		if(!check_name(name_of_the_match)) goto get_match_name;
		newl;
		
	get_teams:
		get_team(team_name_A, password_A, 'A', &team_A_folder_no);
		newl;
		get_team(team_name_B, password_B, 'B', &team_B_folder_no);
		newl;
		
		if(!strcmp(team_name_A, team_name_B))
		{newl; s4;
			printf("Two teams are same !!!\n\n");
			s4; printf("Try distinct teams \n\n");
			pause();
			goto get_teams;
		}
		
		integerNumberIntoString(team_A_folder_no, A_folder_no_string);
		integerNumberIntoString(team_B_folder_no, B_folder_no_string);

	make_as_path(A_folder_path, TEAMS_PATH, A_folder_no_string);
	make_as_path(B_folder_path, TEAMS_PATH, B_folder_no_string);

	Team * team_A = load_a_team(A_folder_path);
	Team * team_B = load_a_team(B_folder_path);

	team_A->teams_folder_no = team_A_folder_no;	strcpy(team_A->teams_folder_string, A_folder_no_string);
	team_B->teams_folder_no = team_B_folder_no;	strcpy(team_B->teams_folder_string, B_folder_no_string);

	get_overs:
	newl; s4;
	
		printf("Total Overs: ");
		scanf("%d", &total_overs);
		if(total_overs<1 || total_overs>50)	goto get_overs;


	// Part 2:
	Player * A_players = NULL;
	Player * B_players = NULL;


	clrscr();
	printf("================================================================================\n");
	printf("|| Match Name:  %s", name_of_the_match);print_spaces(80 - (strlen(name_of_the_match)+16+2)); printf("||\n");
	printf("|| %s vs %s", team_name_A, team_name_B);print_spaces(80 - (strlen(team_name_A)+strlen(team_name_B)+7+2));printf("||\n");
	printf("|| Total Overs: %d", total_overs);print_spaces(80-(log10(total_overs)+1+16+2));printf(" ||\n");
	printf("================================================================================\n");
	A_players = get_players_for(team_A, nopiet);
	newl;
	B_players = get_players_for(team_B, nopiet);
	newl;
	free_players(team_A->players);	team_A->players = A_players;
	free_players(team_B->players);	team_B->players = B_players;
	
	team_A->players = insertion_sort_by_av(team_A->players);
	team_B->players = insertion_sort_by_av(team_B->players);
	
	return( create_match(name_of_the_match, NULL, NULL, 0, 0, nopiet, total_overs, team_A, team_B, NULL, NULL) );
}

void burn_a_team_summary_2(Match * match, Team * team, char * file_path)
{
	FILE * file = fopen(file_path, "a+");
	if(file==NULL) {fprintf(stderr, "Failed to open the file: %s in 'a' mode !!!\n", file_path); exit(1);}
	
	team->players = insertion_sort_by_match_runs(team->players);
	team->players = reverse_player_list(team->players);
	
	fprintf(file, "%s ::", team->name);
	fprintf(file, "%d/%d\n", team->total_runs, team->total_wickets);
	if(team->played_overs != 0) fprintf(file, "Current Run Rate: %0.2lf\n", (double) (team->total_runs*1.0)/team->played_overs);
	fprintf(file, "Overs: %d\n\n", team->played_overs);
	
	Player * player = team->players;
	int max_len = max_name_length_of_players(player)+3;
	fprint_names_runs_label(&file, max_len);
	int i = 1;
	int len;
	while(player != NULL)
	{
		fprintf(file, "%2d. %s", i, player->name);
		len = strlen(player->name);
		if(player->out_or_not == NOT_OUT)
		{
			fprint_spaces(&file, (max_len-len)+4);
			fprintf(file, "NOT OUT");
			fprint_spaces(&file, 4);
		}
		else
		{
			fprint_spaces(&file, (max_len-len)+6);
			fprintf(file, "OUT");
			fprint_spaces(&file, 6);
		}
		fprintf(file, "%4d\n", player->match_runs);
		player = player->next;
		i++;
	}
	fprintf(file, "\nExtras: %4d\n", team->extras);
	fprintf(file, "Total : %4d\n\n", team->total_runs);
	fprint_divider_label(&file, 80);
	
	fclose(file);
}

void burn_a_match_summary(Match * match, char *file_path)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//~ void burn_a_team_summary(Team * team, char * file_path)
	//~ {
		//~ FILE * file = fopen(file_path, "a");
		//~ if(file==NULL) {fprintf(stderr, "Failed to open the file: %s in 'a' mode !!!\n", file_path); exit(1);}
		
		//~ fprintf(file, "%s  :: %d/%d", team->name, team->total_runs, team->total_wickets);
		//~ if(team->status == WON) fprintf(file, "    ***Winner***\n");
		//~ else fprintf(file, "\n");
		//~ fprintf(file, "Played Overs:: %2d\n\n", team->played_overs);
		
		//~ Player * player = team->players;

		//~ for(int i=1; player != NULL; i++)
		//~ {
			//~ fprintf(file, "%d. %s\n", i, player->name);
			//~ fprintf(file, "%d\n", player->match_runs);
			//~ if(player->out_or_not == OUT) fprintf(file, "OUT\n");
			//~ else fprintf(file, "NOT OUT\n");
			//~ fprintf(file, "\n");
			//~ player = player->next;
		//~ }
		//~ fprintf(file, "***%s :: %d\n\n\n", team->man_of_the_team->name, team->man_of_the_team->match_runs);
		//~ fclose(file);
	//~ }
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	FILE * file = fopen(file_path, "a+");
	if(file==NULL) {fprintf(stderr, "Failed to open the file: %s in 'a+' mode !!!\n", file_path); exit(1);}
	
	fprintf(file, "================================================================================\n");
	fprintf(file, "Match Name: %s\n", match->name);
	fprintf(file, "Start Time: %s", match->starting_time);
	fprintf(file, "End   Time: %s", match->ending_time);
	fprintf(file, "%s  vs  %s\n", match->team_A->name, match->team_B->name);
	fprintf(file, "Total Overs: %d\n", match->total_overs);
	if(match->status == DRAW) fprintf(file, "Match Status: Draw\n");
	else if(match->team_A->status == WON) fprintf(file, "Match Status: %s Won\n", match->team_A->name);
	else if(match->team_B->status == WON) fprintf(file, "Match Status: %s Won\n", match->team_B->name);
	else fprintf(file, "Match Status: Draw\n");
	fprintf(file, "================================================================================\n");
	
	
	
	fprintf(file, "\n");
	fclose(file);
	fprintf(file, "--------------------------------------------------------------------------------\n");
	burn_a_team_summary_2(match, match->team_A, file_path);
	fprintf(file, "--------------------------------------------------------------------------------\n");
	fprintf(file, "\n");
	fprintf(file, "--------------------------------------------------------------------------------\n");
	burn_a_team_summary_2(match, match->team_B, file_path);
	fprintf(file, "--------------------------------------------------------------------------------\n");
}



Player * initialize_players(Player *players)
{
	Player * current_player = players;
	while(current_player!=NULL)
	{
		current_player->match_runs = 0;
		current_player->status     = ~BATTING;
		current_player->out_or_not = NOT_OUT;
		
		current_player = current_player->next;
	}
	
	return players;
}



Team * initialize_team(Team * team)
{
	team->total_runs    = 0;
	team->played_overs  = 0;
	team->total_runs    = 0;
	team->total_wickets = 0;
	team->extras        = 0;
	
	team->players = initialize_players(team->players);
	
	return team;
}


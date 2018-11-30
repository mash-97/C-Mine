#define PLAYER_TEAM_MATCH_LIB_FILE_NAME "player_team_match_lib.h"

#define NORMAL				101

int get_team(char *name, char *password, char team, int *team_folder_no)
{
	int check_status;
	get_team:
		get_team_name:
			printf("Name of the Team %c: ", team);
			scanf(" %[^\n]", name);
			namify(name);
			if(!checkExistenceOfTheTeam(name))
			{
				printf("The team: %s doesn't exist -_- !!!\n", name);
				goto get_team_name;
			}
			if(!check_name(name)) goto get_team_name;
			newl;
			
		get_password:
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
				printf("Password Incorrect !\n");
				goto get_team;
			}
			newl;
			
	*team_folder_no = check_status;
	return NORMAL;
}

Player * auto_players_for(Team *team, int NOPIET)
{
	Player * current_player = team->players;
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
	char player_name[51];
	Player *players = NULL;
	Player *player  = NULL;
	
	printf("Name of the %s's players:\n", team->name);
	printf("(To see all the players in the team has, type 'show players'.)\n\n");
	for(int i=1; i<=NOPIET; i++)
	{
		get_player_name:
			printf("%2d: ", i);
			scanf(" %[^\n]", player_name);
			if(i==1 && !strcmp(player_name, "auto")) return(auto_players_for(team, NOPIET));
			
			namify(player_name);
			if(!strcmp(player_name, "Show Players")) 
			{
				display_players(team->players);
				goto get_player_name;
			}
			
			if(!check_name(player_name)) goto get_player_name;
			
			player = search_a_player_by_name(team->players, player_name);
			if(player == NULL)
			{
				printf("The player name: %s not found in the team: %s\n", player_name, team->name);
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
	
	printf("================================================================================\n");
	printf("==========================    Player Registration   ============================\n");
	printf("================================================================================\n");
	get_team(name, password, ':', &team_folder_no);
	
	integerNumberIntoString(team_folder_no, number_string);
	make_as_path(players_folder_path, TEAMS_PATH, number_string);
	join_as_path(players_folder_path, PLAYERS_FOLDER_NAME);
	
	Player * existed_players = load_players(players_folder_path);
	Player * player = NULL;
	
	get_the_player_name:
		printf("New Player's Name: ");
		scanf(" %[^\n]", player_name);
		namify(player_name);
		if(!check_name(player_name)) goto get_the_player_name;
		player = search_a_player_by_name(existed_players, player_name);
		if(player != NULL)
		{
			printf("Player named: %s already exist in the database !!!\n", player->name);
			goto get_the_player_name;
		}
	
	get_confirm_command:
		printf("Do you confirm? (Y:N)-> (1:0) :: for quit press 'q'\n");
		commando = getCommand(":");
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
		printf("Name Of The Match: ");
		scanf(" %[^\n]", name_of_the_match);
		
		if(name_of_the_match[0]=='#')	nopiet = 5;
		else nopiet = 11;
		namify(name_of_the_match);
		if(!check_name(name_of_the_match)) goto get_match_name;
		newl;
	//get_teams:
		get_team(team_name_A, password_A, 'A', &team_A_folder_no);
		newl;
		get_team(team_name_B, password_B, 'B', &team_B_folder_no);
		newl;
		integerNumberIntoString(team_A_folder_no, A_folder_no_string);
		integerNumberIntoString(team_B_folder_no, B_folder_no_string);

	make_as_path(A_folder_path, TEAMS_PATH, A_folder_no_string);
	make_as_path(B_folder_path, TEAMS_PATH, B_folder_no_string);

	Team * team_A = load_a_team(A_folder_path);
	Team * team_B = load_a_team(B_folder_path);

	team_A->teams_folder_no = team_A_folder_no;	strcpy(team_A->teams_folder_string, A_folder_no_string);
	team_B->teams_folder_no = team_B_folder_no;	strcpy(team_B->teams_folder_string, B_folder_no_string);

	get_overs:
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

	return( create_match(name_of_the_match, NULL, NULL, 0, 0, nopiet, total_overs, team_A, team_B, NULL, NULL) );
}



void burn_a_match_summary(Match * match, char *file_path)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	void burn_a_team_summary(Team * team, char * file_path)
	{
		FILE * file = fopen(file_path, "a");
		if(file==NULL) {fprintf(stderr, "Failed to open the file: %s in 'a' mode !!!\n", file_path); exit(1);}
		fprintf(file, "%s  :: %d/%d", team->name, team->total_runs, team->total_wickets);
		if(team->status == WON) fprintf(file, "    ***Winner***\n");
		else fprintf(file, "\n");
		fprintf(file, "Played Overs: %d\n\n", team->played_overs);
		
		Player * player = team->players;

		for(int i=1; player != NULL; i++)
		{
			fprintf(file, "%d. %s\n", i, player->name);
			fprintf(file, "%d\n", player->match_runs);
			if(player->out_or_not == OUT) fprintf(file, "OUT\n");
			else fprintf(file, "NOT OUT\n");
			fprintf(file, "\n");
			player = player->next;
		}
		fprintf(file, "***%s :: %d\n\n\n", team->man_of_the_team->name, team->man_of_the_team->match_runs);
		fclose(file);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	FILE * file = fopen(file_path, "a+");
	if(file==NULL) {fprintf(stderr, "Failed to open the file: %s in 'a+' mode !!!\n", file_path); exit(1);}
	fprintf(file, "Match Name: %s\n", match->name);
	fprintf(file, "Start Time: %s", match->starting_time);
	fprintf(file, "End   Time: %s", match->ending_time);
	fprintf(file, "Versus    : %s  vs  %s\n", match->team_A->name, match->team_B->name);
	if(match->status == DRAW) fprintf(file, "Match Status: Draw\n");
	else if(match->team_A->status == WON) fprintf(file, "Match Status: %s Won\n", match->team_A->name);
	else if(match->team_B->status == WON) fprintf(file, "Match Status: %s Won\n", match->team_B->name);
	else fprintf(file, "Match Status: Draw\n");
	
	fprintf(file, "\n");
	fclose(file);
	burn_a_team_summary(match->team_A, file_path);
	burn_a_team_summary(match->team_B, file_path);
}

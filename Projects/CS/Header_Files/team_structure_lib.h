#define TEAM_STRUCTURE_LIB_FILE_NAME      "team_structure_lib.h"

#define TEAMS_PATH		 	 	"./Teams"
#define TEAM_ENU_PATH    	 	"./Teams/teams.enu"
#define TEAM_NAMES_PATH  	 	"./Teams/teams.nm"
#define TEAM_INFO_FILE_NAME  	"team.inf"
#define TEAM_ENU_FILE_NAME   	"teams.enu"
#define TEAM_NAMES_FILE_NAME 	"teams.nm"


#define SUCCESS_TO_BURN_A_TEAMINFO 455
#define QUIT						-1
#define REGISTRATION_NOT_CONFIRMED   2
#define REGISTRATION_CONFIRMED		 1
#define REGISTRATION_FAILED			 0

// Match Related
#define BATTING 1000
#define BOWLING 2000
#define WON 	1001
#define LOST 	9009
#define DRAW    5005

typedef struct Team
{
	char 	 name[51];
	char 	 encoded_password[5];
	int  	 total_matches;
	int  	 total_wins;
	int  	 total_losts;
	int  	 total_draws;
	int  	 total_players;
	
	// Match related:
	int  teams_folder_no;
	char teams_folder_string[12];
	int played_overs;
	int extras;
	int total_runs;
	int total_wickets;
	int status;						// WIN LOST OR DRAW
	Player *man_of_the_team;
	//
	
	Player * players;
} Team;

Team * create_team(char *name, char *encoded_password, int total_matches, int total_wins, int total_losts, int total_draws, int total_players, Player *players)
{
	Team * new_team = (Team *) malloc(sizeof(Team));

	strcpy(new_team->name, name);
	strcpy(new_team->encoded_password,  encoded_password);
	new_team->total_matches = total_matches;
	new_team->total_wins 	= total_wins;
	new_team->total_losts	= total_losts;
	new_team->total_draws	= total_draws;
	new_team->total_players = total_players;
	new_team->players		= players;

	return new_team;
}

int checkExistenceOfTheTeam(char *name)
{
	char tname[51];
	int team_enu = get_enu(TEAM_ENU_PATH);	//.......................

	FILE *f = fopen(TEAM_NAMES_PATH, "r");		//.......................
	for(int i=1; i<=team_enu; i++)
	{
		fscanf(f, " %[^\n]", tname);
		if(!strcmp(tname, name)) return 1;
	}
	return 0;
}

Team * load_a_team(char *team_folder_path)
{
	char team_info_file_path[311];
	char players_folder_path[311];
	char name[51];
	char encoded_password[5];
	int total_matches;
	int total_wins;
	int total_losts;
	int total_draws;
	int total_players;
	
	make_as_path(team_info_file_path, team_folder_path, TEAM_INFO_FILE_NAME);
	
	FILE * team_info_file = fopen(team_info_file_path, "r");
	if(team_info_file == NULL)
	{
		fstderr(team_info_file_path, "r", TEAM_STRUCTURE_LIB_FILE_NAME, "load_a_team", "1");
		exit(1);
	}
	
	fscanf(team_info_file, " %[^\n]", name);
	fscanf(team_info_file, " %[^\n]", encoded_password);
	fscanf(team_info_file, "%d",	&total_matches);
	fscanf(team_info_file, "%d", 	&total_wins);
	fscanf(team_info_file, "%d", 	&total_losts);
	fscanf(team_info_file, "%d", 	&total_draws);
	fclose(team_info_file);
	
	make_as_path(team_info_file_path, team_folder_path, PLAYERS_FOLDER_NAME);
	join_as_path(team_info_file_path, PLAYERS_ENU_FILE_NAME);
	
	FILE * players_enu_file = fopen(team_info_file_path, "r");
	if(players_enu_file == NULL)
	{
		fstderr(team_info_file_path, "r", TEAM_STRUCTURE_LIB_FILE_NAME, "load_a_team", "2");
		exit(1);
	}
	
	fscanf(players_enu_file, "%d", &total_players);
	fclose(players_enu_file);
	
	Player * players;
	make_as_path(players_folder_path, team_folder_path, PLAYERS_FOLDER_NAME);
	players = load_players(players_folder_path);
	
	return create_team(name, encoded_password, total_matches, total_wins, total_losts, total_draws, total_players, players);
}

void display_a_team(Team *team)
{
	printf("Name: %s\n", team->name);
	printf("Total Matches: %d\n", team->total_matches);
	printf("Total Wins: %d\n", team->total_wins);
	printf("Total Losts: %d\n", team->total_losts);
	printf("Total Draws: %d\n", team->total_draws);
	printf("Total Players: %d\n", team->total_players);
	
	display_players(team->players);
}

int checkIfThePasswordMatch(char *name, char *team_encoded_password)
{
	char temp_name[51];
	char password[5];
	char number_string[11];
	char team_info_file_path[1010];
	int teams_enu = get_enu(TEAM_ENU_PATH);
	
	for(int i=1; i<=teams_enu; i++)
	{
		integerNumberIntoString(i, number_string);
		
		make_as_path(team_info_file_path, TEAMS_PATH, number_string);
		join_as_path(team_info_file_path, TEAM_INFO_FILE_NAME);
		
		FILE *team_inf_file = fopen(team_info_file_path, "r");
		if(team_inf_file==NULL)
		{
			fstderr(team_info_file_path, "r", TEAM_STRUCTURE_LIB_FILE_NAME, "checkIfThePasswordMatch()", "1");
			exit(1);
		}
		
		fscanf(team_inf_file, " %[^\n]", temp_name);
		if(strcmp(temp_name, name)!=0) continue;
		fscanf(team_inf_file, " %[^\n]", password);
		if(strcmp(password, team_encoded_password)==0) return i;
		
		fclose(team_inf_file);
	}
	return 0;
}


void burn_a_team_infos_into_the_file(Team *team, char *file_path)
{
	FILE * file = fopen(file_path, "w");
	if(file == NULL) 
	{
		fstderr(file_path, "w", TEAM_STRUCTURE_LIB_FILE_NAME, "burn_a_team_infos_into_the_file()", "1");
		exit(1);
	}
	
	fprintf(file, "%s\n", team->name);
	fprintf(file, "%s\n", team->encoded_password);
	fprintf(file, "%d\n", team->total_matches);
	fprintf(file, "%d\n", team->total_wins);
	fprintf(file, "%d\n", team->total_losts);
	fprintf(file, "%d\n", team->total_draws);
	
	fclose(file);
}

void create_team_folder(Team * team)
{
	
	void append_a_team_name_in_TNP(char *name)
	{
		FILE *team_names_file = fopen(TEAM_NAMES_PATH, "a+");
		if(team_names_file == NULL) 
		{
			fstderr(TEAM_NAMES_PATH, "a+", TEAM_STRUCTURE_LIB_FILE_NAME, "create_team_folder()", "1");
			exit(1);
		}
		fprintf(team_names_file, "%s\n", name);
		fclose(team_names_file);
	}

	// If the team already exists.
	if(checkExistenceOfTheTeam(team->name)) return;
	append_a_team_name_in_TNP(team->name);
	// First increase the team.enu by 1 and place the new team name into the teams.nm
	int teams_enu = get_enu(TEAM_ENU_PATH);
	set_enu(TEAM_ENU_PATH, ++teams_enu);
	
	
	// Make folder by teams_enu+1
	char teams_enu_string[11];
	char new_teams_folder_path[111];
	
	integerNumberIntoString(teams_enu, teams_enu_string);
	
	make_as_path(new_teams_folder_path, TEAMS_PATH, teams_enu_string);

	int status = makeFolder(new_teams_folder_path);
	if(status != SUCCESS_TO_CREATE_FOLDER)
	{
		fstderr(new_teams_folder_path, "making the folder", TEAM_STRUCTURE_LIB_FILE_NAME, "create_team_folder()", "2");
		exit(1);
	}
	
	
	// Produce a team info file. team.inf and burn infos.
	char team_info_file_path[211];
	make_as_path(team_info_file_path, new_teams_folder_path, TEAM_INFO_FILE_NAME);
	
	burn_a_team_infos_into_the_file(team, team_info_file_path);
	
	// Make a Players folder for players informations.
	char players_folder_path[211];
	make_as_path(players_folder_path, new_teams_folder_path, PLAYERS_FOLDER_NAME);
	
	status = makeFolder(players_folder_path);
	if(status != SUCCESS_TO_CREATE_FOLDER)
	{
		fstderr(players_folder_path, "making the folder", TEAM_STRUCTURE_LIB_FILE_NAME, "create_team_folder()", "3");
		exit(1);
	}
	
	// Produce players.enu file.
	char players_enu_file_path[311];
	make_as_path(players_enu_file_path, players_folder_path, PLAYERS_ENU_FILE_NAME);
	
	set_enu(players_enu_file_path, team->total_players);
	
	// Produce all the players from team->players structure.
	if(team->total_players==0 || team->players==NULL) return;
	burn_all_the_players_in_range(team->players, 1, team->total_players, players_folder_path);
	
}

// Counting total players in the players linked list.
int count_total_players(Player *players)
{
	int count = 0;
	Player * current_player = players;
	while(current_player != NULL)
	{
		count++;
		current_player = current_player->next;
	}
	return count;
}


// Getting password type.
void get_a_password(char *password)
{
	get_password:
		printf("Enter a password::(4 length): ");
		scanf(" %s", password);
		if(strlen(password) != 4) goto get_password;
}

// Registration of a team.
int register_a_team()
{
	int getCommand()
	{
		printf(":: ");
		getchar();
		return getchar();
	}
	clrscr();
	printf("================================================================================\n");
	printf("===========================  Team Registration  ================================\n");
	printf("================================================================================\n");
	
	char command;
	char name[51];
	char player_name[51];
	char password[5];
	char _password_[5];
	int total_players;
	Player * players = NULL;
	Player * new_player = NULL;
	
	get_name:
		printf("Team Name: ");
		scanf(" %[^\n]", name);
		namify(name);
		if(checkExistenceOfTheTeam(name)) 
		{
			printf("A team named %s already exists !\n", name);
			goto get_name;
		}
		if(!check_name(name))	goto get_name;
	
	get_total_players:
		printf("Total Players: ");
		scanf("%d", &total_players);
		if(total_players < 0 || total_players > 20) goto get_total_players;
	
	get_players_names:
		newl;
		printf("Players Names: \n");
		for(int i=1; i<=total_players; i++)
		{
			get_the_player_name:
			printf("%d. ", i);
			scanf(" %[^\n]", player_name);
			namify(player_name);
			if(!check_name(player_name)) goto get_the_player_name;
			new_player = create_player(player_name, 0, 0, 0, NULL);
			players = prepend_player(players, new_player);
		}
		
		get_names_confirmation_command:
		newl;
		printf("Do you want to keep these players names? (Y:N) --> (1:0)\n");
		command = getCommand();
		if(command == '0') goto get_players_names;
		else if(command != '1') goto get_names_confirmation_command;
		
	get_passwords:
		newl;
		get_a_password(password);
		newl;
		printf("Give the above password again:\n");
		get_a_password(_password_);
		
		if(strcmp(_password_, password))
		{
			printf("Didn't match, try again.\n");
			goto get_passwords;
		}
		encode_by_3_left(_password_);
	confirmation:
		newl;
		newl;
		printf("Do you confirm? (Y:N) --> (1:0)\n");
		command = getCommand();
		if(command == '0') return REGISTRATION_NOT_CONFIRMED;
		else if(command != '1') goto confirmation;
		else
		{
			Team * new_team;
			new_team = create_team(name, _password_, 0, 0, 0, 0, total_players, players);
			create_team_folder(new_team);
		}
		return REGISTRATION_CONFIRMED;
	return REGISTRATION_FAILED;
}

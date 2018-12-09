#define PLAYER_STRUCTURE_LIB_FILE_NAME "player_structure_lib.h"

#define PLAYERS_ENU_FILE_NAME 	"players.enu"
#define PLAYERS_FOLDER_NAME		"Players"
#define SUCCESS_TO_BURN_A_PLAYEINFO 555
#define OUT     0
#define NOT_OUT 1


typedef struct Player Player;
struct Player
{
	char name[51];
	int total_played_match;
	int total_runs;
	double average_runs;
	
	// Match related
	int match_runs;
	int status;
	char out_or_not;						// In the current match out or not.
	
	// Folder no string...
	char folder_nos[20];
	Player *next;
};

Player * create_player(char *name, int total_played_match, int total_runs, double average_runs, Player *next)
{
	Player *new_player = (Player *) malloc(sizeof(Player));
	if(new_player == NULL) 
	{
		fprintf(stderr, "Failed to create new_player !!\n");
		exit(1);
	}

	strcpy(new_player->name, name);
	new_player->total_played_match = total_played_match;
	new_player->total_runs 		   = total_runs;
	new_player->average_runs       = average_runs;
	new_player->next 	   		   = next;
	
	return new_player;
}

Player * prepend_player(Player *root, Player *new_player)
{
	if(root == NULL) return new_player;
	if(new_player == NULL) return root;
	new_player->next = root;
	return new_player;
}

Player * find_prev_player(Player *root, Player *p)
{
	if(root == p) return NULL;
	
	Player *current_player = root;
	while(current_player->next != NULL)
	{
		if( current_player->next == p ) return current_player;
		current_player = current_player->next;
	}
	
	return NULL;
}

Player * load_player(char *file_path)
{
	char name[51];
	int total_runs;
	int total_played_match;
	double average_runs;
	//**********************************//
	FILE *file = fopen(file_path, "r");
	if(file == NULL)
	{
		fstderr(file_path, "r", PLAYER_STRUCTURE_LIB_FILE_NAME, "load_player()", "1");
		exit(1);
	}
	
	fscanf(file, " %[^\n]", name);
	fscanf(file, "%d", &total_played_match);
	fscanf(file, "%d", &total_runs);
	fscanf(file, "%lf", &average_runs);
	fclose(file);
	

	return create_player(name, total_played_match, total_runs, average_runs, NULL);
}

void burn_a_player_infos_into_the_file(Player *player, char *file_path)
{
	//**********************************//
	FILE *file = fopen(file_path, "w");
	if(file == NULL)
	{
		fstderr(file_path, "w", PLAYER_STRUCTURE_LIB_FILE_NAME, "burn_a_player_infos_into_the_file()", "1");
		exit(1);
	}
	fprintf(file, "%s\n", player->name);
	fprintf(file, "%d\n", player->total_played_match);
	fprintf(file, "%d\n", player->total_runs);
	fprintf(file, "%.3lf\n", player->average_runs);
	fclose(file);
}


void burn_all_the_players_in_range(Player *players, int left, int right, char *players_folder_path)
{
	char player_file_path[321];
	char number_string[13];
	Player *current_player = players;
	
	for(int i=left; i<=right && current_player != NULL; i++)
	{
		integerNumberIntoString(i, number_string);
		make_as_path(player_file_path, players_folder_path, number_string);
		burn_a_player_infos_into_the_file(current_player, player_file_path);
		current_player = current_player->next;
	}
}

Player * update_player_info_according_to_the_match(Player *player, char *player_info_path)
{
	if(player == NULL) return NULL;
	
	player->total_runs += player->match_runs;
	player->total_played_match++;
	player->average_runs = ((player->total_runs)*1.0)/(player->total_played_match);
	
	burn_a_player_infos_into_the_file(player, player_info_path);
	
	return player;
}


Player * update_players_infos(Player * players, char *player_folder_path)
{	
	char * file_path;
	Player * current_player = players;
	
	while(current_player != NULL)
	{
		printf("# current_player->folder_nos: %s\n", current_player->folder_nos);
		file_path = generate_string_space(
						strlen(player_folder_path)+
							strlen(current_player->folder_nos)+
								5
					);
		
		make_as_path(
			file_path, player_folder_path,
				current_player->folder_nos
		);
		
		printf("## going to update %s's information in path: %s\n\n", current_player->name, file_path);
		update_player_info_according_to_the_match(
				current_player, file_path);
		free(file_path);
		current_player = current_player->next;
	}
	return players;
}
	
Player * swap_players(Player *root, Player *p1, Player *p2)
{
	if(root == NULL ||  root->next == NULL) return root;
	else if(p1 == p2) 
	{
		printf("Unswapped! Two players have same address!\n");
		return root;
	}
	else if(p1 == NULL || p2 == NULL) 
	{
		printf("Sorry! One of the player is NULL!\n");
		return root;
	}
	else if(root == p1)
	{	Player *prev_p2 = find_prev_player(root, p2);
		if(prev_p2 == NULL) 
		{
			printf("p2's prev is NULL\n");
			return root;
		}
		
		Player *root_next = root->next;
		root->next  = p2->next;
		if(root_next != p2) p2->next    = root_next;
		else p2->next = root;
		if(prev_p2 != root) prev_p2->next = root;
		
		return p2;
	}
	else if(root == p2)
	{
		Player *prev_p1 = find_prev_player(root, p1);
		if(prev_p1 == NULL) 
		{
			printf("p1's prev is NULL\n");
			return root;
		}
		Player *root_next = root->next;
		root->next = p1->next;
		if(root_next != p1) p1->next   = root_next;
		else p1->next = root;
		if(prev_p1 != root) prev_p1->next = root;
		
		return p1;
	}
	else if(p1->next == p2)
	{
		Player *prev_p1 = find_prev_player(root, p1);
		if(prev_p1 == NULL) 
		{
			printf("p1's prev is NULL\n");
			return root;
		}
		p1->next = p2->next;
		p2->next = p1;
		if(prev_p1 != NULL) prev_p1->next = p2;
	}
	else if(p2->next == p1)
	{
		Player *prev_p2 = find_prev_player(root, p2);
		if(prev_p2 == NULL) 
		{
			printf("p2's prev is NULL\n");
			return root;
		}
		p2->next = p1->next;
		p1->next = p2;
		prev_p2->next = p1;
	}
	else
	{
		Player *prev_p1 = find_prev_player(root, p1);
		if(prev_p1 == NULL) 
		{
			printf("p1's prev is NULL\n");
			return root;
		}
		Player *prev_p2 = find_prev_player(root, p2);
		if(prev_p2 == NULL) 
		{
			printf("p2's prev is NULL\n");
			return root;
		}

		Player *p1_next = p1->next;
		p1->next     = p2->next;
		p2->next     = p1_next;
		prev_p1->next = p2;
		prev_p2->next = p1;
	}

	return root;
}

void display_players(Player *root)
{
	//clrscr();
	
	Player *current_player = root;
	int count = 1;
	while(current_player != NULL)
	{
		newl;s4;s4;printf("%d:\n", count++);
		newl;s4;s4;printf("Name: %s\n", current_player->name);
		//printf("average: %.2lf\n", current_player->average_runs);
		current_player = current_player->next;
	}
	newl;
}

Player * insertion_sort_by_av(Player *root)
{
	Player *current = root->next;
	Player *next = current->next;
	Player *prev;
	
	while(current != NULL)
	{
		
		prev = find_prev_player(root, current);
		
		while(prev != NULL && prev->average_runs > current->average_runs)
		{
				root = swap_players(root, prev, current);
				prev = find_prev_player(root, current);
		}
		current = next;
		if(next != NULL) next = next->next;
	}
	return root;
}

Player * insertion_sort_by_match_runs(Player *root)
{
	Player *current = root->next;
	Player *next = current->next;
	Player *prev;
	
	while(current != NULL)
	{
		
		prev = find_prev_player(root, current);
		
		while(prev != NULL && prev->match_runs > current->match_runs)
		{
				root = swap_players(root, prev, current);
				prev = find_prev_player(root, current);
		}
		current = next;
		if(next != NULL) next = next->next;
	}
	return root;
}


Player *load_players(char *teams_player_path)
{
	char file_path[10002];
	char number_string[31];
	make_as_path(file_path, teams_player_path, PLAYERS_ENU_FILE_NAME);
	
	int players_enu = get_enu(file_path);
	
	Player *root = NULL;
	Player *new_player;
	for(int i=1; i<=players_enu; i++)
	{
		integerNumberIntoString(i, number_string);
		make_as_path(file_path, teams_player_path, number_string);
		
		if(!isExist(file_path)) continue;
		
		new_player = load_player(file_path);
		printf("# in load_players: number_string: %s\n", number_string);
		strcpy(new_player->folder_nos, number_string);
		printf("# in load_players: new_player->folder_nos: %s\n", new_player->folder_nos);
		root = prepend_player(root, new_player);
	}
	
	return root;
}

int same_player(Player *the_player, Player *root)
{
	Player *cp = root;
	while(cp != NULL)
	{
		if(cp == the_player) return 1;
		cp = cp->next;
	}
	return 0;
}

Player * search_a_player_by_name(Player *root, char *name)
{
	Player *current_player = root;
	while(current_player!=NULL)
	{
		if(!strcmp(current_player->name, name)) return current_player;
		current_player = current_player->next;
	}
	return current_player;
}

Player * copy_player(Player *player)
{
	Player * new_player = create_player( player->name, player->total_played_match, player->total_runs, player->average_runs, NULL);
	new_player->match_runs = player->match_runs;
	new_player->out_or_not = player->out_or_not;
	if(strlen(player->folder_nos)>0)
		strcpy(new_player->folder_nos, player->folder_nos);
	
	return new_player;
}


void free_players(Player * player)
{
	if(player != NULL)
	{
		free_players(player->next);
		free(player);
	}
}


int max_name_length_of_players(Player * players)
{
	int max_len = 0;
	Player * player = players;
	int len;
	while(player != NULL)
	{
		len = strlen(player->name);
		if(len > max_len) max_len = len;
		player = player->next;
	}
	return max_len;
}


Player * player_with_max_runs(Player *root)
{
	if(root == NULL) return NULL;
	Player * maxi    = root;
	Player * current = root->next;
	
	while(current != NULL)
	{
		if(current->match_runs > maxi->match_runs) maxi = current;
		current = current->next;
	}
	
	return maxi;
}
	
Player * reverse_player_list(Player * players)
{
	if(players->next == NULL) return players;
	
	Player * a = NULL;
	Player * b = players;
	Player * c = players->next;
	
	while(c != NULL)
	{
		b->next = a;
		a = b;
		b = c;
		c = c->next;
	}
	b->next = a;
	return b;
}

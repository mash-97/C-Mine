#define MATCH_STRUCTURE_LIB_FILE_NAME "match_structure_lib.h"

#define TEAM_A 'A'
#define TEAM_B 'B'
#define NOT_GIVEN "Not Given"

// Match Status && Innings
#define INITIALIZING  1010
#define RUNNING 	  1111
#define PAUSE   	  5555
#define FIRST_INNINGS 2222
#define LAST_INNINGS  6666
#define END			  9999

typedef struct Match
{
	char name[51];
	char starting_time[35];
	char ending_time[35];
	char toss_winner;					// TEAM_A OR TEAM_B
	char bat_first;						// TEAM_A OR TEAM_B
	int  total_overs;					// 1 <= overs <= 50
	int status;
	int innings;
	int NOPIET;							// number of players in each team in the match
	
	Team * team_A;						
	Team * team_B;	
		
	Team   * winner_team;				// team who won the match, NULL if draw.
	Player * man_of_the_match;			// Man who scored maximum.
	
} Match;

Match * create_match(char *match_name, char *strt_t, char *end_t, char ts_wnr, char bt_fst, int NOPIET, int tot_ov, Team *A, Team *B, Team 
	* winner, Player * mn_match)
{
	Match * new_match = (Match *) malloc(sizeof(Match));
	if(new_match == NULL)
	{
		fprintf(stderr, "Failed to create a new match !!!\n");
		exit(1);
	}
	
	if(match_name) strcpy(new_match->name, match_name);
	else strcpy(new_match->name, NOT_GIVEN);
	
	if(strt_t) strcpy(new_match->starting_time, strt_t);
	else strcpy(new_match->starting_time, NOT_GIVEN);
	 
	if(end_t) strcpy(new_match->ending_time, end_t);
	else strcpy(new_match->ending_time, NOT_GIVEN);
	
	new_match->toss_winner = ts_wnr; 
	new_match->bat_first = bt_fst;
	new_match->total_overs = tot_ov;
	new_match->team_A = A;
	new_match->team_B = B;
	new_match->winner_team = winner;
	new_match->man_of_the_match = mn_match;
	new_match->NOPIET = NOPIET;
	
	return new_match;
}


Match * create_a_void_match()
{
	Match * new_match = (Match *) malloc(sizeof(Match));
	if(new_match == NULL)
	{
		fprintf(stderr, "Failed to create a new match !!!\n");
		exit(1);
	}
	return new_match;
}

void display_match(Match * match)
{
	printf("Match name: %s\n", match->name);
	printf("Total Overs: %d\n", match->total_overs);
	printf("Starting Time: %s\n", match->starting_time);
	printf("Ending Time: %s\n", match->ending_time);
	
	if(match->team_A)
		printf("Team A: %s\n", match->team_A->name);
	if(match->team_B)
		printf("Team B: %s\n", match->team_B->name);
}

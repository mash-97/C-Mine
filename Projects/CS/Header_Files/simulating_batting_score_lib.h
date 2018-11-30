#define SIMUALTING_BATTING_SCORE_LIB_FILE_NAME "simulating_batting_score_lib.h"

enum INSTRUCTION { ONE_RUN = 1, TWO_RUNS = 2, THREE_RUNS = 3, FOUR_RUNS = 4, SIX_RUNS = 6, EXTRA = 5, STRIKER_OUT = 7, OVER = 8,  
SS = 9, HELP = 10, NOT_DEFINED = 11, SWAP = 12, DECLARED = 13, WIDE_BALL = 14, NO_BALL = 15};
typedef enum INSTRUCTION INSTRUCTION;

int instructify(char *stringus)
{
	lowerify(stringus);
	if(!strcmp(stringus, "1") || !strcmp(stringus, "one")) return ONE_RUN;
	else if(!strcmp(stringus, "2")  || !strcmp(stringus, "two")) return TWO_RUNS;
	else if(!strcmp(stringus, "3")  || !strcmp(stringus, "three")) return THREE_RUNS;
	else if(!strcmp(stringus, "4")  || !strcmp(stringus, "four")) return FOUR_RUNS;
	else if(!strcmp(stringus, "6")  || !strcmp(stringus, "six")) return SIX_RUNS;
	else if(!strcmp(stringus, "e")  || !strcmp(stringus, "extra")) return EXTRA;
	else if(!strcmp(stringus, "o")  || !strcmp(stringus, "out")) return STRIKER_OUT;
	else if(!strcmp(stringus, "ov") || !strcmp(stringus, "over")) return OVER; 
	else if(!strcmp(stringus, "ss")) return SS;
	else if(!strcmp(stringus, "h")  || !strcmp(stringus, "help")) return HELP;
	else if(!strcmp(stringus, "7")  || !strcmp(stringus, "swap")) return SWAP;
	else if(!strcmp(stringus, "declared")) return DECLARED;
	else if(!strcmp(stringus, "wide") || !strcmp(stringus, "w")) return WIDE_BALL;
	else if(!strcmp(stringus, "nb") || !strcmp(stringus, "no") || !strcmp(stringus, "no ball")) return NO_BALL;
	return NOT_DEFINED;
}


void print_match_header(Match *match)
{
	printf("================================================================================\n");
	printf("|| Match Name:  %s", match->name);print_spaces(80 - (strlen(match->name)+16+2)); printf("||\n");
	printf("|| %s vs %s", match->team_A->name, match->team_B->name);print_spaces(80 - (strlen(match->team_A->name)+strlen(match->team_B->name)+7+2));printf("||\n");
	printf("|| Total Overs: %d", match->total_overs);print_spaces(80-(log10(match->total_overs)+1+16+2));printf(" ||\n");
	printf("================================================================================\n");
}

void print_score_board(Match * match, Team * team)
{
	printf("%s ::", team->name);
	printf("%d/%d\n", team->total_runs, team->total_wickets);
	if(team->played_overs != 0) printf("Current Run Rate: %0.2lf\n", (double) (team->total_runs*1.0)/team->played_overs);
	printf("Overs: %d\n", team->played_overs);
	
	if(match->status == LAST_INNINGS)
	{
		if(match->bat_first == TEAM_A)
			printf("***To win needs %d runs\n", (match->team_A->total_runs+1) - team->total_runs);
		else 
			printf("**To win needs %d runs\n", (match->team_B->total_runs+1) - team->total_runs);
	}
	newl;
	
	Player * player = team->players;
	int max_len = max_name_length_of_players(player)+3;
	print_names_runs_label(max_len);
	int i = 1;
	int len;
	while(player != NULL)
	{
		printf("%2d. %s", i, player->name);
		len = strlen(player->name);
		if(player->out_or_not == NOT_OUT)
		{
			print_spaces((max_len-len)+4);
			printf("NOT OUT");
			print_spaces(4);
		}
		else
		{
			print_spaces((max_len-len)+6);
			printf("OUT");
			print_spaces(6);
		}
		printf("%4d\n", player->match_runs);
		player = player->next;
		i++;
	}
	newl;
	printf("Extras: %4d\n", team->extras);
	printf("Total : %4d\n", team->total_runs);
	newl;
}
	
void print_batting_header_label(Match * match, Team * team)
{
	printf("================================================================================\n");
	printf("%s :: %d/%d\n", team->name, team->total_runs, team->total_wickets);
	printf("Overs: %d\n", team->played_overs);
	if(match->innings == LAST_INNINGS)
	{
		if(match->bat_first == TEAM_A)
			printf("***To win needs %d runs\n", (match->team_A->total_runs+1) - team->total_runs);
		else 
			printf("**To win needs %d runs\n", (match->team_B->total_runs+1) - team->total_runs);
	}
	printf("================================================================================\n");
	newl;
}

// I like all these function...... :)
void swap_batsman(Player **striker, Player **slider)
{
	Player * batsman = *slider;
	*slider = *striker;
	*striker = batsman;
}
	
void swap_batsman_n_times(Player **striker, Player **slider, int times)
{
	for( int i=1; i<=times; i++)
		swap_batsman(&(*striker), &(*slider));
}


void add_runs_to_the_striker_and_team(Team *team, Player **striker, Player **slider, int runs)
{
	(*striker)->match_runs += runs;
	team->total_runs += runs;
	swap_batsman_n_times(&(*striker), &(*slider), runs);
}
// My favourites............................................


Player * get_new_batsman(Player *root_players, char *printo)
{
	char player_name[51];
	Player * batsman = NULL;
	get_batsman:
		printf("%s", printo);
		scanf(" %[^\n]", player_name);
		namify(player_name);
		if(!strcmp(player_name, "Show Players")) 
		{
			display_players(root_players);
			goto get_batsman;
		}
		if(!check_name(player_name)) goto get_batsman;
		batsman = search_a_player_by_name(root_players, player_name);
		
		if(batsman == NULL)
		{
			printf("Name doesn't exist in the player list !!!\n");
			goto get_batsman;
		}
		if(batsman->out_or_not == OUT || batsman->status == BATTING) goto get_batsman;
		batsman->match_runs = 0;
		batsman->out_or_not = NOT_OUT;
		batsman->status = BATTING;
	return batsman;
}

Team * simulate_batting_for_team(Match * match, Team * team)
{
	int max_name_length = max_name_length_of_players(team->players);
	// Initializing...
	team->played_overs  = 0;
	team->total_runs    = 0;
	team->total_wickets = 0;
	team->extras        = 0;
	//////////////////////////
	clrscr();
	print_match_header(match);
	print_batting_header_label(match, team);

	char commando;
	char stringus[10];
	int ex;
	int balls = 0;
	
	Player * striker = get_new_batsman(team->players, "1st Batsman Name: ");
	
	Player * slider = get_new_batsman(team->players, "2nd Batsman Name: ");
	
	clrscr();
	print_batting_header_label(match, team);
	print_instructions();
	
	
	
	
	INSTRUCTION instruction;
	get_instruction:
		if(match->innings == LAST_INNINGS)
		{
			if(match->team_A == team && team->total_runs > match->team_B->total_runs)
			{
				getchar();
				printf("\n\n *** *** *** Congratulation! %s won the match *** *** ***\n", team->name);
				getchar();
				
				clrscr();
				print_batting_header_label(match, team);
				print_score_board(match, team);
				getchar();
				return team;
			}
			
			if(match->team_B == team && team->total_runs > match->team_A->total_runs)
			{
				getchar();
				printf("\n\n *** *** *** Congratulation! %s won the match *** *** ***\n", team->name);
				getchar();
				
				clrscr();
				print_batting_header_label(match, team);
				print_score_board(match, team);
				getchar();
				return team;
			}
		}
		
		newl;
		printf("(%3d/%2d)::%s", team->total_runs, team->total_wickets, striker->name);
		print_spaces(max_name_length-strlen(striker->name));
		printf(" (%3d) >> ", striker->match_runs);
		scanf(" %[^\n]", stringus);
		
		instruction = instructify(stringus);
		
		if(balls == 7 && instruction != OVER)
		{
			balls = 0;
			team->played_overs++;
			printf("\n---An over is given---\n");
			if(team->played_overs==match->total_overs)
			{
					printf("!!!   -*- Over finished -*-   !!!\n");
					getchar();
					
					clrscr();
					print_batting_header_label(match, team);
					print_score_board(match, team);
					getchar();
					return team;
			}
		}
		
		switch(instruction)
		{
			case ONE_RUN:
				balls++;
				add_runs_to_the_striker_and_team(team, &striker, &slider, 1);
				goto get_instruction;
			break;
			
			case TWO_RUNS:
				balls++;
				add_runs_to_the_striker_and_team(team, &striker, &slider, 2);
				goto get_instruction;
			break;
			
			case THREE_RUNS:
				balls++;
				add_runs_to_the_striker_and_team(team, &striker, &slider, 3);
				goto get_instruction;
			break;
			
			case FOUR_RUNS:
				balls++;
				add_runs_to_the_striker_and_team(team, &striker, &slider, 4);
				goto get_instruction;
			break;
			
			case SIX_RUNS:
				balls++;
				add_runs_to_the_striker_and_team(team, &striker, &slider, 6);	
				goto get_instruction;
			break;
			
			case SWAP:
				swap_batsman(&striker, &slider);
				goto get_instruction;
			break;
			
			case OVER:
				balls = 0;
				swap_batsman(&striker, &slider);
				team->played_overs++;
				if(team->played_overs==match->total_overs)
				{
					printf("!!!   -*- Over finished -*-   !!!\n");
					getchar();
					
					clrscr();
					print_batting_header_label(match, team);
					print_score_board(match, team);
					getchar();
					return team;
				}
				goto get_instruction;
			break;
			
			case STRIKER_OUT:
				striker->out_or_not = OUT;
				team->total_wickets++;
				if(team->total_wickets==match->NOPIET-1)
				{
					printf("!!!   -*- All wickets gone -*-  !!!\n");
					getchar();
					
					clrscr();
					print_batting_header_label(match, team);
					print_score_board(match, team);
					getchar();
					return team;
				}
				striker = get_new_batsman(team->players, "New Batsman Name: ");
				striker->status = BATTING;
				striker->out_or_not = NOT_OUT;
				goto get_instruction;
			break;
			
			case SS:
				clrscr();
				print_batting_header_label(match, team);
				print_score_board(match, team);
				goto get_instruction;
			break;
			
			case DECLARED:
				clrscr();
				print_score_board(match, team);

				commando = getCommand("Are you sure you want to declare? (Y:N) -> (1:0)\n:");
				if(commando == '1')
				{
					clrscr();
					print_batting_header_label(match, team);
					printf("*** DECLARED ***\n");
					print_score_board(match, team);
					return team;
				}
				goto get_instruction;
			break;
			
			case HELP:
				clrscr();
				print_instructions(match, team);
				goto get_instruction;
			break;
			
			case EXTRA:
				printf("How much?\n");
				get_extra:
					ex = get_int(">>> ");
					if(ex<0 || ex>8) goto get_extra;
				
				team->total_runs += ex;
				team->extras += ex;
				goto get_instruction;
			break;
			
			case WIDE_BALL:
				team->total_runs += 1;
				team->extras += 1;
				goto get_instruction;
			break;
			
			case NO_BALL:
				team->total_runs += 1;
				team->extras += 1;
				goto get_instruction;
			break;
			
			default:
				printf("-_-`\n");
				goto get_instruction;
			break;
		}
	return team;
}


Match * simulate_the_match(Match *match)
{
	clrscr();
	
	print_match_header(match);
	match->status = INITIALIZING;
	char commando;
	printf("Who will bat first?    ( %s : 'A'  ::  %s : 'B' )\n\n", match->team_A->name, match->team_B->name);
	get_toss_command:
		commando = getCommand(":");
		if(!(commando == 'A' || commando == 'B')) goto get_toss_command;

	char decommando;
	get_decommando:
	newl;
	newl;
	decommando = getCommand("Start the match? (Y:N) -> (1:0)\n:");
	if(decommando == '0') return NULL;
	if(decommando != '1') goto get_decommando;
	// Setting up starting time.
	createCurrentDTsStringIntoArray(match->starting_time);
	// Initialization.....
	match->status  = RUNNING;
	match->innings = FIRST_INNINGS;
	if(commando == 'A')
	{
			match->bat_first = TEAM_A;
			match->team_A = simulate_batting_for_team(match, match->team_A);
			match->team_B->status = BATTING;
			match->team_A->status = BOWLING;
	}
	else if(commando == 'B')
	{
			match->bat_first = TEAM_B;
			match->team_B = simulate_batting_for_team(match, match->team_B);
			match->team_A->status = BATTING;
			match->team_B->status = BOWLING;
	}

	clrscr();
	printf("Start Last Innings...\n");
	getchar();
	getchar();
	match->innings = LAST_INNINGS;
	if(match->team_A->status == BATTING)
	{
		match->team_A = simulate_batting_for_team(match, match->team_A);
		if(match->team_A->total_runs  == match->team_B->total_runs)
		{
			match->team_A->status = DRAW;
			match->team_B->status = DRAW;
		}
		else if(match->team_A->total_runs  > match->team_B->total_runs)
		{
			match->team_A->status = WON;
			match->team_B->status = LOST;
		}
		else
		{
			match->team_A->status = LOST;
			match->team_B->status = WON;
		}
	}
	else if(match->team_B->status == BATTING)
	{
		match->team_B = simulate_batting_for_team(match, match->team_B);
		if(match->team_A->total_runs  == match->team_B->total_runs)
		{
			match->team_A->status = DRAW;
			match->team_B->status = DRAW;
			match->winner_team    = NULL;
		}
		else if(match->team_A->total_runs  > match->team_B->total_runs)
		{
			match->team_A->status = WON;
			match->team_B->status = LOST;
			match->winner_team    = match->team_A;
		}
		else
		{
			match->team_A->status = LOST;
			match->team_B->status = WON;
			match->winner_team    = match->team_B;
		}
	}

	match->team_A->man_of_the_team = player_with_max_runs(match->team_A->players);
	match->team_B->man_of_the_team = player_with_max_runs(match->team_B->players);
	if(match->team_A->status == WON) match->man_of_the_match = match->team_A->man_of_the_team;
	else if(match->team_B->status == WON) match->man_of_the_match = match->team_B->man_of_the_team;
	else
	{
		if(match->team_A->man_of_the_team->match_runs > match->team_B->man_of_the_team->match_runs)
			match->man_of_the_match = match->team_A->man_of_the_team;
		else if(match->team_A->man_of_the_team->match_runs < match->team_B->man_of_the_team->match_runs)
			match->man_of_the_match = match->team_B->man_of_the_team;
		else match->man_of_the_match = NULL;
	}
	createCurrentDTsStringIntoArray(match->ending_time);
	return match;
}

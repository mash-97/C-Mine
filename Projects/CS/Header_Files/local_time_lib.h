#define LOCAL_TIME_LIB_FILE_NAME "local_time_lib.h"

char *currentDate(char date[14]);
typedef struct Local_Time 
{
	char day[4];
	char month_name[4];
	char time[9];
	int Day;
	int Month;
	int hour;
	int minute;
	int second;
	int Year;
	int Date;
	char date[3];
	char month[4];
	char year[5];
} Local_Time;

//A function to create current date & times string.
char *createCurrentDTsString(){
	static char *dtString;
	time_t dateTime;
	dateTime = time(NULL);
	dtString = ctime(&dateTime);
	return dtString;
}
//A function to creat current date & times string.
void createCurrentDTsStringIntoArray(char string[]){
	char *dtString;
	time_t dateTime;
	dateTime = time(NULL);
	dtString = ctime(&dateTime);
	strcpy(string, dtString);
}
//***String of Time into Local_Time struct***//
Local_Time getSpecsOf(char timeString[]){
	Local_Time specs;
	char month[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct","Nov", "Dec"};
	char day[7][4] = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};
	int i, length = strlen(timeString), iswordstarted = 0, wordcounter = 0, j=0, k;
	static char buffer[10];
	for(i=0; i<length; i++)
	{
		if((timeString[i] >= 'A' && timeString[i] <= 'Z') || (timeString[i] >= 'a' && timeString[i] <= 'z') || (timeString[i] >= '0' && timeString[i] <= '9') || (timeString[i]==':'))
		{
			if(iswordstarted==0)
			{
				iswordstarted = 1;
			}
			buffer[j] = timeString[i];
			j++;
		}
		else
		{
			if(iswordstarted==1)
			{
				iswordstarted=0;
				buffer[j]='\0';
				
				j=0;
				wordcounter++;
				
				if(wordcounter==1)
				{
					strcpy(specs.day, buffer);
					for(k=0; k<7; k++)
					{
						if(strcmp(buffer,day[k])==0)
						{
							specs.Day = k+1;
						}
					}
				}
				else if(wordcounter==2) 
				{
					strcpy(specs.month_name,  buffer);
					for(k=0; k<12; k++)
					{
						if(strcmp(buffer,month[k])==0)
						{
							specs.Month = k+1;
							integerNumberIntoString(k+1, specs.month);
						}
					}
				}
				else if(wordcounter==3) 
				{
					strcpy(specs.date, buffer);
					if(strlen(buffer)==2)
					{
						specs.Date = (buffer[1]-'0')+(buffer[0]-'0')*10;
					}
					else specs.Date = buffer[0]-'0';
					
				}
				else if(wordcounter==4) 
				{
					strcpy(specs.time, buffer);
					
				}
				else 
				{
					strcpy(specs.year, buffer);
					specs.Year = (buffer[3]-'0')+(buffer[2]-'0')*10+(buffer[1]-'0')*100+(buffer[0]-'0')*1000;
					
				}
			}
		}
	}
	length = strlen(specs.time);
	wordcounter = 0;
	iswordstarted = 0;
	j = 0;
	for(i=0; i <= length; i++)
	{
		if(specs.time[i] >= '0' && specs.time[i] <= '9')
		{
			if(iswordstarted==0)
			{
				iswordstarted = 1;
			}
			buffer[j] = specs.time[i];
			j++;
		}
		else
		{
			if(iswordstarted==1)
			{
				iswordstarted = 0;
				j = 0;
				wordcounter++;
				if(wordcounter==1) specs.hour = (buffer[1]-'0')+(buffer[0]-'0')*10;
				else if(wordcounter==2) specs.minute = (buffer[1]-'0')+(buffer[0]-'0')*10;
				else specs.second = (buffer[1]-'0')+(buffer[0]-'0')*10;
			}
		}
	}
	return specs;
}

// Create a Local Time:
Local_Time * get_local_time()
{
	Local_Time * local_time = (Local_Time *) malloc(sizeof(Local_Time));
	char string[111];
	createCurrentDTsStringIntoArray(string);
	Local_Time loct = getSpecsOf(string);
	
	strcpy(local_time->day, loct.day);
	strcpy(local_time->month_name, loct.month_name);
	strcpy(local_time->time, loct.time);
	local_time->Day   	= loct.Day;
	local_time->Month 	= loct.Month;
	local_time->hour  	= loct.hour;
	local_time->minute 	= loct.minute;
	local_time->second 	= loct.second;
	local_time->Year   	= loct.Year;
	local_time->Date   	= loct.Date;
	strcpy(local_time->date, loct.date);
	strcpy(local_time->month, loct.month);
	strcpy(local_time->year,  loct.year);
	
	return local_time;
}

//A function to pass the Date string.
void createCurrentTime(char time[10]){
	struct Local_Time currentDT = getSpecsOf(createCurrentDTsString());
	strcpy(time, currentDT.time);
}


//Displaying Date& Time.
void displayCurrentDateTime(){
	char *dtString;
	time_t dateTime;
	dateTime = time(NULL);
	dtString = ctime(&dateTime);
	printf("Current Time::\n(DD MM Date HH:MIN:SEC YY\n%s\n", dtString);
	
}

//A function to pass the Date string.
void createCurrentDate(char date[14]){
	struct Local_Time currentDT = getSpecsOf(createCurrentDTsString());
	char currDate[20];
	currDate[0] = 0;
	
	strcat(currDate, currentDT.date);
	strcat(currDate, ":");
	
	strcat(currDate, currentDT.month);
	strcat(currDate, ":");
	
	strcat(currDate, currentDT.year);
	strcpy(date, currDate);
}

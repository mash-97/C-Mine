#if defined(_WIN32) || defined(_WIN64)
	#define clrscr() system("cls")
#else 	
	#define clrscr() system("clear")
#endif


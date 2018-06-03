#include <stdio.h>
#include <stdbool.h>
#define swap(value_1,value_2, position_1,position_2) {int i=value_1, j=position_1; value_1=value_2; value_2=i; position_1=position_2; position_2=j;}
#define SIZE 500

int n_o_p = 0;
int array[SIZE][2];

int pushToTheArray(int number, int position, int mean_position, bool by_v, bool by_p)
{	
	static int flag = 0;
	//printf("flag = %d\n", flag);
	if(mean_position < 0 || mean_position > n_o_p){flag = 0; return 0;}
	
	if(flag==0){
		array[mean_position][0] = number, array[mean_position][1] = position; flag=1;
	}
	if(mean_position==0){flag = 0;  return 1;}
	if(array[mean_position-1][0] > number && by_v==1){flag = 0; return 1;}
	if(array[mean_position-1][1] > position && by_p==1){flag = 0; return 1;}
	else
	{
		swap(array[mean_position-1][0], array[mean_position][0], array[mean_position-1][1], array[mean_position][1]);
		
		pushToTheArray(number, position, --mean_position, by_v, by_p);
	}
	
	flag = 0;
	return 1;
}

int main()
{
	n_o_p = 0;
	
	int N, number;
	int a,b;
	scanf("%d%d%d", &N, &a, &b);
	
	for(int i=0; i<N; i++)
	{
		scanf("%d", &number);
		pushToTheArray(number, i, n_o_p++, a, b);
	}
	
	puts("");
	printf("The Global array is with position: \n");
	for(int i=0; i<n_o_p; i++)
	printf("%d %d\n", array[i][0], array[i][1]);
	
	main();
	return 0;
}

		

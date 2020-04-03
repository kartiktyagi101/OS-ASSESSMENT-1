#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Pro{ 
int At,Bt,Wt,Tt;
	char name[4];
};
struct Pro initialize(int At,int Bt,int name)
{ 
	struct Pro obj;
	obj.Bt = Bt;
	obj.At = At;
	sprintf(obj.name,"P%d",name+1);
	return obj;
}
int main(){
	FILE *fp = fopen("CPU_BURST.txt","w+");
	printf("Enter 5 burst time\n ");
	rewind(fp);
	char Burst[50];
	gets(Burst);
	fprintf(fp,"%s",Burst);
	fclose(fp);
	FILE *f = fopen("CPU_BURST.txt","r");
	if(!f)
		return -1*printf("FILE OPEN ERROR!\n");

    int d,i,j,Counter=0;
    int *list = (int*)malloc(sizeof(int));
    while(EOF != fscanf(f,"%d ",&d ))
	{
    	list = (int*)realloc(list,(Counter+1)*sizeof(int));
    	list[Counter++] = d;
    }
    fclose(f);

	struct Pro P[Counter];
	for(i=0; i<Counter; i++)
		P[i] = initialize(0,list[i],i);
	for(i=1; i<Counter; i++){
		for(j=0; j<Counter-i; j++){
			if(P[j].Bt>P[j+1].Bt){
				struct Pro temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
	printf("\nOrder : ");
	int elapsed_time=0;
	for(i=0; i<Counter; i++){
		P[i].Wt = elapsed_time;
		P[i].Tt= P[i].Wt+P[i].Bt;
		elapsed_time += P[i].Bt;
		printf("%s ",P[i].name);
	}
	printf("\n\n%7s|%8s|%6s|%5s|%s\n","PROCESS","ARRIVAL","BURST","WAIT","TURNAROUND");
	int ToTaL_WaitTime=0,ToTaL_TurnAroundTime=0;
	for(i=0; i<Counter; i++){
		ToTaL_WaitTime+=P[i].Wt;
		ToTaL_TurnAroundTime+=P[i].Tt;
		printf("%7s|%8d|%6d|%5d|%9d\n",P[i].name,P[i].At,P[i].Bt,P[i].Wt,P[i].Tt);
	}
	printf("\nAverage Waiting Time     : %.2f\n",ToTaL_WaitTime*1.0/Counter);
	printf("\nAverage Turn Around Time : %.2f\n",ToTaL_TurnAroundTime*1.0/Counter);
	return 0;
}

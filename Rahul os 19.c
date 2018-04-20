#include<semaphore.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdio.h>
#define MAX_RESOURCES 5
sem_t m1;
sem_t m2;
int available_resources=MAX_RESOURCES;
/*decrease available resources by count resources*/
void *decrease_count(void *coun)
{	int *count =coun;
    	sem_wait(&m1);
		while(available_resources<*count)
		printf("\n Client is Waiting to get %d Licences Because Available Resource is %d ",*count,available_resources);
		available_resources-=*count;
		printf("\n Number of Licence issued to new Client is %d .\nRemaining Licences are %d  ",*count,available_resources);
		sem_post(&m1);
		increase_count(*count);
}
int increase_count(int coun)
{     	sem_wait(&m2);  
		int count =coun;
		available_resources+=count;
		printf(" \nNumber of Licence Expired are %d . \nAvailability Of lisence Increased to %d \n",count,available_resources);
		sem_post(&m2);
		
}
int main()
{   
	
   printf("\n                       ||     -----WELCOME-----     ||");

 
 getch();
	sem_init(&m1,0,1);
	sem_init(&m2,0,1);
	pthread_t no_of_client[100];
	int count[100];
	int clients,i;
	printf("\nEnter the no. of license holder's you want:\t");
	scanf("%d",&clients);
	for(i=0;i<clients;i++)
	{
		printf("\n Enter Number of Licence holders %d wants :\t",i+1);
		scanf("%d",&count[i]);
		if(count[i]>available_resources)
		{
			printf("\nERROR-----ERROR----ERROR\n");
		printf("\nERROR-----LIMIT EXCEDDED-----ENTER IN LIMIT\n");
		i=i-1;
	}
	}
	for(i=0;i<clients;i++)
	{
		pthread_create(&no_of_client[i],NULL,decrease_count,&count[i]);
	}
	for( i=0;i<clients;i++)
	{
		pthread_join(no_of_client[i],NULL);
	}
}


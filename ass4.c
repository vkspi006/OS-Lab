#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int size,cnt=0,c,start,stop,tno_f,tno;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int *data;
void *fnc(void *ptr)
{
	int i,x,y;
	int *ptr2 = (int *)ptr;
	//---------------------------------------calculating start and end of each thread-------------------------------------------------------
	c=(size+1)/tno;
	x=(*ptr2)*c;
	y = ((*ptr2+1)*c)-1;
	if(*ptr2==tno-1)
			y = size-1;
	//-----------------------------------------------------------------------------------------------------------------------------------------
	//printf("%d-> %d %d\n",*ptr2,x,y);
	for(i=x;i<=y;i++)
	{
		if(data[i]==3)
		{
			pthread_mutex_lock (&mutex1);
			cnt=cnt+1; //counting number of 3's in input file
			pthread_mutex_unlock (&mutex1);
		}
	}
	return;
}
int main()
{
	int i;
	size=0;
	scanf("%d",&tno);
	scanf("%d",&size);
	int arr[size], a[tno];
	int x = 0,t1,t2;
	t1=clock();
	while(x<size)
	{
		scanf("%d",&arr[x]); //storing elements in array
		x++;
	}
	data = arr;
	for(i=0;i<tno;i++)
		a[i]=i;
	pthread_t thread[tno]; //declaring number of threads	
	for(i=0;i<tno;i++)
	{
		pthread_create(&thread[i], NULL, &fnc, (void *)&a[i]); //creating threads and passing thread number
	}
	for(i=0;i<tno;i++)
		pthread_join(thread[i], NULL); // join threads
	printf("number of 3's in input file: %d\n",cnt);
	t2=clock();
	double overall=(((double)(t2-t1))/CLOCKS_PER_SEC); //calculating time
	printf("over all time is %lf\n",overall); //printing time
	//------------------------------------------------------wrinting output in file---------------------------------------------------
	FILE *fp=fopen("out.txt","a+");
	char temp1[20],temp2[20];
	sprintf(temp1,"%d",tno);
	sprintf(temp2,"%lf",overall);
	strcat(temp1," "); strcat(temp1,temp2); strcat(temp1," \n");
	int ss=strlen(temp1);
	char temp3[ss];
	strcpy(temp3,temp1);
	fwrite(temp3,sizeof(char),sizeof(temp3),fp); 
	close(fp);
	//-----------------------------------------------------------------------------------------------------------------------------------
	return 0;
}

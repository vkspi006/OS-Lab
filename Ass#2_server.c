
                                                    //#OS_LAB-2_SERVER

/*Server will return list of files present in directory to client,and client will select one of the file and request to the server to 
send on request of client the server will fork() a child process to handle the file transfer smoothly with that specific client. 
Statistics about each transfer session (e.g. number of send(), total bytes transferred,client ID, file name, time taken to transfer 
the whole file etc.) will  be stored in the newly created file logfile.txt in the server).  Here socket programming related systems 
calls used in the client server file. 
Here server can connect multiple to the multiple clients during the execution to check whether fork() is working properly or not.*/

//arguments reqquired------  The port number is passed as an argument
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main( int argc, char *argv[] ){
	if( argc > 3 || argc <2)
	{
	      printf("There will be must all required arguments");
	}

	int sockid,newSocket,status,s,count,sum,num,i;


		char buffer[1024];
		char buffer1[1024];
		struct sockaddr_in addrport;
		struct sockaddr_storage serverStorage;
		socklen_t addr_size;

		addrport.sin_family = AF_INET;
		addrport.sin_port = htons(atoi(argv[2])); 
		addrport.sin_addr.s_addr = inet_addr(argv[1]); 
		memset(addrport.sin_zero, '\0', sizeof addrport.sin_zero);  

		if((sockid = socket(PF_INET,SOCK_STREAM,0)) <0)      /* creating socket */
 
		{
			printf("Error in creating socket");
			goto error;	
		}
		printf("\nSocket created");      /* port number to listen on   */
		if(bind(sockid,(struct sockaddr *) &addrport, sizeof(addrport))!=0)
		{
				printf("Binding Failed");
				return 0;
		}
		else
		{
						/* bind socket to this port number on this machine */
			printf("\nBind Successful...");

			status = listen(sockid,10);
			if(status < 0 )
			{ 
				printf("Listen failed");
				goto error;		
			}
			printf("\nListening...\n");
						/* listen for incoming connection requests */
			addr_size = sizeof serverStorage;
			while(1)
			{
				if((s = accept(sockid, (struct sockaddr *) &serverStorage, &addr_size))<0)
				{
					printf("Accept failed");
					goto error;		
				}
				printf("Connected ! \n");
						/* accept a new request, create a new sockfd */
				int pid = fork();
				if(pid>0)
				{
					struct timeval t1;
					FILE *log1 = fopen("log.txt","a+");
					if(log1==NULL)
					{
						printf("logging couldn't be enabled\n");
						exit(1);
					}
					time_t rawtime;
					char data[50];
					memset(data,'\0',50);
					struct tm * timeinfo;
					time ( &rawtime );
					timeinfo = localtime ( &rawtime );
					strcpy(data,asctime(timeinfo));	
					fprintf(log1,"%s ---> list transfered successfully\n",data);
					fclose(log1);
					send_list(s);
					char p[1024];
					memset(p,'\0',1024);
					read(s,(char *)&p,sizeof(p));
					FILE *log2 = fopen("log.txt","a+");
					if(log2==NULL)
					{
						printf("logging couldn't be enabled\n");
						exit(1);
					}
					time ( &rawtime );
					memset(data,'\0',50);
					timeinfo = localtime ( &rawtime );
					strcpy(data,asctime(timeinfo));	
					fprintf(log2,"%s ---> %s File transfer requested\n",data,p);
					fclose(log2);
					long long int d1 = send_file(s,p);
					time ( &rawtime );
					memset(data,'\0',50);
					timeinfo = localtime ( &rawtime );
					strcpy(data,asctime(timeinfo));	
					FILE *log3 = fopen("log.txt","a+");
					if(log3==NULL)
					{
						printf("logging couldn't be enabled\n");
						exit(1);
					}
					fprintf(log3,"%s ---> %s File transfered successfully ---[%lld bytes]\n",data,p,d1);
					fclose(log3);
				}
			}
		}

		error:
		close(s); 
		close(sockid);
		
return 0;
	


}

void send_list(int s)
{
	system("ls > temp_.txt");
	FILE *f = fopen("temp_.txt","r");
	char data[1024];
	int ctr=0;
	if(f==NULL)
	{
		printf("Couldn't send the list\n");
		system("rm temp_.txt");
		return;
			}
			do
			{
				memset(data,'\0',1024);
				ctr = fread(data,1,1024,f);
				write(s,data,ctr);

	}while(ctr==1024);
				system("rm temp_.txt");
				memset(data,'\0',1024);
				strcpy(data,"finished");
				write(s,data,1024);
}
long long int send_file(int s,char name[])
{
	FILE *f = fopen(name,"r");
	char data[1024];
	int ctr=0;
	long long int d1=0;
	if(f==NULL)
	{
		printf("Couldn't send the list\n");
		return 0;
	}
	do
	{
		memset(data,'\0',1024);
		ctr = fread(data,1,1024,f);
		d1 += ctr;
		printf("%s",data);
		write(s,data,ctr);
				}while(ctr==1024);
				memset(data,'\0',1024);
				strcpy(data,"finished");

				time_t rawtime;
				struct tm * timeinfo;
				time ( &rawtime );
				timeinfo = localtime ( &rawtime );
				strcpy(data,asctime(timeinfo));	

				write(s,data,32);
				printf("%s\n",data);
			return d1;
}



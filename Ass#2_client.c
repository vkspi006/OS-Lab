
                                            //#OS_LAB--2_CLIENT

/*    Client recieve the list of files from server and request to send one of the file 

*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



int main( int argc, char *argv[] )
{
	if( argc > 2 || argc <1)
	{
	      printf("There will be must all required arguments");
			}
		  int clientSocket;
		  int run=1;
		  char buffer[1024];
		  char buffer1[1024];
		  memset(buffer,0,sizeof(buffer));

		  memset(buffer1,0,sizeof(buffer));
		  struct sockaddr_in serverAddr;
		  socklen_t addr_size;
		  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
		  serverAddr.sin_family = AF_INET;
		  serverAddr.sin_port = htons(atoi(argv[1]));
		  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");      //running in a lical host
		  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
		  addr_size = sizeof serverAddr;
		  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

		  printf("\nMay be connected!\n");
	
		  char data[1024],out[1024];
			memset(data,'\0',1024);
			memset(out,'\0',1024);
		  int ctr=0;
			receive_list(clientSocket);
			printf("Enter the name of file to Transfer:");
			scanf("%s",data);
	
	
			printf("name for Transfer File to save as:");
			scanf("%s",out);
			write(clientSocket,data,1024);
			download_file(clientSocket,out);
	


  close(clientSocket);
  return 0;
}
void receive_list(int s)
{
	char data[1024];
	while(1)
	{	
		memset(data,'\0',1024);
		read(s,data,1024);
		if(strcmp(data,"finished"))
			printf("%s",data);
		else
			break;
	}	
}
void download_file(int s,char name[])
{
	char data[1024];
	FILE *f = fopen(name,"w");
	if(f==NULL)
	{
		printf("File creation failed\n");
		return;

	}
	int ctr=0;
	while(1)
	{	
		memset(data,'\0',1024);
		ctr = read(s,data,1024);
		if(strcmp(data,"finished")&&ctr>0)
		{
			printf("%s",data);
			fwrite(data,1,ctr,f);
			usleep(5000);
		}
		else
		{
			sleep(1);
			printf("%s",data);
			break;
		}
	}	
}


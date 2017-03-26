 

 /**************************************************         OS LAB ASSIGNMENT# 3            **********************************************/
  /**************************************************            Vivek Kumar                   *******************************************/
  /**************************************************             14CS01006                    *******************************************/

#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>



#define buffer1 1024
int main( void )
{
	char *history[10];
	int i = 0, j=0 , x, y, z;
	while(1)
	{
		char* cwd, * token;
		history[i]= malloc(20);
		char buffer[PATH_MAX];
		char * new_buffer;
		char data[buffer1];
		cwd = getcwd( buffer, PATH_MAX);
		if( cwd != NULL )
		{
				FILE *file;
				int x = strlen("vivek---->>#>>");
				int y = strlen(cwd);
				char a[x+y+1];
				strcpy(a,"vivek---->>");
				strcat(a,cwd);
				strcat(a,"#>>");
				new_buffer = readline(a);
				add_history(new_buffer);
				if(new_buffer[0] == '!')
				{
						z = atoi(new_buffer + 1);
						if(z == -1)
							strcpy(new_buffer, history[i-1]);
						else if(z>0 && z <=i)
							strcpy(new_buffer, history[z-1]);
						else
						{
							printf("please enter correct command\n");
							continue;
						}
			}
			if(strcmp(new_buffer , "history")!=0)
				file = popen(new_buffer , "r");
				if(i<=9 && new_buffer[0] != '!')
				{
					strcpy(history[i],new_buffer);
				}
			else if(i>9 && new_buffer[0] != '!')
			{
				for(j=0;j<9;j++)
					strcpy(history[j],history[j+1]);
				strcpy(history[9],new_buffer);
				i=9;
			}
				else if(i<=9 && new_buffer[0] == '!' && z == -1)
				{
					strcpy(history[i],history[i-1]);
				}
					else if(i<=9 && new_buffer[0] == '!' && z> 0 && z <10)
					{
						strcpy(history[i],history[z-1]);
					}
						else if(i>9 && new_buffer[0] == '!')
						{
							for(j=0;j<9;j++)
								strcpy(history[j],history[j+1]);
							strcpy(history[9],history[z-1]);
							i=9;
						}
						token = strtok(new_buffer, " ");
			if(strcmp(token , "exit")==0)
			{
				pclose(file);
				break;
			}
				else if(strcmp(new_buffer , "history")==0)
				{
					for(j=0;j<=i && j<10 ;j++)
						printf("%d. %s\n",j+1 , history[j]);
				}
					else if(!file)
					{
						printf("command not found it may incorrect command\n");
					}
						else if(strcmp(token , "cd")==0)
						{
							token = strtok(NULL, " ");
							if(token==NULL)
								continue;
							chdir(token);
						}
			else
			{
				
				while(fgets( data , buffer1 , file))
					printf("%s",data);
			}
		}
		else
		{
			printf("There is an error!!\n");
			break;
		}

		i++;	
	}
	return EXIT_SUCCESS;
}

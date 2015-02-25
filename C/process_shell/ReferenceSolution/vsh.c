#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include"builtin.c"							

#define MAXLINE 4096   					//the maximum length of command line
#define MAXARG	 10						//the maximum number of command-line arguments

int main(void)
{
	pid_t	pid;
	int status;
	char 	buf[MAXLINE];					//the input command
	int i=0, j=0, split=0;						//i for string index, j for argument index, split for spliting command-line arguments	
	char *argv[MAXARG];					//argument vectors
	int length=0;								//the length of command line
	int builtin = 0;						//if builtin command finished and contiue shell

	printf("(O-O)");								//print prompt (printf requires %% to print %)

	while(fgets(buf, MAXLINE, stdin) != NULL)
	{		
		i=0, j=0, split=0;						//refresh index for each command line
		memset(argv, 0, sizeof(argv));		//refresh argument vectors
		
		/*fetch the command string without '\n'*/
		if(buf[(length = strlen(buf)) - 1] == '\n')		//replace newline with null, also fetch the length of command line here
		   buf[length - 1] = 0;								
		
		/*split arguments*/
		while( i<length && j<MAXARG )   	//j < MAXARG is for maximum number of arguments
		{							   				
			if(buf[i]==' ')							//when move to the first space, insert a split symbol)
			{
				buf[i]='\0';
				split=0;												
			}
			else
			{
				 if(split==0)						//還未到空白，但flag=0，表示目前來到某參數第一個字元，所以要存該參數的起始位址
					argv[j++]=&buf[i];			//也就是把這一個參數的起始字元addr存到argv[j]中
				 split=1;							//存完該參數的起始位址，為了移動到下個字元(向右移動)，所以flag設為1，讓下一輪不做上兩行
													//或是還未到空白，但flag=1，表示還在某參數的第x字元，所以要繼續往右移動i，flag仍=1
			}
			
			i++;									//move string index forward
		 }
		 
		 
		 /*too much arguments error handling*/
		 if( j>MAXARG && i<length)			
		 {
			puts("There are too many arguments. ");
			printf("(O-O)");
		 	continue;
		 }
		
		
		/*Some builtin command*/
		 if(strcmp(argv[0], "find") == 0)						/**find**/
		 {
		 	find(j,argv);												//invoke funtion
		 	builtin=1;
		 }
		 else if(strcmp(argv[0], "cd") == 0) 					/**change directory**/
		 {		 
			  if(argv[1]==NULL)                                   //directory_name(argv[1])
				puts("Usage: cd [directory name]");
			  else
                if(chdir(argv[1])<0)                               //call chdir changing the directory
                    puts("error occured: chdir");				//if error occur (permition deny or no such file)
				builtin=1;
		}
		 else if(strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "logout") == 0 || strcmp(argv[0], "quit") == 0)		
			break;													/**leave the shell**/
	

		if(builtin==1)
		{
			builtin = 0;
			printf("(O-O)");
			continue;
		}

		/*Executing external program*/
		if((pid = fork()) < 0)
			puts("fork error");
		else if(pid == 0)						/*child*/
		{
				execlp("/bin/sh", "sh", "-c", argv[0], (char *) 0);		//execute commands of sh
				printf("couldn't execute: %s", argv[0]);
				exit(127);														//terminate child process manually when failed
		}	
	
		/* parent */
		if((pid = waitpid(pid, &status, 0)) < 0)
			puts("waitpid error");
		
		printf("(O-O)");	
	}


	exit(0);
}
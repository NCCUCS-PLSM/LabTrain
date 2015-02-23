#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <string.h>
void printHead(); /*print shell head*/
int Search_in_File(char *file, char*str);/* search keyword in given file*/
struct stat s; 
int main(){
	DIR *dirp;
	struct dirent *dp;
	char input[256];
	printHead();
	while(fgets(input,256,stdin)){ /* get user command */
		if(strncmp(input,"find ",5)==0){ /* find func*/
			strtok(input," \n");
			char *keyword= strtok(NULL," \n");
			char *target = strtok(NULL," \n");
			if(stat(target,&s) == 0){
				if(S_ISDIR(s.st_mode)) /*it's a directory*/
				{
					if ((dirp = opendir(target)) == NULL) { /*open directory*/
						printf("couldn't open %s\n",target);
						return 0;
					}
					do{  /*search keyword in each file*/
						if ((dp = readdir(dirp)) != NULL) {
							Search_in_File(dp->d_name,keyword);
						}
					}while(dp != NULL);			 
				}
				else if(S_ISREG(s.st_mode)) /*it's a file */
				{
					Search_in_File(target,keyword);
				}
			}
			else/* no such file or directory*/
			{
				printf("no such file or directory\n");
			}
			printHead();
		}
		else if(strncmp(input,"exit\n",5)==0){
			return 0;
		}
		else{  /*implement other func*/
			pid_t pid = fork();
			if(pid == -1){ /*error*/
				printf("fork failed");
			}			
			else if(pid == 0){ /* child process*/
				char str[128];
				strcpy(str,input);
				char *command = strtok(input," \n");
				int i = 1;
				char *args[10];
				char *temp;
				args[0] = command;
				do{
					temp = strtok(NULL," \n");
					args[i]=temp;
					i++;		
				}while(temp !=NULL);
				args[i]=NULL;
				printf("arg1:%s,arg2:%s",args[0],args[1]);
				execvp(command,args);
				printf("command not found\n");/*should not run this*/
			}
			else{ /*parent process*/
				int returnStatus;    
				waitpid(pid, &returnStatus, 0);  /*wait child process finish*/
				if(returnStatus == 0)
					printHead();	
				else
					printf("The child process terminated with an error");
			}
		}
	}
	return 0;
}
void printHead(){
	printf("(O-O) ");
}
int Search_in_File(char *file, char *str) {
	FILE *fp = fopen(file,"r"); 
	int line_num = 1;
	char temp[512];
	while(fgets(temp,512,fp)!=NULL) {  
		/* get every line and compare */
		char *pfound = strstr(temp, str); 
		if(pfound != NULL) {  
			int dposfound = (int)(pfound - temp);
			int length = strlen(str);
			printf("    In %s Line %d : Char %d~%d\n",file,line_num,dposfound+1,dposfound+length+1);	
		}
		line_num++;
	}
	fclose(fp);
	return(0);
}

/** 
 * Check by Veck on Feb/23, 2015: OK! (and excellent)
 */
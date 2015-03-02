#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

void findFunction(char keyword[], char target[]);
void otherFunction(char cmd[16][16]);

int main(){
	char cmdLine[256],cmd[16][16];
	char *tmp; /*For strtok : no [xx]*/
	int lengh_cmd;
	printf("(O_O) ");
	while(fgets(cmdLine,256,stdin)!=NULL){
		tmp = strtok(cmdLine," \n");
		lengh_cmd = 0;
		while(tmp != NULL){
			lengh_cmd++;
			strcpy(cmd[lengh_cmd-1],tmp); /*It's allowed to strcpy( var,ptr)*/
			tmp = strtok(NULL," \n");
		}
		/*for(i=0;i<lengh_cmd;i++){
			printf("The cmd [ %d ] is %s \n",i,cmd[i]);
		}*/
		if(strcmp("find",cmd[0])==0){
			if( lengh_cmd == 3 ){
				findFunction(cmd[1],cmd[2]);
			} 
			else{
				printf("wrong argument numbers!!\n");
			}
		}
		else if(strcmp("exit",cmd[0])==0){
			break;
		}
		else{
			otherFunction(cmd);
		}
		printf("(O_O) ");
	}
	return 0;
}

void findFunction(char keyword[], char target[]){
	DIR *pwd;
	struct dirent* drt;
	char theLine[100];
	FILE *f;
	char* locate;
	int lineCount;

	pwd = opendir(target);	
	if(pwd!=NULL){
		while((drt = readdir(pwd))!=NULL){
			lineCount=1;
			f = fopen(drt->d_name,"r");
			while(fgets(theLine,100,f)!=NULL){
				locate =  strstr(theLine,keyword);
				if(locate!=NULL){
					printf("In %s Line %d : Char %ld ~ %ld \n",drt->d_name,lineCount,locate-theLine,locate-theLine+strlen(keyword)-1);
				}
				lineCount++;

			}
			fclose(f);
		}
	}
	else{
		printf("Error: Invalid directories !\n");
	}
	closedir(pwd);
}

void otherFunction(char cmd[16][16]){

	pid_t proc = fork();

	if(proc<0){
		printf("Error: Unable to fork ! \n");
	}
	else if(proc == 0){
		if(execlp(cmd[0],cmd,NULL)==-1){
			printf("Error: Invalid Command!! \n");
			exit(EXIT_SUCCESS);
		}
	}
	else{
		int status = -1;
     		wait(&status);
	}
}

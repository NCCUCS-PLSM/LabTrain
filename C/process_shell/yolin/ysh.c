#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#define BUFFER_SIZE 1<<16
#define ARR_SIZE 1<<16

void parse_args(char *buffer, char** args, size_t args_size, size_t *nargs){
    char *buf_args[args_size];
    char **cp;
    char *wbuf;
    size_t i, j;
    
    wbuf=buffer;
    buf_args[0]=buffer; 
    args[0] =buffer;
    
    for(cp=buf_args; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){
        if ((*cp != '\0') && (++cp >= &buf_args[args_size]))
            break;
    }
    
    for (j=i=0; buf_args[i]!=NULL; i++){
        if(strlen(buf_args[i])>0)
            args[j++]=buf_args[i];
    }
    
    *nargs=j;
    args[j]=NULL;
}

void find_inst(char string[], char file[]){
	
	char content[1024] = {'\0'};
	char *found;
	int num = 1;
	int length = strlen(string);
	
	FILE *fp = fopen(file,"r");
	
	while(fgets(content,1024,fp)!=NULL) {  
		found = strstr(content, string); 
		
		if(found != NULL){  
			int pos = (int)(found - content);
			printf("In %s Line %d : Char %d~%d\n", file, num, pos+1, pos+length);	
		}
		num++;
	}
	
}


int main(int argc, char *argv[], char *envp[]){
    char buffer[BUFFER_SIZE];
    char *args[ARR_SIZE];

    int *ret_status;
    size_t nargs;
    pid_t pid;
    
    while(1){
        printf("(O-O) ");
        fgets(buffer, BUFFER_SIZE, stdin);
        parse_args(buffer, args, ARR_SIZE, &nargs); 

        if (nargs==0) continue;
        if (!strcmp(args[0], "exit" )) exit(0);
		else if (!strcmp(args[0], "find" )){
			find_inst(args[1],args[2]);
		}
		else{
        pid = fork();
			if (pid){
				//printf("Waiting for child (%d)\n", pid);
				pid = wait(ret_status);
				//printf("Child (%d) finished\n", pid);
			}else{
				if( execvp(args[0], args)) {
					puts(strerror(errno));
					exit(127);
				}
			}
		}
    }    
    return 0;
}

/** 
 * Check by Veck on Feb/23, 2015: OK!
 * 1. 基本功能有了，不過有個小 Bug，當我輸入『find world .』後，並沒有檢查目錄下所有檔案中有 world 的檔案
 *	  應該使用 DIR 資料型態的元素來實作目錄的檢查和操作，然後再對檔案做內容的檢查
 * 2. 實作 parse_args 是個不錯的想法！
 */
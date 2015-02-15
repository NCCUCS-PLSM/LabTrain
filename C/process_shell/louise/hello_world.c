#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 

int main () 
{ 
	pid_t pid;
	char *show;

	/*fork a child process*/
	pid = fork();
	show = "hello world...";
	//printf("hello world...");
	if(pid<0){  /*error occurred*/
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){ /*child process*/
		execlp("echo","echo", show, NULL);
	}
	else {  /*parent process*/
		wait(NULL);
		//printf("no ok...\n");
	}
	return 0; 
}


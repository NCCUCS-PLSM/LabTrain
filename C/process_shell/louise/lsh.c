

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators


/*******************************************************************/

int main (int argc, char ** argv)
{
char linebuf[MAX_BUFFER];                  // line buffer
char cmndbuf[MAX_BUFFER];                  // command buffer
char * args[MAX_ARGS];                     // pointers to arg strings
char ** arg;                               // working pointer thru args
char * prompt = "(O-O) " ;                    // shell prompt
char *err;
// keep reading input until "exit" command or eof of redirected input 

while (!feof(stdin)) { 

// get command line from input


    fputs (prompt, stdout);                // write prompt
    fflush(stdout);
    if (fgets(linebuf, MAX_BUFFER, stdin )) { // read a line

// tokenize the input into args array

        arg = args;
        *arg++ = strtok(linebuf,SEPARATORS);   // tokenize input
        while ((*arg++ = strtok(NULL,SEPARATORS)));
                                           // last entry will be NULL 

        if (args[0]) {                     // if there's anything there

            cmndbuf[0] = 0;                // set zero-length command string

// check for internal/external command 

            if (!strcmp(args[0],"clr")) {  // "clr" command
                strcpy(cmndbuf, "clear");
            
            } else if (!strcmp(args[0],"find")) {  // "find" command
		if(args[1]==NULL || args[2]==NULL) {
			//err = "Usage: find keyword target\n";
			//execlp("echo", "echo", err, NULL);
			printf("Usage: find keyword target\n");
		} else	
		{
		strcpy(cmndbuf, "grep -R --color "); 
		if (!args[1])
		    args[1] = " ";
		strcat(cmndbuf, args[1]);
		if (!args[2])
                    args[2] = ". ";         // if no arg set current directory
                strcat(cmndbuf, args[2]);
		} 
            } else if (strcmp(args[0], "exit") == 0) {  // "exit" command
                break;
            } else {                         // pass command on to OS shell
                int i = 1;
                strcpy(cmndbuf, args[0]);
                while (args[i]) {
                    strcat(cmndbuf, " ");
                    strcat(cmndbuf, args[i++]);
                }
            }

// pass any command onto OS

            if (cmndbuf[0])
                system(cmndbuf);
        }
    }
}
return 0; 
}

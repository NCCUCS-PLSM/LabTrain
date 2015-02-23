

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
        		} else {
        		  strcpy(cmndbuf, "grep -R --color "); 
        		  if (!args[1])
        		    args[1] = " ";
        		  strcat(cmndbuf, args[1]);

                  /*
                   * 少家這行的話：
                   * (O-O) find hello .
                   * grep -R --color hello.
                   * 導致：grep: warning: recursive search of stdin
                   */
                  strcat(cmndbuf, " ");

        		  if (!args[2])
                    args[2] = ". ";   // if no arg set current directory
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

/**
 * Check by Veck on Feb/23, 2015.
 * 1. 有多做 clr 很好!
      不過作法跟要求的不太一樣，『不能使用 system() 去執行』的意思是，妳必須自己實作 find 的功能
 *    例如當使用者輸入 find hello hello.txt 後，妳的要去檢查目前這個目錄下有沒有 hello.txt 
 *    沒有的話印出『hello.txt: No such file or directory』的訊息；有的話才去看內容
 * 2. 妳有練習到 fork, exec 很棒!
 *    但是『你個程式要能夠執行其他原本 shell 可以執行的命令或功能，請另外寫一個 hello_world.c』不是這個意思
 *    而是妳的 lsh 要能夠執行其他 shell 的功能(例如妳編譯出來的 hello)
 *    執行方式是在 lsh 中去呼叫 fork 來產生子行程，再由子行程去呼叫 exec 來執行 hello 這支程式
 */
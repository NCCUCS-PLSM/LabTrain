#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 4096

/*find*/
void err_find()
{
        puts("find [-cr] keyword target");
		puts("\t -c : upper/lower case sensitive");
		puts("\t -r : used when the target is a directory");
		puts("\t\t keyword : the word you want to find");
		puts("\t\t target : the target file or directory");
}

void findFile(char *keyword, char *target, int cs)			/*find file*/
{
    FILE *input=NULL;							
    char line[MAXLINE];							
    int lno=0, num=0;												//line number and the start position
		
       if((input = fopen(target , "r") ) != NULL)   
           while(fgets(line,MAXLINE,input) != NULL)
            {
           	   lno++;														//record the line number
               if((num=stridx(line, keyword,cs) )>=0)
               {
	       	       num++;												//compute the start index
                   printf("In %s Line : %d Char %d~%d\n", target, lno, num, (int)(num+strlen(keyword)-1) );
					//最後一參數是size_t，gcc會有warning，所以轉int
               }
            }		
	   else
			fprintf(stderr, "Cannot open the file: %s\n ", strerror(errno));			//output error message to standard error	   
}

void findDir(char *keyword, char *target,int cs)			/*find directory*/
{
    DIR *dir, *isdir;
    struct dirent *ptr;
    char path[MAXLINE], *cmp=NULL;
	
	dir = opendir(target);											//open the directory (needless to chech if target is directory indeed)

	while((ptr=readdir(dir))!=NULL)								//read directory one by one
	{
			memset(path, '\0', sizeof(path) );
			
			if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)		//do not traverse these two directory (otherwise, infinite recursion)
					continue;
					
			sprintf(path,"%s/%s", target, ptr->d_name);									//synthesis path
			
			if((isdir=opendir(path) ) !=NULL)											//recusive traverse subdirectory
					findDir(keyword,path,cs);
					
			findFile(keyword,path,cs);														//not directory (so it's file)
	}
	
   closedir(dir);
}

int stridx(char line[], char keyword[], int cs)						/*find the start and terminal index of keyword in a line*/
{
    int i=0, j=0, k=0;
	
	if(cs==0)  					//case sensitive
    {
      for(i = 0; line[i] != '\0'; i++)
      {
         j=i;
		 k=0;		 
		 while(keyword[k] != '\0' && line[j] == keyword[k])
		 {
			j++;
			k++;
		 }
		 
         if(k > 0 && keyword[k] == '\0')
            return i;        
      }
	  return -1;
    }
    else							//case insensitive
    {
        for(i = 0; line[i] != '\0'; i++)
        {
         j=i;
		 k=0; 		 
		 while(keyword[k] != '\0'  
		 && ((line[j] == keyword[k]) || ((line[j]-keyword[k])==32) || ((keyword[k]-line[j])==32) ))
		 {
			j++;
			k++;
		 }
		 
         if(k > 0 && keyword[k] == '\0')
            return i;           
		}		
        return -1;
    }    
}

int find(int argc, char* argv[])
{
   DIR *dp;
    struct dirent *dirp;
    char *ptr=NULL;
    int cs = 1;											//case sensitive = 0, insensitive = 1

    if(argc == 3)										//at least 3 arguments : find  keyword  target
	{
	    cs=1;
        findFile(argv[1],argv[2],cs);
	}
	else if(argc == 4)									//at most 4 arguments : find [-c | -r | (-cr|-rc)]  keyword  target
	{
		if(argv[1][0] != '-')							//option without dash
           	err_find();				
		else if((strcmp("-rc",argv[1]) && strcmp("-cr",argv[1]) ) == 0 )				
		{
			cs = 0;
			ptr=&(argv[3][2]);
			findDir(argv[2],ptr,cs);
		}            	
        else if(argv[1][1] == 'r')
        {
            ptr=&(argv[3][2]);
            findDir(argv[2],ptr,cs);
        }
        else if(argv[1][1] == 'c')
        {
            cs = 0;
            findFile(argv[2],argv[3],cs);
        }            	
        else
            err_find();
	}
	else
		err_find();

	return 0;

}

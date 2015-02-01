#include <stdio.h>
#include <string.h>
#define LINE_SIZE 20
#define COMMAND_SIZE 6
void warning1(){
 	 printf("unrecognized function");
}
int main(){
 	 FILE *file;
	 file = fopen("phoneBook.txt","rb+");
 	 char str[8];
	 char command[LINE_SIZE];
	 while(fgets(str, sizeof str,file) !=NULL)
	  	 printf("%s",str);
	 printf("There are some functions you can use.\n1. Create Name. Number.\n2. Update NO. Name. Number.\n3. Delete NO.\n4. Search [type] [content]\n");
	 while(fgets(command,LINE_SIZE,stdin)){
	 	 if(strncmp(command,"Create",COMMAND_SIZE)==0){
		 	 fseek (file, 0, SEEK_END);

		 	 fprintf(file,"%10s%15s%10s",);	 
		 }
		 else if(strncmp(command,"Update",COMMAND_SIZE)==0){
		 
		 }
		 else if(strncmp(command,"Delete",COMMAND_SIZE)==0){
		 
		 }
		 else if(strncmp(command,"Search",COMMAND_SIZE)==0){
		 
		 }
		 else{
			 warning1();
		 }
	 }
 	 fclose(file);
	 return 0;
}

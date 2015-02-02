#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 64
#define COMMAND_SIZE 6
void printInfo();
void warning1();
void Delete_Line(FILE *file, int line);
void Update_Line(FILE *file, int line, char *name, char *number);
int Search_Line(FILE *file, char *line);
int Search_in_File(FILE *file, char *str ,char *type);
void List(FILE *file);
int Count(FILE *file);
int main(){
	FILE *file;
	file = fopen("phoneBook.txt","rb+");
	char command[LINE_SIZE];
	system("clear");
	printInfo();

	while(fgets(command,LINE_SIZE,stdin)){
		system("clear");
		char *com = strtok(command," \n");
		if(strcmp(com,"Create")==0){
			char *name = strtok(NULL," \n");
			char *number = strtok(NULL," \n");
			int new = Count(file);
			fseek (file, 0, SEEK_END);
			fprintf(file,"%-10d%-15s%-10s\n",new+1,name,number);
		 	List(file);
		}
		else if(strcmp(com,"Update")==0){
			char *n=strtok(NULL," \n");
			char *name=strtok(NULL," \n");
			char *number=strtok(NULL," \n");
			int l = Search_Line(file,n);
			Update_Line(file,l,name,number);
		}
		else if(strcmp(com,"Delete")==0){
			char *line=strtok(NULL," \n");
			int l = Search_Line(file,line);
			Delete_Line(file,l);
		}
		else if(strcmp(com,"Search")==0){
			char *content=strtok(NULL," \n");
			char *type=strtok(NULL," \n");
			Search_in_File(file,content,type);
		}
		else if(strcmp(com,"exit") == 0){
			return 0;		 
		}
		else if(strcmp(com,"List") == 0){
			List(file);
		}
		else{
			warning1();
		}
		printInfo();
	}
	fclose(file);
	return 0;
}
void printInfo(){
	printf("\nThere are some functions you can use.\n1. Create [Name] [Number]\n2. Update [NO.] [Name] [Number]\n3. Delete [NO.]\n4. Search [content] [type] (type can be \"NO.\", \"Name\", \"PhoneNumber\" or blank to search whole file.)\n5. List\n6. exit\n:");
}
void warning1(){
	printf("unrecognized function");
}
void Delete_Line(FILE *file ,int line){
	if(line != 0){	
		char filename[20] = "phoneBook.txt";
		FILE *tmp = fopen("replica.txt", "w");
		char ch[512];
		int temp = 1;
		rewind(file);
		while(fgets(ch, 512, file) != NULL){
			if(temp <line){
				fprintf(tmp,"%s",ch);
			}
			else if(temp >line){
				char *n = strtok(ch," \n");
				char *name = strtok(NULL," \n");
				char *number = strtok(NULL," \n");
				int new = atoi(n);
				fprintf(tmp,"%-10d%-15s%-10s\n",new-1,name,number);
			}
			temp++;
		}

		fclose(file);
		fclose(tmp);
		remove(filename);
		rename("replica.txt", filename);
		printf("\nThe contents of file after being modified are as follows:\n");
		file = fopen(filename, "rb+");
		List(file);
	}
}
void Update_Line(FILE *file, int line, char *name, char *number){
	if(line != 0){
		char filename[20] = "phoneBook.txt";
		FILE *tmp = fopen("replica.txt", "w");
		char ch[512];
		int temp = 1;
		rewind(file);
		while(fgets(ch, 512, file) != NULL){
			if(temp <line){
				fprintf(tmp,"%s",ch);
			}
			else if(temp == line){
			 	 fprintf(tmp,"%-10d%-15s%-10s\n",line-1,name,number);
			}
			else if(temp >line){
				char *n = strtok(ch," \n");
				char *name2 = strtok(NULL," \n");
				char *number2 = strtok(NULL," \n");
				int new = atoi(n);
				fprintf(tmp,"%-10d%-15s%-10s\n",new,name2,number2);
			}
			temp++;
		}

		fclose(file);
		fclose(tmp);
		remove(filename);
		rename("replica.txt", filename);
		printf("\nThe contents of file after being modified are as follows:\n");
		file = fopen(filename, "rb+");
		List(file);
	}
}
int Search_Line(FILE *file,char *line){
	int line_num = 1;
	char temp[512];
	rewind(file);
	while(fgets(temp, 512, file) != NULL) {
		char *n = strtok(temp," \n");
		if(strcmp(n,line)==0) {
			return line_num;
		}
		line_num ++;
	}
	printf("\nSorry, couldn't find a match.\n");
	return 0;
}
int Search_in_File(FILE *file, char *str,char *type) {
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	fseek(file,0,SEEK_SET);
	while(fgets(temp, 512, file) != NULL) {
		if(line_num==1){
			line_num++;
			continue;
		}
		char line[512];
		strcpy(line,temp);
		char *n = strtok(line," \n");
		char *name = strtok(NULL," \n");
		char *number = strtok(NULL," \n");
		if(type == NULL){
			if((strstr(temp, str)) != NULL) {
				printf("%s", temp);
				find_result++;
			}
		}
		else if(strcmp(type,"NO.")==0){
			if((strstr(n, str)) != NULL) {
				printf("%s", temp);
				find_result++;
			}
		}
		else if(strcmp(type,"Name")==0){
			if((strstr(name, str)) != NULL) {
				printf("%s", temp);
				find_result++;
			}
		}
		else if(strcmp(type,"PhoneNumber")==0){
			if((strstr(number, str)) != NULL) {
				printf("%s", temp);
				find_result++;
			}
		}
		line_num++;
	}
	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	return(0);
}
void List(FILE *file){
	char str[512];
	rewind(file);
	while(fgets(str, sizeof str,file) !=NULL){
		printf("%s",str);
	}
}
int Count(FILE *file){
	char str[512];
	int line_num = 0;
	rewind(file);
	while(fgets(str, sizeof str,file) !=NULL){
		line_num++;
	}
	return line_num;
}

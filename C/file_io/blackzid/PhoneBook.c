#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 64
#define CREATE 1
#define UPDATE 2
#define DELETE 3
#define SEARCH 4
#define SHOW 5
#define EXIT 6
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
	int command;
	system("clear");
	printInfo();

	while(scanf("%d",&command)!=EOF){
		system("clear");
		if(command== CREATE ){
			char name[20];
			char number[20];
			printf("Please enter name:");
			scanf("%s",name);
			printf("\nPlease enter number:");
			scanf("%s",number);
			printf("\n");

			int new = Count(file);
			fseek (file, 0, SEEK_END);
			fprintf(file,"%-10d%-15s%-10s\n",new+1,name,number);
			List(file);
		}
		else if(command== UPDATE){
			char number[20];
			char name[20];
			char L[5];
			printf("Enter the NO. you want to update:");
			scanf("%s",L);
			int l = Search_Line(file,L);
			if(l!=0){
				printf("\nPlease enter name:");
				scanf("%s",name);
				printf("\nPlease enter number:");
				scanf("%s",number);
				printf("\n");

				Update_Line(file,l,name,number);
			}
		}
		else if(command== DELETE){
			char line[5];
			printf("Enter the NO. you want to delete:");
			scanf("%s",line);
			printf("\n");

			int l = Search_Line(file,line);
			Delete_Line(file,l);
		}
		else if(command== SEARCH){
			char content[20];
			char type[20];
			printf("Please enter the keyword:");
			scanf("%s",content);
			printf("\nPlease enter the search type(NO./Nmae/Number/all).");
			scanf("%s",type);
			Search_in_File(file,content,type);
		}
		else if(command== EXIT){
			return 0;		 
		}
		else if(command== SHOW){
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
	printf("\nThere are some functions you can use.\n1. Create\n2. Update\n3. Delete\n4. Search\n5. List\n6. exit\n:");
}
void warning1(){
	printf("Usage : Please enter Number 1 to 6.");
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
		if(strcmp(type,"all")==0){
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

/**
 * Check by Veck on Feb/04, 2015: OK!
 * Advise:
 * 1. Comment!
 * 2. Maybe type number is better than type command, or you should hint some usage inforamtions.
 */

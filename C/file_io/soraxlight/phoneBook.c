#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct phone{
	char name[15];
	char number[15];
	int age;
};
typedef struct phone Phone;
Phone create();
int match(FILE *f);
void delete(FILE *f,int line);

int main(){
	FILE *file;
	int lineTag,i;
	char command[10],move[10];
	Phone input,tmp;
	file = fopen("book.txt","rb+");
	printf("Instruction Available : \n\t'create','browse','search','update','delete','exit'\n");
	while(scanf("%s",command)!=EOF){
	
		if(strcmp(command,"create")==0){
			input  = create();
			fseek(file,0,SEEK_END);
			fprintf(file,"%10s %10s %d \n",input.name,input.number,input.age);	 	
		}
		else if(strcmp(command,"browse")==0){
			rewind(file);
			printf("%10s %10s %3s\n","Name:","Number:","Age:");
			while(fscanf(file,"%s %s %d",tmp.name,tmp.number,&tmp.age)!=EOF){
				printf("%10s %10s   %d \n",tmp.name,tmp.number,tmp.age);
			}
			printf("\n");
		}
		else if(strcmp(command,"search")==0){
			lineTag = match(file);
			if(lineTag!= -1){	
				rewind(file);
				for(i=0;i<3*lineTag;i++){
					fscanf(file,"%s",move);
				}
				fscanf(file,"%s %s %d",tmp.name,tmp.number,&tmp.age);
				printf("Match : \n");
				printf("%10s %10s   %d\n\n",tmp.name, tmp.number, tmp.age);
			}
			else{
				printf("Cannot find one !!!!!!!!!!!!\n\n");
			}
		}
		else if(strcmp(command,"update")==0){
			lineTag = match(file);
			if(lineTag!=-1){
				rewind(file);
				for(i=0;i<3*lineTag;i++){
					fscanf(file,"%s",move);
				}
				input = create();
				fprintf(file,"%10s %10s %d \n",input.name,input.number,input.age);
				printf("Done ! \n\n");
			}
			else{
				printf("Cannot find one !!!!!!!!!!!!\n\n");
			}
		}
		else if(strcmp(command,"delete")==0){
			lineTag = match(file);
			if(lineTag!=-1){
				delete(file,lineTag);
				printf("Done ! \n\n");
			}
			else{
				printf("Cannot find one !!!!!!!!!!!!\n\n");
			}
		}

		else if(strcmp(command,"exit")==0){
			break;
		}
		else{
			printf("Wrong Instruction !!\n\n");
		}
		printf("Instruction Available : \n\t'create','browse','search','update','delete','exit'\n");
	}
	fclose(file);
return 0;
}


Phone create(){
	Phone p;
	printf("Please input your names : ");
	scanf("%s",p.name);
	printf("Please input your phone number : ");
	scanf("%s",p.number);
	printf("Please input your age : ");
	scanf("%d",&p.age);
	if(p.age>=200 || p.age < 0 ){
		printf("You must be kidding....\n");
		p = create();
	}
	return p;
}
int match(FILE *f){
	Phone p;
	int isFound = 0,nRound;
	char searchStr[10];
	/*input*/
	printf("Please input keywords : ");
	scanf("%s",searchStr);
	/*start searching*/
	rewind(f);
	nRound = 0;
	while(fscanf(f,"%s %s %d",p.name,p.number,&p.age)!=EOF){
		if(strcmp(searchStr,p.name)==0){
			isFound=1;
			break;
		}
		else if(strcmp(searchStr,p.number)==0){
			isFound=1;
			break;
		}
		nRound++;
	}

	if(isFound==0){		
		nRound = -1;
	}
	return nRound;
}
void delete(FILE *f,int line){
	FILE *replaceFile;
	int i;
	Phone temp;
	replaceFile = fopen("replace.txt","w+");
	if(replaceFile == NULL){
		freopen("replace.txt","w+",replaceFile);
	}
	rewind(f);
	for(i=0;i<line;i++){
		fscanf(f,"%s %s %d",temp.name,temp.number,&temp.age);
		fprintf(replaceFile,"%10s %10s %d\n",temp.name,temp.number,temp.age);
	}
	/*skip a line*/
	fscanf(f,"%s %s %d",temp.name,temp.number,&temp.age);
	while(fscanf(f,"%s %s %d",temp.name,temp.number,&temp.age)!=EOF){
		fprintf(replaceFile,"%10s %10s %d\n",temp.name,temp.number,temp.age);
	}
	fclose(f);
	fclose(replaceFile);
	remove("book.txt");
	rename("replace.txt","book.txt");
	f = fopen("book.txt","rb+");
}

/**
 * Check by Veck on Feb/05, 2015: OK!
 * Advise:
 * 1. Maybe type number is better than type command.
 *

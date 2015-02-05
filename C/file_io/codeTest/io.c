#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE *file;
	file = fopen("book.txt","rb+");
	fprintf(file,"hello world! \n");
	return 0;
}
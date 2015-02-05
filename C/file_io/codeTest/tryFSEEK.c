#include<stdio.h>
int main(){
	FILE *f;
	char str10[10],mv[10];
	int i,tag;
	f = fopen("book.txt","r");
	
	while(scanf("%d",&tag)!=EOF){
		rewind(f);
		for(i=0;i<3*tag;i++){
			fscanf(f,"%s",mv);
		}
		fscanf(f,"%10s",str10);	
		printf("string : %10s\n",str10);
	}

	return 0;
}
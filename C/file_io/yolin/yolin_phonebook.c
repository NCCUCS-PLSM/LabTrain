#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define N 100


struct student{

    char num[12];
    char name[12];
    char tel[12];

};

int scanline(char *filename){ //查看文件有幾行(有幾個連絡人)
    FILE *f = 0;
    char line[N]="";
    int lines = 0;

    f = fopen(filename, "r");

    if(!f) return 0;
    while(!feof(f)) { fgets(line, N, f); lines++;}
    fclose(f);
    return lines;
}

void tel_print_option();
void tel_create(struct student *p);
void tel_display(struct student *p);
void tel_search(struct student *p);
void tel_modify(struct student *p);
void tel_add(struct student *p);
void tel_delete(struct student *p);

void main(){

    char choose='\0',yes_no='\0';
    struct student record[N]={0};

    do{
        tel_print_option();
        printf("請選擇(0-6):");
        choose=getche();

        switch(choose){
            case '1':tel_create(record);break;
            case '2':tel_display(record);break;
            case '3':tel_search(record);break;
            case '4':tel_modify(record);break;
            case '5':tel_add(record);break;
            case '6':tel_delete(record);break;
            case '0':exit(0);
            default :printf("\nwrong option...\n");
        }

        printf("\n繼續選擇嗎(y/n)?\n");
        do{
            yes_no=getch();
        } while(yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n');

    } while(yes_no == 'Y' || yes_no == 'y');

    return 0;
}


void tel_print_option(){ //print出選項

    system("cls");
    printf(" 請輸入選項編號(0-6): \n");
    printf("1--創建通訊錄\n");
    printf("2--顯示通訊錄\n");
    printf("3--搜尋通訊錄\n");
    printf("4--修改通訊錄\n");
    printf("5--新增連絡人\n");
    printf("6--刪除連絡人\n");
    printf("0--退出\n");

}


void tel_create(struct student *p){ //create新電話簿

    struct student *q=p;
    FILE *fp=NULL;

    fp=fopen("phonebook.txt","w");
    if(fp==NULL){
        printf("error");
        return;
    }

        printf("\n學號:");
        gets(p->num);
        printf("姓名:");
        gets(p->name);
        printf("電話:");
        gets(p->tel);
        fprintf(fp,"%12s%12s%12s\n",p->num,p->name,p->tel);
        fclose(fp);

}


void tel_display(struct student *p){  //print出全部電話簿

    FILE *fp=NULL;
    fp=fopen("phonebook.txt","r");
    int lines = 0;
    lines = scanline("phonebook.txt");

    if(fp==NULL){
        printf("error / Empty file");
        return;
    }

    system("cls");
    printf("        學號        姓名        電話\n");

    while(lines>0){
        fscanf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
        printf("%12s%12s%12s\n",p->num,p->name,p->tel);
        p++;
        lines--;
    }
}


void tel_search(struct student *p){     //搜尋電話簿

    struct student *q=p;
    int flag=0;
    char c='\0', nm[12]="", nam[12]="", numb[12]="";

    system("cls");
    tel_display(p);

    int lines = 0;
    lines = scanline("phonebook.txt");




    printf("按照學號查詢(h)或姓名查詢(m)或電話號碼查詢(b):\n");
    c=getche();
    if(c=='h'||c=='H'){
        printf("\n請輸入要查詢記錄的學號:\n");
        gets(nm);

        for(p=q;p-q<lines;p++)
            if(strcmp(nm,p->num)==0){
                printf("        學號        姓名        電話\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("wrong / can't find\n");
    }
    else if(c=='m'||c=='M'){
        printf("\n請輸入要查詢記錄的姓名:\n");
        gets(nam);
        for(p=q;p-q<lines;p++)
            if(strcmp(nam,p->name)==0){
                printf("        學號        姓名        電話\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("wrong / can't find\n");
    }
    else if(c=='b'||c=='B'){
        printf("\n請輸入要查詢記錄的電話號碼:\n");
        gets(numb);
        for(p=q;p-q<lines;p++)
            if(strcmp(numb,p->tel)==0){
                printf("        學號        姓名        電話\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("wrong / can't find\n");
    }
    else printf("wrong option...\n");
}


void tel_modify(struct student *p){     //修改電話簿
    struct student *q=p;
    FILE *fp=NULL;
    char nam[12]="";
    tel_display(p);

    int lines = 0;
    lines = scanline("phonebook.txt");

    printf("請輸入您想要修改記錄的姓名:\n");
    gets(nam);

    for(p=q;p-q<lines;p++)
        if(strcmp(nam,p->name)==0)
            break;
    if(p-q==lines)
        printf("wrong...");
    else{
        printf("請輸入正確的學號:");
        gets(p->num);
        printf("請輸入正確的姓名:");
        gets(p->name);
        printf("請輸入正確的電話:");
        gets(p->tel);
    }

    fp=fopen("phonebook.txt","w");
    if(fp==NULL){
        printf("error");
        exit(0);
    }

    for(p=q;p-q<lines;p++)
        fprintf(fp,"%12s%12s%12s\n",p->num,p->name,p->tel);
        fclose(fp);
}


void tel_add(struct student *p){        //新增連絡人
    FILE *fp=NULL;
    struct student *q=p;
    char c='\n',tempnum[12]="",tempname[12]="",temptel[12]="";

    int lines = 0;
    lines = scanline("phonebook.txt");

    printf("\n");

    tel_display(p);

    do{
        printf("請輸入新紀錄的學號:");
        gets(tempnum);
        printf("請輸入新紀錄的姓名:");
        gets(tempname);
        printf("請輸入新紀錄的電話:");
        gets(temptel);

        for(p=q;p-q<lines;p++)
            if(strcmp(temptel,p->tel)==0){
                printf("學號或電話號碼需要重新輸入嗎(Y/N)?");
                c=getche();
                putchar('\n');
                break;
            }

        if(p-q==lines){
            strcpy(p->num,tempnum);
            strcpy(p->name,tempname);
            strcpy(p->tel,temptel);
            break;
        }
    }while(c=='y'||c=='Y');

    fp=fopen("phonebook.txt","w");
    if(fp==NULL){
        printf("error");
        return;
    }

    for(p=q;p-q<=lines;p++)
        fprintf(fp,"%12s%12s%12s\n",p->num,p->name,p->tel);
    fclose(fp);
}


void tel_delete(struct student *p){  //刪除連絡人
        FILE *fp=NULL;
        struct student *q=p;
        char c[12]="",tempnum[12]="",tempname[12]="",temptel[12]="",choose='\0';
        tel_display(p);

        printf("\n選擇刪除記錄的方式: 學號(h)姓名(m):");
        choose=getche();
        printf("\n");

        int lines = 0;
        lines = scanline("phonebook.txt");


        if(choose=='m'||choose=='M'){
            printf("刪除的記錄:");
            gets(c);
            for(p=q;p-q<lines;p++)
                if(strcmp(c,p->name)==0){
                    for(;p-q<lines-1;p++){
                        strcpy(p->num,(p+1)->num);
                        (p+1)->num[0] = '\0';
                        strcpy(p->name,(p+1)->name);
                        (p+1)->name[0] = '\0';
                        strcpy(p->tel,(p+1)->tel);
                        (p+1)->tel[0] = '\0';
                    }

                }
                else
                    printf("can't find\n");
        }
        else if(choose=='h'||choose=='H'){
            printf("刪除的記錄:");
            gets(c);
            for(p=q;p-q<lines;p++)
                if(strcmp(c,p->num)==0){
                    for(;p-q<lines-1;p++){
                        strcpy(p->num,(p+1)->num);
                        (p+1)->num[0] = '\0';
                        strcpy(p->name,(p+1)->name);
                        (p+1)->name[0] = '\0';
                        strcpy(p->tel,(p+1)->tel);
                        (p+1)->tel[0] = '\0';
                    }
                }
                else
                    printf("can't find\n");
        }
        else printf("wrong\n");

        fp=fopen("phonebook.txt","w");
        if(fp==NULL){
            printf("error");
            return;
        }

        for(p=q;p-q<lines-1;p++)
            fprintf(fp,"%12s%12s%12s\n",p->num,p->name,p->tel);

        fclose(fp);
}



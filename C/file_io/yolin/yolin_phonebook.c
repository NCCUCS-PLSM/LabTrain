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

int scanline(char *filename){ //�d�ݤ�󦳴X��(���X�ӳs���H)
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
        printf("�п��(0-6):");
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

        printf("\n�~���ܶ�(y/n)?\n");
        do{
            yes_no=getch();
        } while(yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n');

    } while(yes_no == 'Y' || yes_no == 'y');

    return 0;
}


void tel_print_option(){ //print�X�ﶵ

    system("cls");
    printf(" �п�J�ﶵ�s��(0-6): \n");
    printf("1--�Ыسq�T��\n");
    printf("2--��ܳq�T��\n");
    printf("3--�j�M�q�T��\n");
    printf("4--�ק�q�T��\n");
    printf("5--�s�W�s���H\n");
    printf("6--�R���s���H\n");
    printf("0--�h�X\n");

}


void tel_create(struct student *p){ //create�s�q��ï

    struct student *q=p;
    FILE *fp=NULL;

    fp=fopen("phonebook.txt","w");
    if(fp==NULL){
        printf("error");
        return;
    }

        printf("\n�Ǹ�:");
        gets(p->num);
        printf("�m�W:");
        gets(p->name);
        printf("�q��:");
        gets(p->tel);
        fprintf(fp,"%12s%12s%12s\n",p->num,p->name,p->tel);
        fclose(fp);

}


void tel_display(struct student *p){  //print�X�����q��ï

    FILE *fp=NULL;
    fp=fopen("phonebook.txt","r");
    int lines = 0;
    lines = scanline("phonebook.txt");

    if(fp==NULL){
        printf("error / Empty file");
        return;
    }

    system("cls");
    printf("        �Ǹ�        �m�W        �q��\n");

    while(lines>0){
        fscanf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
        printf("%12s%12s%12s\n",p->num,p->name,p->tel);
        p++;
        lines--;
    }
}


void tel_search(struct student *p){     //�j�M�q��ï

    struct student *q=p;
    int flag=0;
    char c='\0', nm[12]="", nam[12]="", numb[12]="";

    system("cls");
    tel_display(p);

    int lines = 0;
    lines = scanline("phonebook.txt");




    printf("���ӾǸ��d��(h)�Ωm�W�d��(m)�ιq�ܸ��X�d��(b):\n");
    c=getche();
    if(c=='h'||c=='H'){
        printf("\n�п�J�n�d�߰O�����Ǹ�:\n");
        gets(nm);

        for(p=q;p-q<lines;p++)
            if(strcmp(nm,p->num)==0){
                printf("        �Ǹ�        �m�W        �q��\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("wrong / can't find\n");
    }
    else if(c=='m'||c=='M'){
        printf("\n�п�J�n�d�߰O�����m�W:\n");
        gets(nam);
        for(p=q;p-q<lines;p++)
            if(strcmp(nam,p->name)==0){
                printf("        �Ǹ�        �m�W        �q��\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("wrong / can't find\n");
    }
    else if(c=='b'||c=='B'){
        printf("\n�п�J�n�d�߰O�����q�ܸ��X:\n");
        gets(numb);
        for(p=q;p-q<lines;p++)
            if(strcmp(numb,p->tel)==0){
                printf("        �Ǹ�        �m�W        �q��\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("wrong / can't find\n");
    }
    else printf("wrong option...\n");
}


void tel_modify(struct student *p){     //�ק�q��ï
    struct student *q=p;
    FILE *fp=NULL;
    char nam[12]="";
    tel_display(p);

    int lines = 0;
    lines = scanline("phonebook.txt");

    printf("�п�J�z�Q�n�ק�O�����m�W:\n");
    gets(nam);

    for(p=q;p-q<lines;p++)
        if(strcmp(nam,p->name)==0)
            break;
    if(p-q==lines)
        printf("wrong...");
    else{
        printf("�п�J���T���Ǹ�:");
        gets(p->num);
        printf("�п�J���T���m�W:");
        gets(p->name);
        printf("�п�J���T���q��:");
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


void tel_add(struct student *p){        //�s�W�s���H
    FILE *fp=NULL;
    struct student *q=p;
    char c='\n',tempnum[12]="",tempname[12]="",temptel[12]="";

    int lines = 0;
    lines = scanline("phonebook.txt");

    printf("\n");

    tel_display(p);

    do{
        printf("�п�J�s�������Ǹ�:");
        gets(tempnum);
        printf("�п�J�s�������m�W:");
        gets(tempname);
        printf("�п�J�s�������q��:");
        gets(temptel);

        for(p=q;p-q<lines;p++)
            if(strcmp(temptel,p->tel)==0){
                printf("�Ǹ��ιq�ܸ��X�ݭn���s��J��(Y/N)?");
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


void tel_delete(struct student *p){  //�R���s���H
        FILE *fp=NULL;
        struct student *q=p;
        char c[12]="",tempnum[12]="",tempname[12]="",temptel[12]="",choose='\0';
        tel_display(p);

        printf("\n��ܧR���O�����覡: �Ǹ�(h)�m�W(m):");
        choose=getche();
        printf("\n");

        int lines = 0;
        lines = scanline("phonebook.txt");


        if(choose=='m'||choose=='M'){
            printf("�R�����O��:");
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
            printf("�R�����O��:");
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



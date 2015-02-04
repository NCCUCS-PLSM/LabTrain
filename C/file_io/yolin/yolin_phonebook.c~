#include <stdio.h>
//#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define N 100

struct student{

    char num[12];
    char name[12];
    char tel[12];

};

int scanline(char *filename){ //check out file lines(how many contacts)
    FILE *f = 0;
    char line[N]="";
    int lines = 0;

    f = fopen(filename, "r");

    if(!f) return 0;
    while(!feof(f)){
        fgets(line, N, f);
        lines++;
    }
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

int main(){

    char choose = '\0',yes_no = '\0', clear;
    struct student record[N]={0};
    setbuf(stdin,NULL);

    do{
        tel_print_option();
        printf("Options(0-6):");

        setbuf(stdin,NULL);
        choose = getchar();
        clear = getchar();

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

        printf("\nKeep Going?(y/n)\n");
        do{
            setbuf(stdin,NULL);
            yes_no = getchar();
            clear = getchar();

        } while(yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n');

    } while(yes_no == 'Y' || yes_no == 'y');

    return 0;
}


void tel_print_option(){ //print options

    system("clear");
    printf("Options(0-6): \n");
    printf("1.Create phonebook\n");
    printf("2.Print  phonebook\n");
    printf("3.Search phonebook\n");
    printf("4.Modify phonebook\n");
    printf("5.Add new contacts\n");
    printf("6.Delete contacts\n");
    printf("0.Quit\n");

}


void tel_create(struct student *p){ //create new phonebook

    struct student *q=p;
    FILE *fp=NULL;
    char tempnum[12]="",tempname[12]="",temptel[12]="";
    system("clear");
    setbuf(stdin,NULL);
    fp=fopen("phonebook.txt","w");
    if(fp==NULL){
        printf("error");
        return;
    }

        printf("ID number:");

        fgets(p->num, 12, stdin);//gets(p->num);
        if (p->num[strlen(p->num) - 1] == '\n')
            p->num[strlen(p->num) - 1] = '\0';
        printf("Name:");

        fgets(p->name, 12, stdin);//gets(p->name);
        if (p->name[strlen(p->name) - 1] == '\n')
            p->name[strlen(p->name) - 1] = '\0';
        printf("Tel:");

        fgets(p->tel, 12, stdin);//gets(p->tel);
        if (p->tel[strlen(p->tel) - 1] == '\n')
            p->tel[strlen(p->tel) - 1] = '\0';

        fprintf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
        fclose(fp);

}


void tel_display(struct student *p){  //print all contacts

    FILE *fp=NULL;
    fp=fopen("phonebook.txt","r");
    int lines = 0;
    lines = scanline("phonebook.txt");
    setbuf(stdin,NULL);

    if(fp==NULL){
        printf("Error! / Empty file!");
        return;
    }

    system("clear");
    //printf("%d", lines);
    printf("         ID:       Name:        Tel:\n");

    while(lines>0){
        fscanf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
        printf("%12s%12s%12s\n",p->num,p->name,p->tel);
        p++;
        lines--;
    }
}


void tel_search(struct student *p){     //Search phonebook

    struct student *q=p;
    int flag=0;
    char c='\0', nm[12]="", nam[12]="", numb[12]="", clear;
    setbuf(stdin,NULL);

    system("clear");
    tel_display(p);

    int lines = 0;
    lines = scanline("phonebook.txt");




    printf("Search by ID(h)or Name(m)or Tel(b):\n");
    setbuf(stdin,NULL);
    c=getchar();
    clear = getchar();
    if(c=='h'||c=='H'){
        printf("\nEnter the ID you want to search:\n");
        setbuf(stdin,NULL);
        fgets(nm, 12, stdin);
        if (nm[strlen(nm) - 1] == '\n')
            nm[strlen(nm) - 1] = '\0';//gets(nm);

        for(p=q;p-q<lines;p++)
            if(strcmp(nm,p->num)==0){
                printf("         ID:       Name:        Tel:\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("Wrong! / Can't find!\n");
    }
    else if(c=='m'||c=='M'){
        printf("\nEnter the Name you want to search:\n");
        setbuf(stdin,NULL);
        fgets(nam, 12, stdin);
        if (nam[strlen(nam) - 1] == '\n')
            nam[strlen(nam) - 1] = '\0';//gets(nam);

        for(p=q;p-q<lines;p++)
            if(strcmp(nam,p->name)==0){
                printf("         ID:       Name:        Tel:\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("Wrong! / Can't find!\n");
    }
    else if(c=='b'||c=='B'){
        printf("\nEnter the Tel you want to search:\n");
        setbuf(stdin,NULL);
        fgets(numb, 12, stdin);
        if (numb[strlen(numb) - 1] == '\n')
            numb[strlen(numb) - 1] = '\0';//gets(numb);

        for(p=q;p-q<lines;p++)
            if(strcmp(numb,p->tel)==0){
                printf("         ID:       Name:        Tel:\n");
                printf("%12s%12s%12s\n",p->num,p->name,p->tel);
                flag=1;
            }
        if(flag==0) printf("Wrong! / Can't find!\n");
    }
    else printf("Wrong option...\n");
}


void tel_modify(struct student *p){     //Modify phonebook
    struct student *q=p;
    FILE *fp=NULL;
    char nam[12]="";
    int check = 0;
    int count = 0;
    setbuf(stdin,NULL);
    tel_display(p);

    int lines = 0;
    lines = scanline("phonebook.txt");

    printf("Enter the Name you want to modify:\n");
    setbuf(stdin,NULL);
    fgets(nam, 12, stdin);
    if (nam[strlen(nam) - 1] == '\n')
        nam[strlen(nam) - 1] = '\0';//gets(nam);

    for(p=q;p-q<lines;p++){
        if(p-q==lines)
            printf("Wrong!");
        else if(strcmp(nam,p->name)==0){
            check = 1;
            printf("Enter the correct ID:");
            fgets(p->num, 12, stdin);
            if (p->num[strlen(p->num) - 1] == '\n')
                p->num[strlen(p->num) - 1] = '\0';//gets(p->num);

            printf("Enter the correct Name:");
            fgets(p->name, 12, stdin);
            if (p->name[strlen(p->name) - 1] == '\n')
                p->name[strlen(p->name) - 1] = '\0';//gets(p->name);

            printf("Enter the correct Tel:");
            fgets(p->tel, 12, stdin);
            if (p->tel[strlen(p->tel) - 1] == '\n')
                p->tel[strlen(p->tel) - 1] = '\0';//gets(p->tel);
        }
    }

    if(check == 0){
        printf("Wrong! / Can't find!\n");
    }

    fp=fopen("phonebook.txt","w");
    if(fp==NULL){
        printf("Error!");
        return;
    }

    for(p=q;p-q<lines;p++){
        fprintf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
        count ++;
        if(count != lines)
            fprintf(fp, "\n");
    }
    fclose(fp);

}


void tel_add(struct student *p){        //Add new contacts
    FILE *fp=NULL;
    struct student *q=p;
    char c='\n',tempnum[12]="",tempname[12]="",temptel[12]="", clear;
    int count = 0;
    int add = 0;
    setbuf(stdin,NULL);

    int lines = 0;
    lines = scanline("phonebook.txt");

    //printf("\n");

    tel_display(p);

    do{
        printf("Enter the new ID:");
        setbuf(stdin,NULL);
        fgets(tempnum, 12, stdin);
        if (tempnum[strlen(tempnum) - 1] == '\n')
            tempnum[strlen(tempnum) - 1] = '\0';//gets(tempnum);

        printf("Enter the new Name:");

        fgets(tempname, 12, stdin);
        if (tempname[strlen(tempname) - 1] == '\n')
            tempname[strlen(tempname) - 1] = '\0';//gets(tempname);

        printf("Enter the new Tel:");

        fgets(temptel, 12, stdin);
        if (temptel[strlen(temptel) - 1] == '\n')
            temptel[strlen(temptel) - 1] = '\0';//gets(temptel);

        for(p=q;p-q<=lines;p++){
            if(strcmp(temptel,p->tel)==0 || strcmp(tempname,p->name)==0 || strcmp(tempnum,p->num)==0){
                printf("The ID or Name or Tel you entered is repeated.\nDo you want to enter it again?(y/n)?");
                setbuf(stdin,NULL);
                c=getchar();
                clear = getchar();
                putchar('\n');
                break;
            }
            if(p-q==lines){
                strcpy(p->num,tempnum);
                strcpy(p->name,tempname);
                strcpy(p->tel,temptel);
                add = 1;
                c='\n';
                printf("Add success!");
                break;
            }
        }
    }while(c=='y'||c=='Y');


    if(add == 1){
        fp=fopen("phonebook.txt","w");
        if(fp==NULL){
            printf("Error!");
            return;
        }

        for(p=q;p-q<=lines;p++){
            fprintf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
            count ++;
            if(count != lines+1)
                fprintf(fp, "\n");
        }
    }
    fclose(fp);

}


void tel_delete(struct student *p){  //Delete contacts
        FILE *fp=NULL;
        struct student *q=p;
        char c[12]="",tempnum[12]="",tempname[12]="",temptel[12]="",choose='\0', clear;
        int count = 0;
        setbuf(stdin,NULL);

        tel_display(p);

        printf("\nChoose the way you delete the contacts: ID(h) or Name(m):");
        setbuf(stdin,NULL);
        choose=getchar();
        clear = getchar();
        printf("\n");

        int lines = 0;
        lines = scanline("phonebook.txt");


        if(choose=='m'||choose=='M'){
            printf("The Name you want to delete:");
            setbuf(stdin,NULL);
            scanf("%s", &c);//gets(c);
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


                    fp=fopen("phonebook.txt","w");

                    if(fp==NULL){
                        printf("Error!");
                        return;
                    }

                    for(p=q;p-q<lines-1;p++){
                        fprintf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
                        count ++;
                        if(count != lines-1)
                            fprintf(fp, "\n");
                    }
                    fclose(fp);

                    printf("Delete success!");

                }
                else
                    printf("Can't find\n");
        }
        else if(choose=='h'||choose=='H'){
            printf("The ID you want to delete:");
            setbuf(stdin,NULL);
            scanf("%s", &c);//gets(c);
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


                    fp=fopen("phonebook.txt","w");

                    if(fp==NULL){
                        printf("Error!");
                        return;
                    }

                    for(p=q;p-q<lines-1;p++){
                        fprintf(fp,"%12s%12s%12s",p->num,p->name,p->tel);
                        count ++;
                        if(count != lines-1)
                            fprintf(fp, "\n");
                    }
                    fclose(fp);

                    printf("Delete success!");
                }
                else
                    printf("Can't find!\n");
        }
        else printf("Wrong!\n");
}



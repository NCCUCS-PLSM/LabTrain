#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 4096

struct entry
{
   char id[10];
   char name[20];
   char phone[50];
};
typedef struct entry* node;

node cache[1000];
FILE *fptr = NULL;   
int count = 0;

/****************************** Functions used in options ****************************/
void put_to_cache(char* id, char* name, char* phone)
{
   int index = 0;
   sscanf(id, "%d", &index);    // use id as index to avoid duplicate
   node row = malloc(sizeof(struct entry));
   strcpy(row->id, id);
   strcpy(row->name, name);
   strcpy(row->phone, phone);   
   if(cache[--index]->id == NULL)
    {
      count++;
      cache[index] = row;
      printf("[Info] Entry loaded: id: %s name: %s, phone: %s\n", 
        cache[index]->id, cache[index]->name, cache[index]->phone);
    }
}

void write_to_file(int count)
{
  int i = 0;
  while(i <  count)
  {
    if(cache[i] != NULL)    
      if(fprintf(fptr, "<%s,%s,%s>\n", cache[i]->id, cache[i]->name, cache[i]->phone))
        printf("[Info] Entry wrote: <%s,%s,%s>\n", cache[i]->id, cache[i]->name, cache[i]->phone);
    i++;
  }
}

node search_in_cache(char option[], char paras[])
{  
  int i = 0;
  int find = 0;
  node tmp;

  if(strcmp(option, "name") == 0)
      while(i < count)
        if(strcmp(cache[i]->name, paras) == 0) //same
        {
          find = 1;
          break;
        }
        else //different
          i++;
  else if(strcmp(option, "phone") == 0)
      while(i < count)
        if(strcmp(cache[i]->phone, paras) == 0) //same
        {
          find = 1;
          break;
        }
        else //different
          i++;
  else    
    return NULL;
 
  if(find == 1)
  {
    /* We only need to return the address instead of copy memory */
    tmp = cache[i];
    return tmp;
  }
  else
    return NULL;
}

void show_entries()
{
  int i = 0;
  while(i < count)
  {
    if(cache[i] != NULL)
      printf("id:%s, name: %s, phone: %s\n", cache[i]->id, cache[i]->name, cache[i]->phone);
    i++;
  }
}
/****************************** Major Options ****************************/
void query()
{
  int choice = 0;
  int id = 0;
  char paras[MAXLEN];
  char choice_name[50];
  node tmp;

  while(choice != 4)
  {
    puts("Choose the query method:1)id, 2)name, 3)phone, 4)show entries, 5)return");
    scanf("%d", &choice);

    switch(choice)
    {
      case 1:
        printf("id:");
        scanf("%d", &id);
        if(cache[id-1]!=NULL)
          printf("id:%s, name: %s, phone: %s\n", cache[id-1]->id, cache[id-1]->name, cache[id-1]->phone);
        else
          printf("Cannot find %d.\n", id);
        break;
      case 2:
        printf("name:");
        scanf("%s", paras);
        strcpy(choice_name,"name");
        break;
      case 3:
        printf("phone:");
        scanf("%s", paras);    
        strcpy(choice_name, "phone");  
        break;
      case 4:
        show_entries();
        break;
      case 5:
        return ;
      default:
        puts("Invalid choice.");
        fflush(stdin);
        choice = 0;
        id = 0;
        strcpy(paras, " ");
        strcpy(choice_name, " ");
        continue;
    }

    if (choice != 4 && id == 0)
    {
      tmp = search_in_cache(choice_name, paras);   
      if(tmp!=NULL)    
        printf("id:%s, name: %s, phone: %s\n", tmp->id, tmp->name, tmp->phone);
      else
        printf("Cannot find %s.\n", paras);
    }

    fflush(stdin);
    choice = 0;
    id = 0;
    strcpy(paras, " ");
    strcpy(choice_name, " ");
  }//end_of_while(choice != 4)
}

void create()
{
  /* since the value of count is index+1, it can be new index for creation */
  cache[count] = malloc(sizeof(struct entry));
  sprintf(cache[count]->id, "%d", count);  
  printf("name:");
  scanf("%s", cache[count]->name);
  printf("phone:");
  scanf("%s", cache[count]->phone);
  printf("[Info] Entry created <%s,%s,%s>\n",cache[count]->id, cache[count]->name, cache[count]->phone);
  count++;
}

void update()
{
  int id = 0;
  int choice = 0;

  while(choice != 4)
  {
    printf("Which fieds do you want to change?\n1)name, 2)phone, 3)both, 4)cancel:");
    scanf("%d", &choice);
    
    if(choice == 4)
      return;
    else
    {
      printf("Update entry id:");
      scanf("%d", &id);
    }

    switch(choice)
    {
      case 1:
        printf("New name:");
        scanf("%s", cache[id-1]->name); 
        printf("[Info] Name changed.\n");       
        break;
      case 2:
        printf("New phone:");
        scanf("%s", cache[id-1]->phone);      
        printf("[Info] Phone changed.\n");       
        break;
      case 3:
        printf("New name:");
        scanf("%s", cache[id-1]->name);
        printf("New phone:");
        scanf("%s", cache[id-1]->phone);
        printf("[Info] Name changed.\n");       
        printf("[Info] Phone changed.\n");       
        break;
      default:
        puts("Invalid choice.");    
        break;
    }
    fflush(stdin);
    choice = 0; 
    id = 0;
  }
}

void delete()
{
  int id = 0;
  int choice = 0;
  while(1)
  {
    printf("Type id or -1 to exit:");
    scanf("%d", &id);
    if(id == -1)
      return;

    printf("Are you sure you want to remove entry %d?(1)Yes/(2)No", id);
    scanf("%d", &choice);
    if(choice == 1)
      cache[id-1] = NULL;
    else
    {
      fflush(stdin);
      id = 0;
      choice = 0;
      continue;
    }
  }
  return;
}

/****************************** Main ****************************/

int main(int argc, char *args[])
{
   char usage[] = "";
   char line[MAXLEN];
   int choice = 0;

   fptr = fopen("db.txt", "r");
   if(fptr)
      puts("[Info] File open successfully.");
   else
      puts("[Error] Failed to open file.");

   while(fgets(line, MAXLEN, fptr))
   {
      //important: strdup the string from buffer(line)
      char* entry = strtok(line, "<");
      char* id = strdup(strtok(entry, ","));
      char* name = strdup(strtok(NULL, ","));
      char* phone = strdup(strtok(NULL, ">"));
      put_to_cache(id, name, phone);
      // important: free(entry);
   }
   fclose(fptr);
   printf("[Info] File closed. \n");
   printf("[Info] There are %d entries.\n", count);

   while(choice != 5)
   {
     puts("What do you want to do?\n1)Query\n2)Create\n3)Update\n4)Delete\n5)Exit");
     scanf("%d", &choice);

     switch(choice)
     {
        case 1:
           query();
           break;
        case 2:
           create();           
           break;
        case 3:
           update();
           break;
        case 4:
           delete();
           break;
        case 5:
           fptr = fopen("db.txt", "w");
           write_to_file(count);
           fclose(fptr);
           printf("[Info] File closed.\n");
           return 0;
        default:
           puts("Invalid choice.");
           break;
     }     
     fflush(stdin);
     choice = 0;
   }

   return 0;
}

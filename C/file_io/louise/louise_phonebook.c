#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#define LIST struct tel

// define data structure
    struct tel 
		{ 
		
           char name[15]; 
           char tel[15];
           char id[15];
		   
           LIST *next;  
		}; 
    int total=0;  

// Create a new table    
    LIST *create() 
		{  
             LIST *head,*p1,*p2; 
             head=p1=p2=NULL; 
             printf("Input:'#' that finish this table.\n");
             while(1) 
             { 
                 p1= (LIST*)malloc(sizeof(LIST));  
       /*Name*/  printf("Input name：\n"); 
                 scanf("%s",p1->name); 
                 if(strcmp(p1->name,"#")==0)  
                 { 
                     if(total==0)  
                     { 
                      printf("no creating...\n"); 
                      free(p1);   
                      return (head); 
                     } else {
                          break; 
                     } 
                 } 
      /*Phone*/  printf("Input phone：\n"); 
                 scanf("%s",p1->tel); 
                 if(strcmp(p1->tel,"#")==0)  
                 { 
                     if(total==0) 
                     { 
                      printf("no creating...\n"); 
                      free(p1); 
                      return (head); 
                     } else {
                          break; 
                     } 
                 } 
      /*Id*/     printf("Input id：\n");
                 scanf("%s", p1->id);
                 if(head==NULL) { // when linked list is empty 
                          head=p1; 
                          p2=p1;
                      } else {   // linked list is not empty
                          p2->next=p1;  
                          p2=p1;  
                      } 
                        total++; 
             } 
             p2->next=NULL; 
             printf("\ncreate success...\n\n");
             free(p1); 
             return (head); 
             
        } 

//Read         
    void *read(LIST *head)
		{
			
           LIST *p;
           p = head;
           printf("          name|\t        phone|\t          id|\n");
           if(head == NULL){
                printf("no recording...\n");     
           } else do{ 
                printf("%15s%15s%15s\n",p->name,p->tel,p->id);                
                // next node 
                p = p->next;    
           } while(p!=NULL);   
     }
     
//Delete 
    LIST *del(LIST *head)
	{
			
	    LIST *p1,*p2; 
	    p1=p2=head;
	    char show; // Y or N 
	    char cname[15]; // stored the name want to delete
            if(head == NULL){
                printf("no recording...\n\n");
                } else {
              
			printf("\nInput the name you want to delete it： "); 
			scanf("%s", cname); 
			// find node to delete
			while((strcmp(p1->name,cname)!=0) && p1->next!=NULL)
		    {  
				p2=p1;  
				p1=p1->next;  
		    } 
			// found it
		    if(strcmp(p1->name,cname)==0) // p1->name=cname
			{
                           printf("\nDelete node:\n");
                           printf("          name|\t        phone|\t          id|\n");
                           printf("%15s%15s%15s\n",p1->name,p1->tel,p1->id); 
			   printf("\nReady to delete？Y/N?\n");      
			   getchar(); 
			   scanf("%c",&show); 
			   if(show=='y'||show=='Y') 
				{ 
				  if(p1==head){ 
                                  // first node to delete  
					  head=p1->next;
                                  } else { 
					  p2->next=p1->next;
                                  }    
                                  free(p1);  
                   		  printf("delete success...\n\n");
                		} else { // show = N
			    		printf("\nnot to delete...\n\n"); 
             			}
            		} else  // p1->name!=cname 
                		printf("\nno finding...\n\n");     
            			return (head);  
            	}          
	}
        
//Query    
	void search(LIST *head) 
		{  
			 LIST *p;
                         p=head; 
			 int flag=0; // current position
			 char query;  
             	while(1){
               	if(head == NULL){
                     printf("no recording...\n\n"); break;
             	} else {          
			printf("\nInput the initial name, phone or id: \n"); 
			scanf("%s", &query);   
                	printf("          name|\t        phone|\t          id|\n");   
		   	while(p!=NULL)  
		      	{  
				if(p->name[0]==query||p->tel[0]==query||p->id[0]==query) 
				     { 
				       printf("%15s%15s%15s\n",p->name,p->tel,p->id);
				       flag=1; 
				       } 
                       		       p=p->next;  // check the next node
			         } 
                   	if(flag==0)  
                       		printf("\nno finding...\n\n");
                   		break;     
             }
             }       
		}

//Update
	LIST *update(LIST *head) 
		{ 
		
			LIST *p1;
			LIST *p2; 
			p1=p2=head; 
			char cname[15]; // stored the name want to update
			if(head == NULL){
              printf("no recording...\n\n");
            } else {
			printf("Input name："); 
			scanf("%s", cname);
			// 
			while((strcmp(p1->name,cname)!=0) && p1->next!=NULL)
		    {  
				p2=p1;  
				p1=p1->next;  
		    }
		    if(strcmp(p1->name,cname)==0) // p1->name=cname
			{
				printf("Update node:\n"); 
				printf("          name|\t        phone|\t          id|\n");
                		printf("%15s%15s%15s\n",p1->name,p1->tel,p1->id); 
				printf("Input phone to update: "); 
				scanf("%s",p1->tel); 
				printf("phone renew...\n\n");
				printf("Input id to update: "); 
				scanf("%s",p1->id); 
				printf("id renew...\n\n");
			} else  // p1->name!=cname 
                		printf("\nno finding...\n\n");
            			return(head); 
		    }    
		} 
        		
//------------------------------------------------

     int main() { 
         LIST *head=NULL;
         char choice[6]; 
         int i, num, len, change;
         
         while(1){
              printf("\n");
	      printf("********************************************\n\n");
              printf("# First of all, build the new phonebook.\n");    
              printf("# Choose the digital during 1-6.\n\n");
	      printf("\t1 Build phonebook \n");
              printf("\t2 Read phonebook \n");
              printf("\t3 Delete phonebook \n");
              printf("\t4 Search phonebook \n");
              printf("\t5 Update phonebook \n");
              printf("\t6 Exit \n");
              printf("********************************************\n\n");
              
              scanf("%s", choice); 
		      
			  len=strlen(choice);
              for (i=0; i<len; i++)
		      {
			      if (choice[i]<'0' || choice[i]>'9')
                  break;
		      } 
		      if (i==len){
                	change=atoi(choice); // str to int 
			switch(change){
                          case 1: head=create(); break; //create
                          case 2: read(head); break; //read
                          case 3: head=del(head); break; //delete
                          case 4: search(head); break; //search
                          case 5: head=update(head); break; //update
                          case 6: exit(0); break; //exit
                          default: printf("Choose the digital during 1-6, try again...\n\n");
                    }
              } else 
                     printf("not digital, try again...\n\n");              
         }
         //system("pause"); 
         return 0; 
    } 



#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#define LIST struct tel

//定義結構資料名稱
    struct tel 
		{ 
           char name[15]; 
           char tel[15];
           char id[15];
		   
           LIST *next;  //struct tel *next;
		}; 
//定義變數    
	//struct tel LIST;  
    int total=0;  

//創建新記錄表    
    LIST *create() 
		{  
             LIST *head,*p1,*p2; 
             head=p1=p2=NULL; 
             printf("若要結束請輸入'#'\n");
             while(1) 
             { 
                 p1= (LIST*)malloc(sizeof(LIST));   //動態create一個記憶體空間 
       /*Name*/  printf("請輸入name：\n"); 
                 scanf("%s",p1->name); 
                 if(strcmp(p1->name,"#")==0) // p1->name和"#"相比 =>若同則傳回0 
                 { 
                     if(total==0) //且總筆數為0 
                     { 
                      printf("no creating...\n"); 
                      free(p1);  //釋放記憶體空間 
                      return (head); 
                     } else {
                          break; 
                     } 
                 } 
      /*Phone*/  printf("請輸入phone：\n"); 
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
      /*Id*/     printf("請輸入id：\n");
                 scanf("%s", p1->id);
                 if(head==NULL) { //當鏈表為空的 
                          head=p1; 
                          p2=p1;
                      } else {   // 當鏈表不是空的
                          p2->next=p1; //p1指向新節點 
                          p2=p1; //p2指向鏈表當前尾節點 
                      } 
                        total++; 
             } 
             p2->next=NULL; 
             printf("\ncreate success...\n\n");
             free(p1); 
             return (head); 
             
        } 

//讀取記錄表         
    void *read(LIST *head)
		{
      //利用這個函數負責讀取這個鏈結(因為非建立鏈結串列所以不用使用LIST來建立) 
           LIST *p;
           p = head;
           printf("          name|\t        phone|\t          id|\n");
           if(head == NULL){
                printf("no recording...\n");     
           } else do{
                //印出 
                printf("%15s%15s%15s\n",p->name,p->tel,p->id);                
                //跳到第二個節點 
                p = p->next;    
           } while(p!=NULL);   
     }
     
//刪除記錄表 
    LIST *del(LIST *head)
		{
			LIST *p1,*p2; 
			p1=p2=head;
			char show; //判斷Y or N 
			char cname[15]; //存放要查找姓名
            if(head == NULL){
            printf("no recording...\n\n");
            } else {
              
			printf("\n請輸入要刪除的name： "); 
			scanf("%s", cname); 
			/*先搜尋鏈結中的是否有資料 
               /** p1指向的不是 要的節點，且p1後面還有節點*/
			while((strcmp(p1->name,cname)!=0) && p1->next!=NULL)
		    {  
				p2=p1; //p2指向p1 
				p1=p1->next; //p1向後移一個節點 
		    } 
		    //再判斷這筆資料是否要刪除 
		    if(strcmp(p1->name,cname)==0) // p1->name=cname
			{
                printf("\n要刪除的記錄為:\n");
                printf("          name|\t        phone|\t          id|\n");
                printf("%15s%15s%15s\n",p1->name,p1->tel,p1->id); 
				printf("\n是否要刪除該記錄？Y/N?\n");      
				getchar(); 
				scanf("%c",&show); 
				if(show=='y'||show=='Y') 
				{ 
				  if(p1==head){ 
                      //頭節點 
					  head=p1->next;
                 } else { 
                      //p1指向要刪除的節點，p2->next跳過p1接p1->next 
					  p2->next=p1->next;
                 }    
                free(p1); //要刪的節點用完後，釋放記憶體空間 
                printf("delete success...\n\n");
                } else { // show = N
			    printf("\n該記錄沒有被刪除...\n\n"); 
             }
            } else  // p1->name!=cname 
                printf("\n未能找到符合的記錄，no finding...\n\n");     
            return (head);  
            }          
		}
        
//查詢記錄表    
	void search(LIST *head) 
		{  
			 LIST *p;
             p=head; 
			 int flag=0; //當前位置，初始 flag=0
			 char query; //存放要查找資料 
             while(1){
               if(head == NULL){
                     printf("no recording...\n\n"); break;
             } else {          
				   printf("\n請僅輸入要查詢的name、phone或id的開頭: \n"); 
				   scanf("%s", &query);   
                   printf("          name|\t        phone|\t          id|\n");   
			       while(p!=NULL) //先確定鏈結內有資料尚未搜尋結束 
			       { //且query有符合查找條件 
				     if(p->name[0]==query||p->tel[0]==query||p->id[0]==query) 
				     { 
				       printf("%15s%15s%15s\n",p->name,p->tel,p->id);
				       flag=1; 
				       } 
                       p=p->next;  //檢查下一個節點
			         } 
		           //當flag最後還是0時，表示找不到符合的條件，就印出no finding 
                   if(flag==0)  
                       printf("\n未能找到符合的記錄，no finding...\n\n");
                   break;     
             }
             }       
		}

//更新記錄表
	LIST *update(LIST *head) 
		{ 
			LIST *p1;
			LIST *p2; 
			p1=p2=head; 
			char cname[15]; //存放要查找姓名
			if(head == NULL){
              printf("no recording...\n\n");
            } else {
			printf("請輸入要修改的name："); 
			scanf("%s", cname);
            /*先搜尋鏈結中的是否有資料 
               /** p1指向的不是 要的節點，且p1後面還有節點*/ 
			while((strcmp(p1->name,cname)!=0) && p1->next!=NULL)
		    {  
				p2=p1; //p2指向p1 
				p1=p1->next; //p1向後移一個節點 
		    }
		    if(strcmp(p1->name,cname)==0) // p1->name=cname
			{
				printf("要更新的記錄為:\n"); 
				printf("          name|\t        phone|\t          id|\n");
                printf("%15s%15s%15s\n",p1->name,p1->tel,p1->id); 
				printf("請輸入要更新的phone: "); 
				scanf("%s",p1->tel); 
				printf("phone已更新 \n\n");
				printf("請輸入要更新的id: "); 
				scanf("%s",p1->id); 
				printf("id已更新 \n\n");
			} else  // p1->name!=cname 
                printf("\n未能找到符合的記錄，no finding...\n\n");
            return(head); }    
		} 
        		
//------------------------------------------------

     int main() { 
         LIST *head=NULL;
         char choice[6]; 
         int i, num, len, change;
         
         while(1){
              printf("\n");
              printf("#請先建立新的電話簿記錄\n\n");    
              printf("\t1 建立電話簿記錄表 \n");
              printf("\t2 讀取電話簿記錄表 \n");
              printf("\t3 刪除電話簿記錄表 \n");
              printf("\t4 查詢電話簿記錄表 \n");
              printf("\t5 更新電話簿記錄表 \n");
              printf("\t6 離開電話簿記錄表 \n");
              printf("********************************************\n\n");
              // 避免user輸入非數字，故一開始就把從scanf讀進的值都當成字串 
              scanf("%s", choice);
		      // 檢查字串是否有不是數字出現 
		      len=strlen(choice);
              for (i=0; i<len; i++)
		      {
			      if (choice[i]<'0' || choice[i]>'7')
                  break;
		      } 
		      // 如果字元是'1'-'6'當中的任一個就選擇case執行 
		      if (i==len){
                 change=atoi(choice); //字串轉整數 
			     switch(change){
                          case 1: head=create(); break; //create
                          case 2: read(head); break; //read
                          case 3: head=del(head); break; //delete
                          case 4: search(head); break; //search
                          case 5: head=update(head); break; //update
                          case 6: exit(0); break; //exit
                          default: printf("請選擇1-6的範圍，try again...\n\n");
                    }
              } else 
                     printf("請選擇1-6的範圍，try again...\n\n");              
         }
         //system("pause"); 
         return 0; 
    } 


/**
 * Check by Veck on Feb/04, 2015: OK!
 * Advise:
 * 1. Recommand don't use Chinese in terminal program or you should make sure encoding.
 */

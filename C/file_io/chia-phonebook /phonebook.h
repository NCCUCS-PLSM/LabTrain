#define CAPACITY 100

#define ADD    'a'
#define DELETE 'd'
#define FINDNAME 'f'
#define LIST   'l'
#define QUIT   'q'
#define FINDID 'i' //n
#define FINDNUM 'n'//n

#define NAME_LEN 80
#define NUMBER_LEN 40
#define ID_LEN 40//n
//

typedef struct {
  char id[ ID_LEN ];//n
  char name[ NAME_LEN ];
  char number[ NUMBER_LEN ];
} phone_record;

//

char get_command( void );
phone_record *get_record( void );
void add_record( phone_record *new_record );
void list_phonebook( void );
int find_name( char *name );
void delete_name( char *name );
int find_number(char *number);//n
int find_id(char *id);//n

//void delete_number(char *name );//n
#include <stdio.h>
#include  "stdlib.h"
#include "phonebook.h"
#include <string.h>

int num_entries;           // Number of entries currently 
phone_record **phonebook;  // Where the names are stored

int main( int argc, char **argv ) {
  char ch;
  char name[ NAME_LEN ];
  char number[ NUMBER_LEN ];
  char id[ ID_LEN ];
  char confirm[ 10 ];//yes no
  phone_record *rec;
  int loc;

  // 開新電話簿
  phonebook = (phone_record **)malloc( sizeof( phone_record *) * CAPACITY );
  num_entries = 0;

  // 電話簿選項
  while ( ( ch = get_command() ) != QUIT ) {
    switch( ch ) {
      case ADD:
        rec = get_record();
        if ( find_name( rec->name ) == -1 ) {
          add_record( rec );
        }
        else {
          printf( "此姓名已經存在\n" );
        }
        break;

      //
      //case DELETE
      case DELETE:
        // Get name to delete
        printf( "Name:  " );
        scanf( "%s", name );

        // If it is there delete it
        if ( ( loc = find_name( name ) ) != -1 ) {
          printf( "Are you sure (y/n)?" );
          scanf( "%s", confirm );

          if ( confirm[ 0 ] == 'y' ) {
            delete_name( name );
          }
        }
        else {
          printf( "尚未有此人\n" );
        }
        break;
	  //***
      case FINDID:
      	printf( "ID:  " );
        scanf( "%s", id );
        
        if ( ( loc = find_id( id ) ) != -1 ) {
        	printf( "id:  %s\n", phonebook[ loc ]->id );	
        }
        else{
        	printf( "無此帳號\n" );	
        }
        break;
      //*** 	
      //***
      case FINDNUM:
      	printf( "Number:  " );
        scanf( "%s", number );
        
        if ( ( loc = find_number( number ) ) != -1 ) {
        	printf( "Name:  %s\n", phonebook[ loc ]->name );	
        }
        else{
        	printf( "此為空號\n" );	
        }
        break;
      //*** 	
      case FINDNAME:
        // Name to find
        printf( "Name:  " );
        scanf( "%s", name );

        // Look for the name
        if ( ( loc = find_name( name ) ) != -1 ) {
          printf( "Number:  %s\n", phonebook[ loc ]->number );
        }
        else {
          printf( "尚未有此人\n" );
        }
        break;

      case LIST:
        // List the phonebook
        list_phonebook();
        break;
    }
  }
}

/* 
 * Read and return a command from the keyboard. 
 */
char get_command() {
  char line[ 80 ];

  do {
    printf( "ADD:a\n" );
    printf("DEL:d\n");
    printf("FINDID:i\n");
    printf("FINDNAME:f\n");
    printf("FINDNUM:n\n");//n
    printf("LIST:l\n");
    printf("QUIT:q\n");
	
    // 
    if ( scanf( "%s", line ) == -1 ) {
      line[ 0 ] = QUIT;
      printf( "\n" );  
    }
  
    // 縮寫
    switch( line[ 0 ] ) {
      case ADD:
      case DELETE:
      case FINDNAME:
      case FINDNUM://n
      case FINDID://n
      case LIST:
      case QUIT:
        break;
      default://防呆
        printf( "錯誤指令\n" );
        line[ 0 ] = 0;
    }
  } while ( line[ 0 ] == 0 );

  return line[ 0 ];
}

//新增一筆資料
void add_record( phone_record *new_record ) {
  int cur;

  // Make sure there is room
  if ( num_entries == CAPACITY ) {
    printf( "電話簿容量已滿\n" );
  }
  else {
    // 
    for ( cur = num_entries; 
          cur > 0 && strcmp( phonebook[ cur - 1 ]->name, new_record->name ) > 0;
          cur = cur - 1 ) {

      phonebook[ cur ] = phonebook[ cur - 1 ];
    }

    
    phonebook[ cur ] = new_record;
    num_entries = num_entries + 1;
  }
}

//List the   phonebook.
 
void list_phonebook() {
  int i;

  if ( num_entries != 0 ) {
    printf( "Id\tName\t\tNumber\n" );//
    printf( "----\t\t------\n" );

    for ( i = 0; i < num_entries; i = i + 1 ) {
      printf( "%s\t%s\t\t%s\n", phonebook[ i ]->id,phonebook[ i ]->name, phonebook[ i ]->number );
    }
  }
  else {
    printf( "電話簿目前是空的\n" );
  }
}

/*
 * Delete the specified name from the phonebook.
 */
void delete_name( char *name ) {
  int found;
  int i;

  // Start at the top looking for the record to delete.  Once it is
  // found starting moving elements in the phonebook up one
  // position.
  for ( i = 0, found = 0; i < num_entries; i = i + 1 ) {
    if ( !found ) {
      found = strcmp( name, phonebook[ i ]->name ) == 0;
    }
    else {
      phonebook[ i - 1 ] = phonebook[ i ];
    }
  }

  if ( found ) num_entries = num_entries - 1;
}
//***
int find_id( char *id ) {
  int pos = -1;
  int i;

  for ( i = 0; pos == -1 && i < num_entries; i = i + 1 ) {
    if ( strcmp( id, phonebook[ i ]->id ) == 0 ) pos = i;
  }  

  return pos;
}

//find name
int find_name( char *name ) {
  int pos = -1;
  int i;

  for ( i = 0; pos == -1 && i < num_entries; i = i + 1 ) {
    if ( strcmp( name, phonebook[ i ]->name ) == 0 ) pos = i;
  }  

  return pos;
}

//***
int find_number( char *number ) {
  int pos = -1;
  int i;

  for ( i = 0; pos == -1 && i < num_entries; i = i + 1 ) {
    if ( strcmp( number, phonebook[ i ]->number ) == 0 ) pos = i;
  }  

  return pos;
}

//***
 // 
 
phone_record *get_record() {
  phone_record *rec;
  char *name;
  char *number;

  
  rec = (phone_record *)malloc( sizeof( phone_record ) );

  // Get the data
  printf( "Id:  " );
  scanf( "%s", rec->id );
  
  printf( "Name:  " );
  scanf( "%s", rec->name );

  printf( "Phone:  " );
  scanf( "%s", rec->number );

  return rec;
}

/**
 * Check by Veck on Feb/06, 2015
 * Advise:
 * 1. Recommand don't use Chinese in terminal program or you should make sure encoding.
 * 2. UI layout could be prettier.
 */

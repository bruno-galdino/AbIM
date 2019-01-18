
#ifndef TAD_H
#define TAD_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LIST_AUTOFREE __attribute__( (cleanup(ListFree) ) )
#define STR_ARRAY_INIT { NULL,0 }

typedef struct list_t 
{
    int    id;
    void  *data;
    int    state;
    struct list_t *next;
    struct list_t *last;
    
} list_t;

typedef struct
{
    int x,y;
    
} point_t;

typedef struct
{
    char  *str;
    size_t len;
    
} str_array_t;

list_t *CreateList( );
void    DestroyList( list_t *list);
void    ListFree( list_t **list );
list_t *ListAppend( list_t *list, int id, int state );
list_t *GetItem( list_t *list, int id );
list_t *GetItemAdd( list_t *list, int id );
bool    StrArrayAppend( str_array_t *array, char *str );
void    StrArrayFree( str_array_t *array );

#endif
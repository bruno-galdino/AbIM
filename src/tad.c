
#include "../include/tad.h"

list_t *CreateList( )
{
    return calloc( sizeof(list_t),1);
}

void DestroyList( list_t *list )
{
    list_t *l = list;
    list_t *temp;    
    
    while( l )
    {
        temp = l;
        l = l->next;
        free(temp);
    }
}

void ListFree( list_t **list )
{
    DestroyList( *list );
}

list_t *ListAppend( list_t *list, int id, int state )
{
    list_t *new;
    
    if( !list->last )
    {
        list->id = id;
        list->state = state;
        list->last  = list;
        return list;
    }
    
    new = calloc( sizeof(list_t), 1 );
    
    if( new )
    {
        list->last = list->last->next = new;
        new->id = id;
        new->state = state;
    }
    
    return new;
    
}

list_t *GetItem( list_t *list, int id )
{
    while( list )
    {
        if( list->id == id )
        {
            return list;
        }
        
        list = list->next;
    }
    
    return NULL;
}

list_t *GetItemAdd( list_t *list, int id )
{
    list_t *aux = list;
    
    while( list )
    {
        if( list->id == id )
        {
            return list;
        }
        
        list = list->next;
    }
    
    
    return ListAppend( aux, id, 0 );
    
}

bool StrArrayAppend( str_array_t *array, char *str )
{
    size_t len = strlen(str);
    char *new = realloc( array->str, array->len + len );
    
    if( new )
    {
        memcpy( &new[array->len], str, len );
        array->str = new;
        array->len += len;
        
        return true;
    }
    
    return false;
}

void StrArrayFree( str_array_t *array )
{
    free( array->str );
    array->len = 0;
    array->str = NULL;
}
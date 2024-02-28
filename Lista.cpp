#include <stdio.h>
#include <malloc.h>
#include "Lista.h"


ListHead* CreateList()
{
	return (ListHead*)calloc( 1, sizeof(ListHead) );
}

int Insert2List( ListHead* pHead, int linijka ) 
{
	if( !pHead ) return 0;

	ListItem* pNew = (ListItem*)calloc( 1, sizeof(ListItem) ); 
	if( !pNew ) return 0;

	pNew->linijka = linijka; 

	if( !pHead->pFirst ) 
	{
		pHead->pFirst = pNew; 
	}
	else
	{
		pHead->pLast->pNext = pNew; 
	}
	pHead->pLast = pNew;
	return 1;
}

void PrintList( ListHead* pHead )
{
	ListItem* v = pHead->pFirst;
	while( v )
	{
		printf( "%d ",v->linijka );
		v = v->pNext;
	}
}

void ClearList(ListHead* pList)
{
	if( !pList )
	{
		printf( "Error: pList doesn't exist\n" );
		return;
	}

	while( !IsEmpty(pList->pFirst) )
	{
		ListItem* temp =  pList->pFirst->pNext;
		free( pList->pFirst );
		pList->pFirst = temp;
	}
	pList->pLast = NULL;
}

int IsEmpty( ListItem* pList )     
{
	return !( pList->pNext && pList );
}


void RemoveList( ListHead** pList )
{
	if( !pList || !*pList )
	{
		printf( "Error: list doesn't exist\n" );
		return;
	}
	ClearList( *pList );
	free( *pList );
	*pList = NULL;
}
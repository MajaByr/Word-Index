#pragma once

typedef struct tagListItem
{
	int linijka;
	tagListItem* pNext;

}ListItem;

typedef struct tagListHead
{
	tagListItem* pFirst;
	tagListItem* pLast;
}ListHead;

int IsEmpty( ListItem* pList );
ListHead* CreateList(); 
int Insert2List( ListHead* pAfter, int linia ); 
void PrintList( ListHead* pHead ); 
void RemoveList( ListHead** pList );
void ClearList( ListHead* pList );

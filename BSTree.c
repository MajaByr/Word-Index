#include "BSTree.h"
#include <stdio.h>
#include <malloc.h>

void Visit( TreeItem* pTItem, int linijka );

TreeItem* FindAndInsert ( TreeItem* pRoot, char* pWord, int linijka, int (__cdecl* StrCmp)(char*, char*) )
{
	if( !pRoot )
	{
		pRoot = (TreeItem*)calloc( 1, sizeof(TreeItem) );
		if( !pRoot ) return NULL;
		pRoot->pWord = pWord;
		pRoot->ilosc = 1;
		pRoot->linijki = CreateList();
		if( !Insert2List(pRoot->linijki,linijka) ) return NULL; 
		return pRoot;
	}

	if( StrCmp(pWord,pRoot->pWord) < 0 )
	{
		pRoot->pLeft = FindAndInsert( pRoot->pLeft, pWord, linijka, StrCmp );
	}

	else if( StrCmp(pWord,pRoot->pWord) > 0 )
	{
		pRoot->pRight = FindAndInsert( pRoot->pRight, pWord, linijka, StrCmp );
	}
	else { Visit(pRoot,linijka); }
	return pRoot;
}

void inOrder( TreeItem* pRoot )
{
	if( !pRoot ) return;

	inOrder( pRoot->pLeft );
	PrintTreeItem( pRoot );
	inOrder( pRoot->pRight );
}

TreeItem* cutTree( TreeItem* pRoot )
{
	if( !pRoot ) return NULL;

	pRoot->pLeft = cutTree( pRoot->pLeft );
	cutTree( pRoot->pRight );
	RemoveList( &pRoot->linijki );
	free( pRoot );
	return NULL;
}

void PrintTreeItem( TreeItem* pTItem ) 
{
	printf( "%s\t ilosc wystapien: %d\t nr linii: ", pTItem->pWord, pTItem->ilosc );
	PrintList( pTItem->linijki );
	printf( "\n" );
}

void Visit( TreeItem* pTItem, int linijka )
{
	Insert2List( pTItem->linijki, linijka );
	pTItem->ilosc++;
}

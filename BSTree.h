#pragma once
#include "Lista.h" 

typedef struct tagTreeItem
{
	char* pWord; //word
	int ilosc; //how many times appears
	ListHead* linijki; //lines where appears
	tagTreeItem* pLeft; //left subtree
	tagTreeItem* pRight; //right subtree 

} TreeItem;

TreeItem* FindAndInsert ( TreeItem* pRoot, char* pWord, int linijka, int (__cdecl* StrCmp)(char*,char*) );
void PrintTreeItem( TreeItem* pTItem );
void inOrder( TreeItem* pRoot );
TreeItem* cutTree( TreeItem* pRoot );

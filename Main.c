#include "BSTree.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Characters.h"

#define DEBUG
#define EOFERR -1
#define WORDSIZE 9 

int line = 1;

TreeItem* readData( FILE* fin ); //reads data from input file
int print2File ( TreeItem* pRoot );
int StrCmp( char* pWord1,char* pWord2 );
void reallocWord( char** pWord, int currsize );
char* readWort( FILE* fin );

int main( int argc,char* argv[] )
{
#ifdef DEBUG
	printf( "//////////////PROGRAM FOR CREATING WORD INDEX//////////////\n" );
	printf( "Input file: %s\n", argv[1] );
#endif

	if( argc != 2 )
	{
		printf( "Usage: %s <input_file>\n", argv[0] );
		return -1;
	}

	FILE* fin = NULL;

	if( (fin = fopen(argv[1],"rt")) == NULL )
	{
		perror( "Main: Error open input file\n" );
		return -2;
	}

	TreeItem* pRoot = readData( fin ); //reading words to BST

	if( !pRoot )
	{
		printf( "Main: Write words to BST error\n" );
		return 11;
	}

	if( !print2File(pRoot) ) //printing to file
	{
		printf( "Main: Write to file error\n" );
		return 21;
	}

	inOrder( pRoot ); //inorder print of elements in queue

	cutTree( pRoot ); //free memory

	return 0;
}

char* readWort(FILE* fin)
{
	char* pWord = NULL;
	char* c = (char*)calloc( 1, sizeof(char) ); 
	//fscanf( fin, "%c", c );
	while( !isLetter(c) ) 
	{
		if( fscanf(fin,"%c",c) == EOF ) return NULL; //returns NULL when EOF
		if( *c == '\n' ) line++;
	}

	ungetc( *c, fin );
	free( c );

	int i = 0;
	while( !i || isAlpha(pWord+i-1) )
	{
		if( !((i)%WORDSIZE) ) reallocWord( &pWord, i );
		fscanf( fin, "%c", pWord+i );
		i++;
	}
	ungetc( *(pWord+i-1) , fin );
	pWord[i-1] = 0;
	return pWord;
}

TreeItem* readData( FILE* fin ) 
{
	TreeItem* pRoot = NULL;
	char* pWord;
	while( pWord = readWort(fin) ) //readWort returns NULL when EOF
	{
		pRoot = FindAndInsert( pRoot, pWord, line, StrCmp );
	}

		return pRoot;
}

int print2File ( TreeItem* pRoot ) 
{

	FILE* fout = freopen( "WordIndex.txt", "w",stdout );
	if( fout == NULL )
	{
		printf( "print2File: ERROR open output file\n" );
		return 0;
	}
	printf( "Words in index:\n" );
	inOrder( pRoot );

	if( fclose(fout) ) return 0;
	freopen( "CON", "w", stdout );

	return 1;
}

int StrCmp( char* pWord1, char* pWord2 ) 
{
	char* pCopy1 = (char*)calloc( strlen(pWord1)+1, sizeof(char) );
	char* pCopy2 = (char*)calloc( strlen(pWord2)+1, sizeof(char) );
	if( !pCopy1 || !pCopy2 )
	{
		printf( "StrCmp: Creating queue error\n" );
		return 0;
	}

	strcpy( pCopy1, pWord1 );
	strcpy( pCopy2, pWord2 );
	_strupr( pCopy1 ); 
	_strupr( pCopy2 );

	int res = strcmp( pCopy1, pCopy2 );
	free( pCopy1 );
	pCopy1 = NULL;
	free( pCopy2 );
	pCopy2 = NULL;

	return res;
}

void reallocWord( char** pWord, int currsize )
{
	char* pTemp = *pWord;

	*pWord = (char*)realloc( *pWord, currsize+WORDSIZE*sizeof(char)+(!currsize) );
	if( !*pWord )																
	{
		printf( "reallocWord: Memory allocation error\n" );
		*pWord = pTemp; 
		return;
	}

	memset( *pWord+currsize, 0, WORDSIZE*sizeof(char) );
}

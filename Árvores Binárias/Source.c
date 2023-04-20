//utilizar os #include necess�rios
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
//-------------------------------------------
#define DATA(node) ((node)->Data)
#define LEFT(node) ((node)->Left)
#define RIGHT(node) ((node)->Right)
#define EMPTY NULL
#define NO_LINK NULL
//-------------------------------------------
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef struct _BTREE_NODE {
	void* Data;
	struct _BTREE_NODE* Left;
	struct _BTREE_NODE* Right;
} BTREE_NODE;
typedef BTREE_NODE* BTREE;
//-------------------------------------------
//---declaracao de funcoes----------
STATUS initBTree(BTREE*);
BOOLEAN emptyBTree(BTREE);
BOOLEAN isLeaf(BTREE_NODE*);
STATUS createNewBTNode(BTREE_NODE**, void*);
void InOrder(BTREE);
void PostOrder(BTREE);
void PreOrder(BTREE);
STATUS insertIntBST(BTREE*, void*);
STATUS insertBT(BTREE*, void*, void*, void*);
//-------------------------------------------
int main()
{
	srand(time(NULL));
	BTREE BT;
	int i;
	int* pInt;
	initBTree(&BT);
	for (i = 0; i < 30; i++)
	{
		pInt = (int*)malloc(sizeof(int));
		//*pInt = rand()%100;
		*pInt = i;
		insertIntBST(&BT, pInt);
	}
	InOrder(BT);
	printf("\n");
	PostOrder(BT);
	printf("\n");
	PreOrder(BT);
	printf("\n");
	printf("Altura: %d\n", BTHeight(BT));
	printf("Tamanho: %d\n", BTSize(BT));
	return 0;
}
/**************************************************************
* Fun��o initBTree(): Inicializa a �rvore bin�ria
*
* Par�metros: pBT � �rvore bin�ria (passado por ref)
* Sa�da: STATUS
***************************************************************/
STATUS initBTree(BTREE * pBT)
{
	*pBT = NULL;
	return OK;
}
/**************************************************************
* Fun��o emptyBTree(): verifica se a �rvore bin�ria est� vazia
*
* Par�metros: BT � �rvore bin�ria
* Sa�da: TRUE se a �rvore bin�ria estiver vazia, FALSE caso contr�rio
***************************************************************/
BOOLEAN emptyBTree(BTREE BT)
{
	return (BT == NULL) ? TRUE : FALSE;
}
/**************************************************************
* Fun��o isLeaf(): verifica se adeterminado n� da �rvore bin�ria � folha
*
* Par�metros: pNode � apontador para n� (da �rvore bin�ria)
* Sa�da: TRUE se for uma folha, FALSE caso contr�rio
***************************************************************/
BOOLEAN isLeaf(BTREE_NODE* pNode)
{
	return ((LEFT(pNode) == NULL) && (RIGHT(pNode) == NULL)) ? TRUE : FALSE;
}
/**************************************************************
* Fun��o printBTree(): apresenta no ecr� os elementos da �rvore bin�ria
*
* Par�metros: BT � �rvore bin�ria
* Sa�da: void
*
* Esta fun��o n�o � gen�rica: s� funciona para elementos de tipo INT
***************************************************************/
void InOrder(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return;
	InOrder(LEFT(BT));
	printf("%d, ", *(int*)DATA(BT));
	InOrder(RIGHT(BT));
	return;
}

void PostOrder(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return;
	PostOrder(LEFT(BT));
	PostOrder(RIGHT(BT));
	printf("%d, ", *(int*)DATA(BT));
	return;
}

void PreOrder(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return;
	printf("%d, ", *(int*)DATA(BT));
	PreOrder(LEFT(BT));
	PreOrder(RIGHT(BT));
	return;
}

int BTHeight(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return 0;
	int left = BTHeight(LEFT(BT));
	int right = BTHeight(RIGHT(BT));
	if (left > right) return left + 1;
	else return right + 1;
}

int BTSize(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return 0;
	return BTSize(LEFT(BT)) + BTSize(RIGHT(BT)) + 1;
}
/**************************************************************
* Fun��o insertIntBST(): insere um elemento (n�) numa BST
*
* Par�metros: pBT � BST (passado por ref)
* pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: OK se o n� foi inserido na BST e ERROR caso contr�rio
* Esta fun��o n�o � gen�rica: s� funciona para elementos de tipo INT
***************************************************************/
STATUS insertIntBST(BTREE * pBT, void* pData)
{
	if (emptyBTree(*pBT))
	{
		BTREE_NODE* pNew;
		if (createNewBTNode(&pNew, pData) == ERROR)
			return ERROR;
		*pBT = pNew;
		return OK;
	}
	else if (*(int*)(pData) < *(int*)(DATA(*pBT)))
		insertIntBST(&(LEFT(*pBT)), pData);
	else insertIntBST(&(RIGHT(*pBT)), pData);
	return OK;
}
/**************************************************************
* Fun��o createNewBTNode(): cria um n� da �rvore bin�ria
*
* Par�metros: pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: apontador para o n� criado ou NULL em caso de erro
***************************************************************/
STATUS createNewBTNode(BTREE_NODE** pNew, void* pData)
{
	BTREE_NODE* pTemp;
	if ((pTemp = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) == NULL)
		return ERROR;
	*pNew = pTemp;
	DATA(pTemp) = pData;
	LEFT(pTemp) = NULL;
	RIGHT(pTemp) = NULL;
	return OK;
}
//utilizar os #include necessários
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
		*pInt = rand()%100;
		//*pInt = i;
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
* Função initBTree(): Inicializa a árvore binária
*
* Parâmetros: pBT – árvore binária (passado por ref)
* Saída: STATUS
***************************************************************/
STATUS initBTree(BTREE * pBT)
{
	*pBT = NULL;
	return OK;
}
/**************************************************************
* Função emptyBTree(): verifica se a árvore binária está vazia
*
* Parâmetros: BT – árvore binária
* Saída: TRUE se a árvore binária estiver vazia, FALSE caso contrário
***************************************************************/
BOOLEAN emptyBTree(BTREE BT)
{
	return (BT == NULL) ? TRUE : FALSE;
}
/**************************************************************
* Função isLeaf(): verifica se adeterminado nó da árvore binária é folha
*
* Parâmetros: pNode – apontador para nó (da árvore binária)
* Saída: TRUE se for uma folha, FALSE caso contrário
***************************************************************/
BOOLEAN isLeaf(BTREE_NODE* pNode)
{
	return ((LEFT(pNode) == NULL) && (RIGHT(pNode) == NULL)) ? TRUE : FALSE;
}
/**************************************************************
* Função printBTree(): apresenta no ecrã os elementos da árvore binária
*
* Parâmetros: BT – árvore binária
* Saída: void
*
* Esta função não é genérica: só funciona para elementos de tipo INT
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
* Função insertIntBST(): insere um elemento (nó) numa BST
*
* Parâmetros: pBT – BST (passado por ref)
* pData - apontador genérico para os dados a inserir no nó criado
* Saída: OK se o nó foi inserido na BST e ERROR caso contrário
* Esta função não é genérica: só funciona para elementos de tipo INT
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
* Função createNewBTNode(): cria um nó da árvore binária
*
* Parâmetros: pData - apontador genérico para os dados a inserir no nó criado
* Saída: apontador para o nó criado ou NULL em caso de erro
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
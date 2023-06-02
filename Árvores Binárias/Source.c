//utilizar os #include necessários
#define _CRT_SECURE_NO_WARNINGS
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
#define MAX_NAME 20
#define STAGES 15
//-------------------------------------------
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _BTREE_LOCATION { BTREE_LEFT, BTREE_RIGHT } BTREE_LOCATION;	
typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;
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
STATUS ReadPlayersFromFile(void** players, char* file_name);
BTREE_NODE *CreateBtree(void** v, int i , int s);
int BTHeight(BTREE);
int BTSize(BTREE);
int BTCountLeaves(BTREE);
int BTCountNodes(BTREE);
int PrintLeaves(BTREE);
void Printwinnergames(BTREE);
//-------------------------------------------
int main()
{
	//srand(time(NULL));
	//BTREE BT;
	//int i;
	//int* pInt;
	//initBTree(&BT);
	//for (i = 0; i < 30; i++)
	//{
	//	pInt = (int*)malloc(sizeof(int));
	//	*pInt = rand()%100;
	//	//*pInt = i;
	//	insertIntBST(&BT, pInt);
	//}
	//InOrder(BT);
	//printf("\n");
	//PostOrder(BT);
	//printf("\n");
	//PreOrder(BT);
	//printf("\n");
	//printf("Altura: %d\n", BTHeight(BT));
	//printf("Tamanho: %d\n", BTSize(BT));
	//return 0;
	BTREE BT = NULL;
	PLAYER* players[STAGES];
	ReadPlayersFromFile(players, "torneio.txt");
	BT = CreateBtree(players, 0, STAGES);
	InOrder(BT);
	printf("\n_________________________________________________________\n");
	PrintLeaves(BT);
	printf("\n_________________________________________________________\n");
	Printwinnergames(BT);
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
/**************************************************************/
void InOrder(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return;
	InOrder(LEFT(BT));
	printf("\n%s,%d ", ((PLAYER*)DATA(BT))->name, ((PLAYER*)DATA(BT))->sets);
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

int BTCountLeaves(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return 0;
	if (isLeaf(BT) == TRUE) return 1;
	return BTCountLeaves(LEFT(BT)) + BTCountLeaves(RIGHT(BT));
}

int BTCountNodes(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return 0;
	if (isLeaf(BT) == TRUE) return 0;
	return BTCountNodes(LEFT(BT)) + BTCountNodes(RIGHT(BT)) + 1;
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
/**************************************************************/
STATUS ReadPlayersFromFile(void** players, char* file_name)
{
	FILE* fp;
	int j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ((PLAYER*)ptr_data)->name);
				fscanf(fp, "%d\n", &(((PLAYER*)ptr_data)->sets));
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}
/**************************************************************/
BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}
BTREE_NODE* AddBtreeNode(BTREE_NODE* upnode, BTREE_NODE* node, BTREE_LOCATION where)
{
	BTREE_NODE* tmp_pt = upnode;
	if (where == BTREE_LEFT)
	{
		if (LEFT(upnode) == NULL)
			LEFT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	else
	{
		if (RIGHT(upnode) == NULL)
			RIGHT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	return tmp_pt;
}
BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}
BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}
/***************************************************************/
int PrintLeaves(BTREE BT) {
	if (emptyBTree(BT) == TRUE) return 0;
	if (isLeaf(BT) == TRUE)
	{
		printf("\n%s,%d ", ((PLAYER*)DATA(BT))->name, ((PLAYER*)DATA(BT))->sets);
		return 1;
	}
	return PrintLeaves(LEFT(BT)) + PrintLeaves(RIGHT(BT));
}
/**************************************************************/
int PrintNonLeaves(BTREE BT) {
	if (emptyBTree(BT) == TRUE) return 0;
	if (isLeaf(BT) == TRUE) return 0;
	printf("\n%s,%d ", ((PLAYER*)DATA(BT))->name, ((PLAYER*)DATA(BT))->sets);
	return PrintNonLeaves(LEFT(BT)) + PrintNonLeaves(RIGHT(BT)) + 1;
}
/**************************************************************/
void Printwinnergames(BTREE BT) {
	if (isLeaf(BT) == TRUE) return 0;
	printf("Jogo:\nPlayer: %s->%d vs player: %s->%d\n", ((PLAYER*)DATA(BT->Left))->name, ((PLAYER*)DATA(BT->Left))->sets, ((PLAYER*)DATA(BT->Right))->name, ((PLAYER*)DATA(BT->Right))->sets);
	printf("Vencerdor: %s", ((PLAYER*)DATA(BT))->name);		
	printf("\n_________________________________________________________\n");
	Printwinnergames(LEFT(BT));
	Printwinnergames(RIGHT(BT));
}
/**************************************************************/
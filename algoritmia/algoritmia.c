//utilizar os #include necess�rios
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
//-------------------------------------------
#define EMPTY NULL
#define NO_LINK NULL
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
//-------------------------------------------
typedef struct _LIST_NODE {
	void* pData;
	struct _LIST_NODE* next;
} LIST_NODE;
typedef LIST_NODE* LIST;
#define DATA(node) ((node)->pData)
#define NEXT(node) ((node)->next)
//-------------------------------------------	
typedef struct _ESTACAO {
	char nome[25];
	float custo;
	BOOLEAN estado, ligacao;
}ESTACAO;
//-------------------------------------------
void initList(LIST* plist);
BOOLEAN emptyList(LIST list);
LIST_NODE* createNewNode(void* pdata);
STATUS insertStartList(LIST* plist, void* pdata);
STATUS insertEndList(LIST* plist, void* pdata);
int ListSize(LIST list);
void printList(LIST list); // esta solu��o n�o � �gen�rica�
STATUS readdata(LIST* lista, char* file);


int main() {
	LIST lista = NULL;
	if (readdata(&lista, "Linha1.txt"))
		printList(lista);
}

STATUS readdata(LIST* lista, char* file) {
	FILE* fp = NULL;
	ESTACAO* pt = NULL;
	if (fp = fopen(file, "r")) {
		{
			while (!feof(fp))
			{
				if ((pt = (ESTACAO*)malloc(sizeof(ESTACAO))) != NULL && (insertStartList(lista, pt)) == OK)	
					fscanf(fp, "%[^;];%f;%d;%d;\n",pt->nome,&(pt->custo), &(pt->estado),&(pt->ligacao));
			}
			fclose(fp);
			return OK;
		}
		return ERROR;
	}
}
/**************************************************************
* Fun��o initList(): Inicializa a lista
*
* Par�metros: pL - lista (passado por ref)
* Sa�da: void
***************************************************************/
void initList(LIST * pL)
{
	*pL = NULL;
}
/**************************************************************
* Fun��o emptyList(): verifica se a lista est� vazia
*
* Par�metros: L - lista
* Sa�da: TRUE se a lista estiver vazia, FALSE caso contr�rio
***************************************************************/
BOOLEAN emptyList(LIST L)
{
	return (L == NULL) ? TRUE : FALSE;
}
/**************************************************************
* Fun��o insertStartList(): insere um elemento (n�) no in�cio da lista
*
* Par�metros: pL � lista (passado por ref)
* pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: OK se o n� foi inserido na LISTA e ERROR caso contr�rio
***************************************************************/
STATUS insertStartList(LIST* pL, void* pData)
{
	LIST_NODE* pNew;
	if ((pNew = createNewNode(pData)) == EMPTY)
		return ERROR;
	NEXT(pNew) = *pL;
	*pL = pNew;
	return OK;
}
/**************************************************************
* Fun��o insertEndList(): insere um elemento (n�) no final da lista
*
* Par�metros: pL � lista (passado por ref)
* pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: OK se o n� foi inserido na lista e ERROR caso contr�rio
***************************************************************/
//STATUS insertEndList(LIST * pL, void* pData)
//{
//	LIST_NODE* pNew, * pTemp;
//	if ((pNew = createNewNode(pData)) == EMPTY)
//		return ERROR;
//	if (*pL == NULL)
//		*pL = pNew;
//	else
//	{
//		pTemp = *pL;
//		while (NEXT(pTemp) != NULL)
//			pTemp = NEXT(pTemp);
//		NEXT(pTemp) = pNew;
//	}
//	return OK;
//}
/**************************************************************
* Fun��o listSize(): calcula o n�mero de elementos da lista
*
* Par�metros: L � lista
* Sa�da: n�mero de elementos da lista
***************************************************************/
int listSize(LIST L)
{
	LIST pTemp = L;
	int count = 0;
	while (pTemp != NULL)
	{
		count++;
		pTemp = NEXT(pTemp);
	}
	return count;
}
/**************************************************************
* Fun��o printList(): apresenta no ecr� os elementos da lista
*
* Par�metros: L � lista
* Sa�da: void
*
* Esta fun��o n�o � gen�rica: s� funciona para elemento de tipo ALUNO
***************************************************************/
void printList(LIST L)
{
	LIST pTemp = L;
	if (emptyList(pTemp) == TRUE)
	{
		printf("\nLista vazia.\n");
		return;
	}
	while (pTemp != NULL)
	{
		printf(" %s;%.2f;%d;%d\n", ((ESTACAO*)DATA(pTemp))->nome, ((ESTACAO*)DATA(pTemp))->custo, ((ESTACAO*)DATA(pTemp))->estado, ((ESTACAO*)DATA(pTemp))->ligacao);
		pTemp = NEXT(pTemp);
	}
	printf("NULL\n");
	return;
}
/**************************************************************
* Fun��o createNewNode(): cria um n� da lista
*
* Par�metros: pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: apontador para o n� criado ou NULL em caso de erro
***************************************************************/
LIST_NODE* createNewNode(void* pData)
{
	LIST_NODE* pNew=NULL;
	if ((pNew = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
	{
		pNew->pData = pData;
		pNew->next = NULL;
	}
	return pNew;
}
//-------------------------------------------
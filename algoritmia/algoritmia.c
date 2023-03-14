//utilizar os #include necessários
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
void printList(LIST list); // esta solução não é “genérica”
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
* Função initList(): Inicializa a lista
*
* Parâmetros: pL - lista (passado por ref)
* Saída: void
***************************************************************/
void initList(LIST * pL)
{
	*pL = NULL;
}
/**************************************************************
* Função emptyList(): verifica se a lista está vazia
*
* Parâmetros: L - lista
* Saída: TRUE se a lista estiver vazia, FALSE caso contrário
***************************************************************/
BOOLEAN emptyList(LIST L)
{
	return (L == NULL) ? TRUE : FALSE;
}
/**************************************************************
* Função insertStartList(): insere um elemento (nó) no início da lista
*
* Parâmetros: pL – lista (passado por ref)
* pData - apontador genérico para os dados a inserir no nó criado
* Saída: OK se o nó foi inserido na LISTA e ERROR caso contrário
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
* Função insertEndList(): insere um elemento (nó) no final da lista
*
* Parâmetros: pL – lista (passado por ref)
* pData - apontador genérico para os dados a inserir no nó criado
* Saída: OK se o nó foi inserido na lista e ERROR caso contrário
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
* Função listSize(): calcula o número de elementos da lista
*
* Parâmetros: L – lista
* Saída: número de elementos da lista
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
* Função printList(): apresenta no ecrã os elementos da lista
*
* Parâmetros: L – lista
* Saída: void
*
* Esta função não é genérica: só funciona para elemento de tipo ALUNO
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
* Função createNewNode(): cria um nó da lista
*
* Parâmetros: pData - apontador genérico para os dados a inserir no nó criado
* Saída: apontador para o nó criado ou NULL em caso de erro
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
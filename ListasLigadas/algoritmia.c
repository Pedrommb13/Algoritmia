//utilizar os #include necessários
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "locale.h"
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
	char nome[32];
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
STATUS newstation(LIST* lista);
void readstation(ESTACAO* pt);
void* searchstation(LIST lista, char* _nome);
float coststation(LIST lista, ESTACAO* pt1,ESTACAO* pt2);
STATUS deleteNode(LIST* plist, ESTACAO* estacao);

int main() {
	LIST lista = NULL;
	int selection = 0;
	char nome[32]="";
	ESTACAO *pt1=NULL, *pt2=NULL;
	readdata(&lista, "Linha1.txt");
	ESTACAO* pt = searchstation(lista, nome);
	float cost = 0;
	setlocale(LC_ALL, "Portuguese");
	do {
		printf("Estolha uma opcao:\n"); 
		printf("1-Mostrar estacoes\n");
		printf("2-Eliminar estacao\n");
		printf("3-Ler ficheiro\n");
		printf("4-Adicionar estacao manualmente\n");
		printf("5-Procurar estacao\n");
		printf("6-Ver custo viagem\n");
		printf("");
		printf("0-sair\n");
		scanf("%d",&selection);
		switch (selection) {
		case 1:
			printList(lista);
			break;
		case 2:
			do {
			//limpar stdin
			fgets(nome, 32, stdin);
			printf("Nome estacao a remover: ");
			fgets(nome, 32, stdin);
			int x = strcspn(nome, "\n");
			nome[x] = 0;
			pt = searchstation(lista, nome);
			if (!pt) printf("Estação não encontrada\n");
			} while (pt == NULL);
			deleteNode(&lista, pt);
			break;
		case 3:
			if (readdata(&lista, "Linha1.txt"))
				printList(lista);
			break;
		case 4:
			if (newstation(&lista))
				printList(lista);
			break;
		case 5:
			//limpar stdin
			fgets(nome, 32, stdin);
			printf("Nome estacao: ");
			fgets(nome, 32, stdin);
			int x = strcspn(nome, "\n");
			nome[x] = 0;
			pt = searchstation(lista, nome);
			printf("nome: %s\n", pt->nome);
			printf("custo: %f\n", pt->custo);
			printf("estado: %d\n", pt->estado);
			printf("ligacao: %d\n", pt->ligacao);
			break;
		case 6:
			//limpar stdin
			fgets(nome, 32, stdin);
			cost = 0;
			do {
				printf("Nome estação de entrada: ");
				fgets(nome, 32, stdin);
				int x = strcspn(nome, "\n");
				nome[x] = 0;
				pt = searchstation(lista, nome);
				if (!pt) printf("Estação não encontrada\n");
			} while (pt == NULL);
			pt1 = pt;
			do {
				printf("Nome estação de saida: ");
				fgets(nome, 32, stdin);
				int x = strcspn(nome, "\n");
				nome[x] = 0;
				pt = searchstation(lista, nome);
				if (!pt) printf("Estação não encontrada\n");
			} while (pt == NULL);
			pt2 = pt;
			if (cost = coststation(lista, pt1, pt2) > 0) printf("Custo: %f\n", cost);
			else printf("A estação de entrada tem que ser antes da estação saída\n");
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 0:
			break;
		}		
	} while (selection != 0);	
}

STATUS readdata(LIST* lista, char* file) {
	FILE* fp = NULL;
	ESTACAO* pt = NULL;
	if (fp = fopen(file, "r")) {
		{
			while (!feof(fp))
			{
				if ((pt = (ESTACAO*)malloc(sizeof(ESTACAO))) != NULL && (insertEndList(lista, pt)) == OK)	
					fscanf(fp, "%[^;];%f;%d;%d;\n",&(pt->nome),&(pt->custo), &(pt->estado),&(pt->ligacao));
			}
			return OK;
		}
		return ERROR;
	}
}

STATUS newstation(LIST* lista) {
	ESTACAO* pt = NULL;
	if ((pt = (ESTACAO*)malloc(sizeof(ESTACAO))) != NULL && (insertEndList(lista, pt)) == OK) {
		readstation(pt);
		return OK;
	}
	return FALSE;
}

void readstation(ESTACAO* pt) {
	printf("Nome estacao: ");
	scanf("%s", &pt->nome);
	printf("Custo: ");
	scanf("%f", &pt->custo);
	printf("Estado (1-TRUE 0-FALSE): ");
	scanf("%d", &pt->estado);
	printf("Ligacão (1-TRUE 0-FALSE): ");
	scanf("%d", &pt->ligacao);
}

void* searchstation(LIST lista,char* _nome) {
	while (lista != NULL) {
		if (strcmp(_nome,((ESTACAO*)lista->pData)->nome)==0)
			return lista->pData;
		lista = lista->next;
	}
	return NULL;
}

float coststation(LIST lista, ESTACAO* pt1, ESTACAO* pt2)
{
	float cost = 0;
	while (lista != NULL) {
		while (lista->pData != pt1) {
			if (lista->pData == pt2) return -1;
			lista=lista->next;
		}
		while (lista->pData != pt2) {
			cost += ((ESTACAO*)lista->pData)->custo;
			lista = lista->next;
		}
		return;
	}
	return cost;
}

STATUS deleteNode(LIST* plist, ESTACAO* estacao) {
	LIST_NODE* lista = *plist, *node=NULL;

	while (lista != NULL) {
		if (lista->pData != estacao) {
			while (lista->next->pData != estacao) {
				lista = lista->next;
			}
			node = lista->next;
			lista->next = lista->next->next;
		}
		else {
			node = lista;
			*plist = (*plist)->next;
		}
		
		
		//free memory
		free(node->pData);
		free(node);
		return OK;
	}
	return ERROR;
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
STATUS insertEndList(LIST * pL, void* pData)
{
	LIST_NODE* pNew, * pTemp;
	if ((pNew = createNewNode(pData)) == EMPTY)
		return ERROR;
	if (*pL == NULL)
		*pL = pNew;
	else
	{
		pTemp = *pL;
		while (NEXT(pTemp) != NULL)
			pTemp = NEXT(pTemp);
		NEXT(pTemp) = pNew;
	}
	return OK;
}
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
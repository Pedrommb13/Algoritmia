#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#define MAX 20 
typedef struct _VACINA
{ 
	char farma[MAX]; 
	int lote, quantidade;
	float custo; 
}VACINA; 
typedef struct _LIST_NODE 
{ 
	void * data; 
	struct _LIST_NODE * next;
}LIST_NODE; 
typedef LIST_NODE * LIST; 
#define DATA(node) ((node)->data) 
#define NEXT(node) ((node)->next) 

LIST_NODE* CreateNode(void* data) {
	LIST_NODE * node = (LIST_NODE *)malloc(sizeof(LIST_NODE)); 
	if (node) {
		DATA(node) = data; 
		NEXT(node) = NULL; 
	} 
	return node; 
}

VACINA* CreateVac(char* farma,int lote,int quantidade,float custo) {
	VACINA* v=NULL;
	v = (VACINA*)malloc(sizeof(VACINA));
	if (v != NULL) {
		strcpy(v->farma,farma);
		v->lote = lote;
		v->quantidade = quantidade;
		v->custo = custo;
		return v;
	}
	return NULL;
}

LIST_NODE* InsertIni(LIST* list,void* data) {
	LIST_NODE* node, * temp;
	if (node = CreateNode(data) == NULL)
		return NULL;
	node->next = *list;
	*list = node;
	return list;
}

LIST_NODE* InsertEnd(LIST* list, void* data) {
	LIST_NODE* node=NULL, * temp=NULL;
	node = CreateNode(data);
	if (node == NULL)
		return NULL;
	if (*list == NULL)
		*list = node;
	else {
		temp = *list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

int ReadList(LIST * lista) {
	FILE* f=NULL;
	VACINA* VAC=NULL;
	char farma[MAX];
	int lote=0, quantidade=0;
	float custo=0;
	if (f = fopen("dados.txt", "r")) {
		while (!feof(f)) {
			fscanf(f, "%[^;];%d;%d;%f\n", farma, &lote, &quantidade, &custo);
			VAC = CreateVac(farma, lote, quantidade, custo);
			if (VAC == NULL)
				return 0;
			else
				InsertEnd(lista, VAC);
		}
		fclose(f);
		return 1;
	}
	else 
		return 0;
}

int PrintList(LIST lista) {
	VACINA* vac=NULL;
	if (lista == NULL)
		return 0;
	while (lista->next != NULL) {
		vac = (VACINA*)(lista->data);
		printf("Vacina: %s;%d;%d;%f\n", vac->farma, vac->lote, vac->quantidade, vac->custo);
		lista = lista->next;
	}
}

int _PrintList(LIST lista) {
	VACINA* vac = NULL;
	float x = 0;
	while (lista!=NULL)
	{
		vac = (VACINA*)(lista->data);
		x= x + (vac->custo);
		lista = lista->next;
	}
	printf("Custo total: %f\n", x);
	return 1;
}

VACINA * CheckLote(LIST lista,int lote) {
	int i=0;
	VACINA* VAC =NULL;
	while (lista->next != NULL && i != lote) {
		lista = lista->next;
		i++;
	}
	if (i == lote) {
		VAC = (VACINA*)lista->data;
	    return VAC;
	}	
	else 
		return NULL;
}

int setvac0(LIST* lista,char* farma) {
	VACINA* vac = NULL;
	LIST_NODE* temp = *lista;
	while (temp!=NULL)
	{
		vac = (VACINA*)(temp->data);
		if (strcmp(vac->farma, farma) == 0) {
			vac->quantidade = 0;
		}
		temp=temp->next;
	}
}

int removefarma(LIST* lista, char* farma) {
	LIST temp = *lista, ptr = NULL;
	VACINA* vac = NULL;
	while (temp!=NULL)
	{
		vac = (VACINA*)(temp->data);
		if (strcmp(vac->farma, farma) == 0) 
		{
			if (temp == *lista) {
				*lista = (*lista)->next;
				free(temp->data);
				free(temp);
				temp = *lista;
			}
			else {
				ptr->next = temp->next;
				free(temp->data);
				free(temp);
				temp = ptr->next;
			}	
		}
		else {
			ptr = temp;
			temp = temp->next;
		}
	}
	return 1;
}

int main() { 
	LIST lista = NULL;
	VACINA * vac = NULL;
	char farma[MAX]="";
	int lote=0;
	if (ReadList(&lista)) {
		printf("Lista lida com sucesso\n");
	}
	else {
		printf("Erro ao ler a lista\n"); 
		return 0; 
	}

	PrintList(lista);
	scanf("%s", &farma);
	removefarma(&lista,farma);
	if (PrintList(lista)) {
		printf("Lista impressa com sucesso\n");
	}
	else {
		printf("Erro ao imprimir a lista\n");
		return 0;
	}
	return 1; 
}


//01 Faça a função ReadList() de forma a ler os dados de n registos a partir do ficheiro <dados.txt> 
// para uma lista adequada.Considere um registo por linha com todos os dados separados por “; ” e que 
// o número de registos é desconhecido.exemplo de um registo : Moderna; 14; 120; 0, 27 



//02 Desenvolva o código necessário para calcular e mostrar no ecrã o custo de um determinado 
// lote(número de vacinas desse lote × custo individual) cujo número deve ser lido através do teclado. 


//03 Desenvolva o código necessário para eliminar da lista todos os registos de uma determinada farmacêutica
// cujo nome deve ser lido através do teclado.
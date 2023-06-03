#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS; 
typedef struct _PERSON { 
	char name[50]; 
	int age; 
	BOOLEAN alive; 
}PERSON; 
typedef struct _BTREE_NODE { 
	void* data; 
	struct _BTREE_NODE* left; 
	struct _BTREE_NODE* right; 
} BTREE_NODE; 
#define DATA(node) ((node)->data) 
#define LEFT(node) ((node)->left) 
#define RIGHT(node) ((node)->right) 
typedef BTREE_NODE * BTREE; 
BTREE_NODE * NewBtreeNode(void* data);
void BtreeFree(BTREE btree);
BTREE_NODE * InitNode(void* ptr_data, BTREE_NODE * node1, BTREE_NODE * node2);
STATUS ReadFile(void** persons, char* file_name);
BTREE_NODE * CreateBtree(void** v, int i, int size);
int countalive(BTREE BT);
void changename(BTREE bt);
void printTree(BTREE bt);
void add2(BTREE bt, PERSON* p1, PERSON* p2);
int main(int argc, char* argv[]) {
	BTREE btree;
	PERSON* persons[15];
	char file_name[20];
	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(persons, file_name)) {
		btree = CreateBtree(persons, 0, 15);
		printf("pessoas vivas: %d", countalive(btree));
		//changename(btree);
		//printTree(btree);
		strcpy(persons[0]->name, "boda");
		strcpy(persons[0]->name, "bino");
		add2(btree,persons[0], persons[1]);
		printTree(btree);
		BtreeFree(btree);
	}
	else printf("ERRO na leitura do ficheiro\n"); 
	return 1;
}

BTREE_NODE * NewBtreeNode(void* data) { 
	BTREE_NODE * tmp_pt; if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
		DATA(tmp_pt) = data; LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL; 
	} 
	return tmp_pt; 
} 
void BtreeFree(BTREE btree) { 
	if (btree != NULL) { 
	BtreeFree(LEFT(btree));
	BtreeFree(RIGHT(btree)); 
	free(DATA(btree)); 
	free(btree); 
	} 
} 
BTREE_NODE * InitNode(void* ptr_data, BTREE_NODE * node1, BTREE_NODE * node2) {
	BTREE_NODE * tmp_pt = NULL; 
	tmp_pt = NewBtreeNode(ptr_data); 
	LEFT(tmp_pt) = node1; 
	RIGHT(tmp_pt) = node2; 
	return(tmp_pt); 
} 
STATUS ReadFile(void** persons, char* file_name) { 
	FILE * fp; 
	int aux, j, i = 0; 
	void* ptr_data; 
	if ((fp = fopen(file_name, "r")) != NULL) 
	{ 
		while (!feof(fp)) { 
			if ((ptr_data = malloc(sizeof(PERSON))) != NULL) { 
				fscanf(fp, "%[^;];%d;%d\n", ((PERSON*)ptr_data)->name, & ((PERSON*)ptr_data)->age, & aux);
				if (aux) ((PERSON*)ptr_data)->alive = TRUE; 
				else ((PERSON*)ptr_data)->alive = FALSE;
				persons[i] = ptr_data; i++; 
				printf("li: %s %d %d\n", ((PERSON*)ptr_data)->name, ((PERSON*)ptr_data)->age, ((PERSON*)ptr_data)->alive);
				
			} else { 
				for (j = i; j >= 0; j--) free(persons[j]); 
				return(ERROR); 
			} 
		} 
		fclose(fp); 
		return(OK); 
	} else return(ERROR); 
} 
BTREE_NODE * CreateBtree(void** v, int i, int size) { 
	if (i >= size) return(NULL); 
	else return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size))); 
}

// print tree in order
void printTree(BTREE bt) {
	if (bt == NULL) return;
	printTree(bt->left);
	printf("%s %d %d\n", ((PERSON*)bt->data)->name, ((PERSON*)bt->data)->age, ((PERSON*)bt->data)->alive);
	printTree(bt->right);
}

//ex1 contar todas as pessoas vivas
int countalive(BTREE BT) {
	if (BT == NULL)return 0;
	if (((PERSON*)BT->data)->alive == TRUE) return(1 + countalive(BT->left) + countalive(BT->right));
	else return(countalive(BT->left) + countalive(BT->right));
}
//ex2 mudar nome de uma pessoa
void changename(BTREE bt) {
	char name[50];
	printf("Nome da pessoa a mudar: ");
	scanf("%s", name);
	if (bt == NULL) return;
	else {
		if (strcmp(((PERSON*)bt->data)->name, name) == 0) {
			printf("Novo nome: ");
			scanf("%s", ((PERSON*)bt->data)->name);
		}
		else {
			changename(bt->left);
			changename(bt->right);
		}
	}
}
//3 adcionar 2 pessoas a arvore, na folha mais a esquerda e na folha mais a direita
void add2(BTREE bt, PERSON* p1, PERSON* p2) {
	if (bt == NULL) return;
	if (bt->left == NULL && bt->right == NULL) {
		bt->left = NewBtreeNode(p1);
		bt->right = NewBtreeNode(p2);
	}
	else {
		add2(bt->left, p1, p2);
		add2(bt->right, p1, p2);
	}
}
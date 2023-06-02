#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include <string.h>
typedef enum _STATUS {ERROR,OK} STATUS; 
typedef enum _BOOLEAN {FALSE,TRUE} BOOLEAN; 
#define MAX 20 
typedef struct _DIR{ 
	char desig[MAX];
	int tamanho,Kb; 
} DIR; 
typedef struct _BTREE_NODE { 
	void * data; 
	struct _BTREE_NODE * left; 
	struct _BTREE_NODE * right; 
} BTREE_NODE; 
typedef BTREE_NODE * BTREE; 
#define DATA(node) ((node)->data) 
#define LEFT(node) ((node)->left) 
#define RIGHT(node) ((node)->right) 
//---declaracao de funcoes----------
BOOLEAN emptyBTree(BTREE);
BTREE_NODE* CreateBtree(void** v, int i, int size);
BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2);
BTREE_NODE* NewBtreeNode(void* data);
DIR* NewDir(char* desig, int tamanho, int Kb);
BOOLEAN GenRandDir(void** Dirs);
void InOrder(BTREE btree);
void Ex1(BTREE btree);
int Ex2(BTREE btree);
int Ex3(BTREE btree,char* desig);
int main() { 
	BTREE btree = NULL; 
	DIR* dirs[MAX];
	if (GenRandDir(dirs) == FALSE) return -1;
	if (btree = CreateBtree(dirs, 0, MAX)) {
		printf("Arvore criada com sucesso\n");
		InOrder(btree);
		printf("Ex2 bits: %d\n",Ex2(btree));
		printf("bits totais: %d\n", Ex3(btree,""));
		printf("Ex3 bits: %d", Ex3(btree, "Dir19"));
		return 1;
	}else return -1;
}

BOOLEAN emptyBTree(BTREE btree) {
	return (btree == NULL); 
}

BTREE_NODE* CreateBtree(void** v, int i, int size){
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2) {
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	tmp_pt->left = node1;
	tmp_pt->right = node2;
	return(tmp_pt);
}

BTREE_NODE* NewBtreeNode(void* data){
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		tmp_pt->data = data;
		tmp_pt->left = tmp_pt->left = NULL;
	}
	return tmp_pt;
}

DIR* NewDir(char* desig, int tamanho, int Kb) {
	DIR* tmp_pt;
	if ((tmp_pt = (DIR*)malloc(sizeof(DIR))) != NULL)
	{
		strcpy(tmp_pt->desig, desig);
		tmp_pt->tamanho = tamanho;
		tmp_pt->Kb = Kb;
	}
	return tmp_pt;
}

BOOLEAN GenRandDir(void** Dirs) {
	int i;
	char desig[20];
	int tamanho, Kb;
	srand(time(NULL));
	for (i = 0; i < 20; i++) {
		sprintf(desig, "Dir%d", i);
		tamanho = rand() % 40;
		Kb = rand() % 1000000 * tamanho;
		Dirs[i] = NewDir(desig, tamanho, Kb);
		printf("%s: %d ficheiro(s), %d Kb(s)\n",((DIR*)Dirs[i])->desig, ((DIR*)Dirs[i])->tamanho, ((DIR*)Dirs[i])->Kb);
	}
	return TRUE;
}
//01 Faça uma função(ou mais) que liste no ecrã todos os dados das diretorias com mais de 20 ficheiros(tamanho > 20).
void InOrder(BTREE BT) {
	if(BT==NULL) return;
	InOrder(BT->left);
	Ex1(BT);
	InOrder(BT->right);
	return ;
}
void Ex1(BTREE BT) {
	if (((DIR*)DATA(BT))->tamanho > 20) printf("%s: %d ficheiro(s), %d Kb(s)\n", ((DIR*)DATA(BT))->desig, ((DIR*)DATA(BT))->tamanho, ((DIR*)DATA(BT))->Kb);
}
//02 Faça uma função(ou mais) que calcule, e devolva, o numero total de Kb(Kb) de todas as diretorias com mais de 10 ficheiros(tamanho > 10).
int Ex2(BTREE BT) {
	if (BT == NULL) return 0;
	if (((DIR*)DATA(BT))->tamanho < 10) return (0 + Ex2(BT->left) + Ex2(BT->right));
	return (((DIR*)BT->data)->Kb + Ex2(BT->left) + Ex2(BT->right));
}
//03 Faça uma função (ou mais) que calcule, e devolva, o total de Kb de uma diretoria (e todas as suas subdiretorias) cuja designação deve ser recebida como parâmetro.
int Ex3(BTREE BT, char* desig) {
	if(BT==NULL) return 0;
	if(strcmp(desig, ((DIR*)BT->data)->desig) == 0 || desig == "") return (((DIR*)BT->data)->Kb + Ex3(BT->left,"") + Ex3(BT->right,"")); // assumindo que o nome da diretoria nao pode ser vazio
	return (Ex3(BT->left, desig) + Ex3(BT->right, desig));
}
#include <stdlib.h> 
#include <stdio.h> 
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
int main() { 
	LIST lista = NULL; 
	if(ReadList(&lista)) { 
		 
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
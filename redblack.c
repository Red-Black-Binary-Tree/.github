#include <stdlib.h>
#include <stdio.h>
#include "redblack.h"

struct nodo *cria_nodo(struct nodo *no, int chave) {
	struct nodo *n = malloc(sizeof(struct nodo));
	n->chave = chave;
	n->esq = NULL;
	n->dir = NULL;
	//Se o nó que foi passado é NULL = Não tem pai:
	if (no == NULL)
		n->pai = NULL;
	//Se não for NULL = Juntar pai e filho:
	else {
		n->pai = no;
		if (no->chave > n->chave)
			no->esq = n;
		else if (no->chave < n->chave)
			no->dir = n;
	}
	return n;
}

struct nodo *inserir(struct nodo *anterior, struct nodo *no, int chave) {
	if (no == NULL)
		return cria_nodo(anterior, chave);
	if (no->chave > chave)
		return inserir(no, no->esq, chave);
	// AINDA NÃO DEFINI QUAL LADO VAI SE FOR IGUAL!!!
	if (no->chave < chave)
		return inserir(no, no->dir, chave);
	return NULL;
}

void print_tree(struct nodo *no) {
	if (no == NULL)
		return;
	print_tree(no->esq);
	printf("%.d ", no->chave);
	print_tree(no->dir);
}

int main() {
	int booleano_raiz = 1;
	struct nodo *raiz;
	while (1) {
		char escolha;
		int chave;
		scanf(" %c %d", &escolha, &chave);
		if (escolha != 'i')
			break;
		if (booleano_raiz) {
			raiz = cria_nodo(NULL, chave);
			booleano_raiz = 0;
		}
		else {
			inserir(NULL, raiz, chave);
		}
	}
	print_tree(raiz);
	printf("\n");
}

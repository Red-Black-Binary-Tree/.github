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
	struct nodo *raiz = cria_nodo(NULL, 10);
	inserir(NULL, raiz, 7);
	inserir(NULL, raiz, 11);
	inserir(NULL, raiz, 6);
	inserir(NULL, raiz, 8);
	print_tree(raiz);
	printf("\n");
}

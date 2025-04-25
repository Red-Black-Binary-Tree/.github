#include <stdlib.h>
#include <stdio.h>
#include "redblack.h"

int main() {
	initNIL();
	struct arvore *t;
	t = malloc(sizeof(struct arvore));
	t->raiz = NIL;
	char escolha;
	int chave;
	while (scanf(" %c %d", &escolha, &chave) == 2) {
		if (escolha == 'i'){
			struct nodo *z = cria_nodo(NIL, chave);
			rb_insert(t, z);
			nivelacao(t->raiz, 0);
		}
		else if(escolha == 'r'){
			struct nodo *z = acha(t->raiz, chave);
			if (z != NIL) {
				rb_delete(t, z);
				nivelacao(t->raiz, 0);
			} else {
				printf("Nó %d não encontrado para remoção!\n", chave);
			}
		}
	}
	print_tree(t->raiz);
}

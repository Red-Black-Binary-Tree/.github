#include <stdlib.h>
#include <stdio.h>
#include "redblack.h"

int main() {
	initNIL();
	struct arvore *t;
	t = malloc(sizeof(struct arvore));
	t->raiz = NIL;
	while (1) {
		char escolha;
		int chave;
		scanf(" %c %d", &escolha, &chave);
		if (escolha == 'i'){
			struct nodo *z = cria_nodo(NIL, chave);
			rb_insert(t, z);
			nivelacao(t->raiz, 0);
			//printf("\nVisual (pra baixo):\n");
			//print_arvore_vertical(t->raiz);
			//printf("\n");
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
		else{
			break;
		}
	}
	nivelacao(t->raiz, 0);
	printf("\n");
	print_tree(t->raiz);
	printf("\n");
	//printf("\nVisual (pra baixo):\n");
	//print_arvore_vertical(t->raiz);
	//printf("\n");
	//conferir se raiz->esq != NULL (se for, não tem antecessor).
	struct nodo *antecessor_raiz = antecessor(t->raiz->esq);
	//conferir se raiz->dir != NULL (se for, não tem sucessor).
	struct nodo *sucessor_raiz = sucessor(t->raiz->dir);
	if (antecessor_raiz != NIL){-
		printf("antecessor da raiz: %d\n", antecessor_raiz->chave);
	}
	else{-
		printf("antecessor da raiz: NULO\n");
	}
	if (sucessor_raiz != NIL){
		printf("sucessor da raiz: %d\n", sucessor_raiz->chave);
	}
	else{
		printf("sucessor da raiz: NULO\n");
	}
}

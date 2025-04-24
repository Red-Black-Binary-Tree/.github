#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "redblack.h"

#define ESPACO 5  
#define MAX_LINHAS 100
#define MAX_COLUNAS 255
#define PRETO 0
#define VERMELHO 1

struct nodo *NIL;

//----------------------------------------------------------------------------------------------//
//Área de criação de nodo.
void initNIL() {
    NIL = malloc(sizeof(struct nodo));
    NIL->cor = PRETO;
    NIL->esq = NIL;
    NIL->dir = NIL;
    NIL->pai = NIL;
}

struct nodo *cria_nodo(struct nodo *pai, int chave) {
    struct nodo *n = malloc(sizeof(struct nodo));
    n->chave = chave;
    n->esq = NIL;
    n->dir = NIL;
    n->nivel = 0;

    if (pai == NIL) {
        n->pai = NIL;
        n->cor = PRETO;
    } else {
        n->cor = VERMELHO;
        n->pai = pai;
        if (pai->chave > n->chave)
            pai->esq = n;
        else if (pai->chave < n->chave)
            pai->dir = n;
    }
    return n;
}

//----------------------------------------------------------------------------------------------//
//Área destinada a achar o antecessor e sucessor.
struct nodo *antecessor(struct nodo *no_esquerdo) {
    if (no_esquerdo == NIL)
        return NIL;
    if (no_esquerdo->dir != NIL)
        return antecessor(no_esquerdo->dir);
    return no_esquerdo;
}

struct nodo *sucessor(struct nodo *no_direito) {
    if (no_direito == NIL)
        return NIL;
    if (no_direito->esq != NIL)
        return sucessor(no_direito->esq);
    return no_direito;
}

struct nodo *tree_minimum(struct nodo *x){
    while(x->esq != NIL){
        x = x->esq;
    }
    return x;
}

struct nodo *tree_maximum(struct nodo *x){
    while(x->dir != NIL){
        x = x->dir;
    }
    return x;
}

//----------------------------------------------------------------------------------------------//
//Área destinada às rotações.
void rotacao_esquerda(struct arvore *t, struct nodo *x){
    struct nodo *y = x->dir;
    x->dir = y->esq;
    if(y->esq != NIL){
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == NIL){
        t->raiz = y;
    }
    else if (x == x->pai->esq){
        x->pai->esq = y;
    }
    else{
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
}

void rotacao_direita(struct arvore *t, struct nodo *y){
    struct nodo *x = y->esq;
    y->esq = x->dir;
    if(x->dir != NIL){
        x->dir->pai = y;
    }
    x->pai = y->pai;
    if(y->pai == NIL){
        t->raiz = x;
    }
    else if(y == y->pai->esq){
        y->pai->esq = x;
    }
    else{
        y->pai->dir = x;
    }
    x->dir = y;
    y->pai = x;
}

//----------------------------------------------------------------------------------------------//
//Área destinada a inserção.
void confere_rb(struct arvore *t, struct nodo *z) {
    while (z->pai != NIL && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            struct nodo *y = z->pai->pai->dir;
            int cor_y = (y != NIL) ? y->cor : PRETO;

            if (cor_y == VERMELHO) {  
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;  
            } else {  
                if (z == z->pai->dir) {  
                    z = z->pai;
                    rotacao_esquerda(t, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_direita(t, z->pai->pai);
            }
        } else {  
            struct nodo *y = z->pai->pai->esq;
            int cor_y = (y != NIL) ? y->cor : PRETO;

            if (cor_y == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacao_direita(t, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_esquerda(t, z->pai->pai);
            }
        }
    }
    t->raiz->cor = PRETO;  
}

void rb_insert(struct arvore *t, struct nodo *z) {
    struct nodo *y = NIL;
    struct nodo *x = t->raiz;
    while (x != NIL) {
        y = x;
        if (z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;
    if (y == NIL)
        t->raiz = z;
    else if (z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;

    z->esq = NIL;
    z->dir = NIL;
    z->cor = VERMELHO;
    
    if (z != t->raiz)
        confere_rb(t, z);
    else
        z->cor = PRETO;
}

//----------------------------------------------------------------------------------------------//
//Área destinada a remoção

struct nodo *acha(struct nodo *n, int procurado) {
    if (n == NIL) {
        return NIL;
    }
    if (n->chave == procurado) {
        return n;
    }

    struct nodo *resultado = acha(n->esq, procurado);
    if (resultado != NIL) {
        return resultado;
    }

    return acha(n->dir, procurado);
}

void rb_transplante(struct arvore *t, struct nodo *u, struct nodo *v){
    if(u->pai == NIL){
        t->raiz = v;
    }
    else if(u == u->pai->esq){
        u->pai->esq = v;
    }
    else{
        u->pai->dir = v;
    }
    v->pai = u->pai;
}

void rb_delete_fixup(struct arvore *t, struct nodo *x){
    struct nodo *w;
    while (x != t->raiz && x->cor == PRETO) {
        if (x == x->pai->esq) {
            w = x->pai->dir;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacao_esquerda(t, x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->dir->cor == PRETO) {
                    w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacao_direita(t, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->dir->cor = PRETO;
                rotacao_esquerda(t, x->pai);
                x = t->raiz;
            }
        } else {
            w = x->pai->esq;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacao_direita(t, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->esq->cor == PRETO) {
                    w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacao_esquerda(t, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esq->cor = PRETO;
                rotacao_direita(t, x->pai);
                x = t->raiz;
            }
        }
    }
    x->cor = PRETO;
}

void rb_delete(struct arvore *t, struct nodo *z){
    struct nodo *x;
    struct nodo *y = z;
    int yCorOriginal = y->cor;

    if(z->esq == NIL){
        x = z->dir;
        rb_transplante(t,z,z->dir);
    }
    else if(z->dir == NIL){
        x = z->esq;
        rb_transplante(t,z,z->esq);
    }
    else{ 
        y = tree_maximum(z->esq);
        yCorOriginal = y->cor;
        x = y->esq;
        if(y->pai == z){
                x->pai = y;
        }
        else{
            rb_transplante(t,y,y->esq);
            y->esq = z->esq;
            y->esq->pai = y;
        }

        rb_transplante(t,z,y);
        y->dir = z->dir;
        y->dir->pai = y;
        y->cor = z->cor;
    }
    if(yCorOriginal == PRETO){
        rb_delete_fixup(t,x);
    }
}

//----------------------------------------------------------------------------------------------//
//Área destinada a nivelação.
void nivelacao(struct nodo *no, int nivel) {
    if (no == NIL)
        return;

    no->nivel = nivel;

    nivelacao(no->esq, nivel + 1);
    nivelacao(no->dir, nivel + 1);
}

//----------------------------------------------------------------------------------------------//
// Área destinada ao print.
void print_tree(struct nodo *no) {
    if (no == NIL)
        return;
    print_tree(no->esq);
    printf("(%d, %d, %d)\n", no->chave, no->nivel, no->cor);
    print_tree(no->dir);
}

int altura(struct nodo *raiz) {
	if (raiz == NIL) return 0;
	int h_esq = altura(raiz->esq);
	int h_dir = altura(raiz->dir);
	return (h_esq > h_dir ? h_esq : h_dir) + 1;
}

void preenche_matriz(char tela[MAX_LINHAS][MAX_COLUNAS], struct nodo *raiz, int linha, int col, int espaco) {
	if (raiz == NIL) return;

	char buffer[30];
	sprintf(buffer, "(%d %d %d)", raiz->chave, raiz->nivel, raiz->cor);
	int len = strlen(buffer);

	for (int i = 0; i < len; i++)
		tela[linha][col + i] = buffer[i];

	if (raiz->esq != NIL) {
		tela[linha + 1][col - 1] = '/';
		preenche_matriz(tela, raiz->esq, linha + 2, col - espaco, espaco / 2);
	}
	if (raiz->dir != NIL) {
		tela[linha + 1][col + len] = '\\';
		preenche_matriz(tela, raiz->dir, linha + 2, col + espaco, espaco / 2);
	}
}


void print_arvore_vertical(struct nodo *raiz) {
	char tela[MAX_LINHAS][MAX_COLUNAS];
	for (int i = 0; i < MAX_LINHAS; i++)
		for (int j = 0; j < MAX_COLUNAS; j++)
			tela[i][j] = ' ';

	int h = altura(raiz);
	int largura = 64;  
	preenche_matriz(tela, raiz, 0, largura / 2, largura / 4);

	for (int i = 0; i < h * 2; i++) {
		tela[i][MAX_COLUNAS - 1] = '\0';
		printf("%s\n", tela[i]);
	}
}
//----------------------------------------------------------------------------------------------//

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
			printf("\nVisual (pra baixo):\n");
			print_arvore_vertical(t->raiz);
			printf("\n");
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
	printf("\nVisual (pra baixo):\n");
	print_arvore_vertical(t->raiz);
	printf("\n");
	//conferir se raiz->esq != NULL (se for, não tem antecessor).
	struct nodo *antecessor_raiz = antecessor(t->raiz->esq);
	//conferir se raiz->dir != NULL (se for, não tem sucessor).
	struct nodo *sucessor_raiz = sucessor(t->raiz->dir);
	if (antecessor_raiz != NIL){ 
		printf("antecessor da raiz: %d\n", antecessor_raiz->chave);
	}
	else{ 
		printf("antecessor da raiz: NULO\n");
	}
	if (sucessor_raiz != NIL){
		printf("sucessor da raiz: %d\n", sucessor_raiz->chave);
	}
	
	else{
		printf("sucessor da raiz: NULO\n");
	}
}

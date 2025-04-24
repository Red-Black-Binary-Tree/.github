#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "redblack.h"
#define ESPACO 5  
#define MAX_LINHAS 100
#define MAX_COLUNAS 255

//----------------------------------------------------------------------------------------------//
//Área de criação de nodo.
struct nodo *cria_nodo(struct nodo *pai, int chave) {
	struct nodo *n = malloc(sizeof(struct nodo));
	n->chave = chave;
	n->esq = NULL;
	n->dir = NULL;
	n->nivel = 0;
	//Se o nó que foi passado é NULL = Não tem pai, ou seja, "n" é a raiz:
	if (pai == NULL) {
		n->pai = NULL;
		n->cor = 0;
	}
	//Se não for NULL = Juntar pai e filho:
	else {
		n->cor = 1;
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
	//se ele não tiver nó à esquerda, ele não tem antecessor.
	if (no_esquerdo == NULL)
		return NULL;
	else {
		if (no_esquerdo->dir != NULL)
			return antecessor(no_esquerdo->dir);
		else
			return no_esquerdo;
	}
}

struct nodo *sucessor(struct nodo *no_direito) {
	//se ele não tiver nó à direita, ele não tem sucessor.
	if (no_direito == NULL)
		return NULL;
	else {
		if (no_direito->esq != NULL)
			return sucessor(no_direito->esq);
		else
			return no_direito;
	}
}

struct nodo *tree_minimum(struct nodo *x){
	while(x->esq != NULL){
		x = x->esq;
	}
	return x;
}

struct nodo *tree_maximum(struct nodo *x){
	while(x->dir != NULL){
		x = x->dir;
	}
	return x;
}
//----------------------------------------------------------------------------------------------//
//Área destinada às rotações.
void rotacao_esquerda(struct arvore *t, struct nodo *x){
	struct nodo *y = x->dir;
	x->dir = y->esq;
	if(y->esq != NULL){
		y->esq->pai = x;
	}
	y->pai = x->pai;
	if(x->pai == NULL){
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
	if(x->dir != NULL){
		x->dir->pai = y;
	}
	x->pai = y->pai;
	if(y->pai == NULL){
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
	while (z->pai != NULL && z->pai->cor == 1) {
		//se o pai de z é o filho da esquerda do avô de z.
		if (z->pai == z->pai->pai->esq) {
			struct nodo *y = z->pai->pai->dir;
			//Há um problema: se ele não tiver tio.
			//Por isso, cria-se essa nova variável.
			// Se ele não tiver tio, não acessa o NULL e não dá segmentation fault.
			int cor_y;
			if (y != NULL)
				cor_y = y->cor;
			else
			 	cor_y = 0;
			if (cor_y == 1) {
				z->pai->cor = 0;
				y->cor = 0;
				z->pai->pai->cor = 1;
				z = z->pai->pai;
			}
			else {
				//se z é o filho da direita.
				if (z == z->pai->dir) {
					z = z->pai;
					rotacao_esquerda(t, z);
				}
				z->pai->cor = 0;
				z->pai->pai->cor = 1;
				rotacao_direita(t, z->pai->pai);
			}
		}
		//se o pai de z é o filho da direita do avô de z.
		else {
			struct nodo *y = z->pai->pai->esq;
			int cor_y;
			if (y != NULL)
				cor_y = y->cor;
			else
			 	cor_y = 0;

			if (cor_y == 1) {
				z->pai->cor = 0;
				y->cor = 0;
				z->pai->pai->cor = 1;
				z = z->pai->pai;
			}
			else {
				if (z == z->pai->esq) {
					z = z->pai;
					rotacao_direita(t, z);
				}
				z->pai->cor = 0;
				z->pai->pai->cor = 1;
				rotacao_esquerda(t, z->pai->pai);
			}
		}
	}
	t->raiz->cor = 0;
}

void rb_insert(struct arvore *t, struct nodo *z ) {
	struct nodo *y = NULL;
	struct nodo *x = t->raiz;
	while (x != NULL) {
		y = x;
		if (z->chave < x->chave)
			x = x->esq;
		else
			x = x->dir;
	}
	z->pai = y;
	if (y == NULL)
		t->raiz = z;
	else if (z->chave < y->chave)
		y->esq = z;
	else
		y->dir = z;
	//chamar o cria_nodo() depois...
	z->esq = NULL;
	z->dir = NULL;
	z->cor = 1;
	if (z != t->raiz)
		confere_rb(t, z);
	else
		z->cor = 0;
}
//----------------------------------------------------------------------------------------------//
//Área destinada a remoção

void rb_transplante(struct arvore *t, struct nodo *u, struct nodo *v){
	if(u->pai == NULL){
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
	while(x != t->raiz && x->cor == 0){
		if(x == x->pai->esq){
			w = x->pai->dir;
		}
		if(w->cor == 1){
			w->cor = 0;
			x->pai->cor = 1;
			rotacao_esquerda(t,x->pai);
			w = x->pai->dir;
		}
		if(w->esq->cor == 0 && w->dir->cor == 0){
			w->cor = 1;
			x = x->pai;
		}
		else if(w->dir->cor == 0){
			w->esq->cor = 0;
			w->cor = 1;
			rotacao_direita(t,w);
			w = x->pai->dir;
		}
	}
}




void rb_delete(struct arvore *t, struct nodo *z){
	struct nodo *x;
	struct nodo *y = z;
	int yCorOriginal = y->cor;
	if(z->esq == NULL){
		x = z->dir;
		rb_transplante(t,z,z->dir);
	}
	else if(z->dir == NULL){
		x = z->esq;
		rb_transplante(t,z,z->esq);
	}
	else{ 
		y = tree_minimum(z->dir);
		yCorOriginal = y->cor;
		x = y->dir;
		if(y->pai == z){
			x->pai = y;
		}
		else{
			rb_transplante(t,y,y->dir);
			y->dir = z->dir;
			y->dir->pai = y;
		}
		rb_transplante(t,z,y);
		y->esq = z->esq;
		y->esq->pai = y;
		y->cor = z->cor;
	}
	if(yCorOriginal == 0){
		rb_delete_fixup(t,x);
	}
}






//----------------------------------------------------------------------------------------------//
//Área destinada a nivelação.
void nivelacao(struct nodo *no, int nivel) {
	if (no == NULL)
		return;

	no->nivel = nivel;

	nivelacao(no->esq, nivel+1);
	nivelacao(no->dir, nivel+1);
}
//----------------------------------------------------------------------------------------------//
// Área destinada ao print.
void print_tree(struct nodo *no) {
	if (no == NULL)
		return;
	print_tree(no->esq);
	printf("(%.d, %d, %d)\n", no->chave, no->nivel, no->cor);
	print_tree(no->dir);
}

int altura(struct nodo *raiz) {
	if (raiz == NULL) return 0;
	int h_esq = altura(raiz->esq);
	int h_dir = altura(raiz->dir);
	return (h_esq > h_dir ? h_esq : h_dir) + 1;
}

void preenche_matriz(char tela[MAX_LINHAS][MAX_COLUNAS], struct nodo *raiz, int linha, int col, int espaco) {
	if (raiz == NULL) return;

	char buffer[30];
	sprintf(buffer, "(%d %d %d)", raiz->chave, raiz->nivel, raiz->cor);
	int len = strlen(buffer);

	for (int i = 0; i < len; i++)
		tela[linha][col + i] = buffer[i];

	if (raiz->esq != NULL) {
		tela[linha + 1][col - 1] = '/';
		preenche_matriz(tela, raiz->esq, linha + 2, col - espaco, espaco / 2);
	}
	if (raiz->dir != NULL) {
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
	//int booleano_raiz = 1;
	struct arvore *t;
	t = malloc(sizeof(struct arvore));
	while (1) {
		char escolha;
		int chave;
		scanf("%c %d", &escolha, &chave);
		struct nodo *z = malloc(sizeof(struct nodo));
		z->chave = chave;
		if (escolha == 'i'){
			rb_insert(t, z);
		}
		else if(escolha == 'r'){
			rb_delete(t,z);
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
	if (antecessor_raiz != NULL){ 
		printf("antecessor da raiz: %d\n", antecessor_raiz->chave);
	}
	else{ 
		printf("antecessor da raiz: NULO\n");
	}
	if (sucessor_raiz != NULL){
		printf("sucessor da raiz: %d\n", sucessor_raiz->chave);
	}
	
	else{
		printf("sucessor da raiz: NULO\n");
	}
}


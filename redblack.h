#ifndef __REDBLACK__
#define __REDBLACK__

struct nodo {
	int chave;
	struct nodo *esq;
	struct nodo *dir;
	struct nodo *pai;
	//(0 == preto e 1 == vermelho)
	int cor;
	int nivel;
};

struct arvore{
	struct nodo *raiz;
};

extern struct nodo *NIL;
void initNIL();
struct nodo *cria_nodo(struct nodo *pai, int chave);
struct nodo *antecessor(struct nodo *no_esquerdo);
struct nodo *sucessor(struct nodo *no_direito);
struct nodo *tree_minimum(struct nodo *x);
struct nodo *tree_maximum(struct nodo *x);
void rotacao_esquerda(struct arvore *t, struct nodo *x);
void rotacao_direita(struct arvore *t, struct nodo *y);
void confere_rb(struct arvore *t, struct nodo *z);
void rb_insert(struct arvore *t, struct nodo *z);
struct nodo *acha(struct nodo *n, int procurado);
void rb_transplante(struct arvore *t, struct nodo *u, struct nodo *v);
void rb_delete_fixup(struct arvore *t, struct nodo *x);
void rb_delete(struct arvore *t, struct nodo *z);
void nivelacao(struct nodo *no, int nivel);
void print_tree(struct nodo *no);

#endif

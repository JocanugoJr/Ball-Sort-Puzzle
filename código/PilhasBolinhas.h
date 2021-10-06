#ifndef PILHASBOLINHAS_H_INCLUDED
#define PILHASBOLINHAS_H_INCLUDED

typedef struct elemento Elemento;
{
	int info;
	struct elemento *prox;
}Elemento;

/*estrutura da pilha (cabeçalho) */
typedef struct pilha Pilha;
{
	Elemento *prim; // aponta para o topo
	int Max;
	int qtd;
}Pilha;

Pilha* pilha_cria ();
int pilha_vazia (Pilha* p);
void pilha_push (Pilha* p, int v);
int pilha_pop (Pilha* p);
void pilha_libera (Pilha* p);
void inicia_pilha(Pilha* p, int limite);
Pilha** cria_pt_pt(int tamanho, int limite);
void libera_pt_pt(Pilha** p, int tamanho);

#endif // PILHASBOLINHAS_H_INCLUDED

#include "PilhasBolinhas.h"
#include <stdio.h>
#include <stdlib.h>

/**ALÉM DAS FUNÇÕES DE PILHA* TEM FUNÇÕES PILHA** */

struct elemento
{
	int info;
	struct elemento *prox;
};

/*estrutura da pilha (cabeçalho) */
struct pilha
{
	Elemento *prim; // aponta para o topo
	int Max;
	int qtd;
};

Pilha* pilha_cria ()
{
	Pilha *p = (Pilha*) malloc(sizeof(Pilha));
	p->prim = NULL;
	return p;
}

int pilha_vazia (Pilha* p)
{
	if(p->prim == NULL)
	{
		return 1;
	}

	return 0;
}

void pilha_push (Pilha* p, int v)
{
	Elemento *novo;
	novo = (Elemento*) malloc(sizeof(Elemento));
	novo->info = v;
	novo->prox = p->prim;
	p->prim = novo;
}

int pilha_pop (Pilha* p)
{
	Elemento *t;
	int v;

	if (pilha_vazia(p)){
		return 0; //não indica erro;
	}

	t = p->prim;
	v = t->info;
	p->prim = t->prox;
	free(t);
	return v;
}

void pilha_libera (Pilha* p)
{
	Elemento *t, *q = p->prim;

	while (q!=NULL)
	{
		t = q->prox;
		free(q);
		q = t;
	}

	free(p);
}

void inicia_pilha(Pilha* p, int limite)
{
	p->Max=limite;
	p->qtd=0;
}

Pilha** cria_pt_pt(int tamanho, int limite)
{
	int i;
	Pilha** p = (Pilha**)malloc((tamanho)*sizeof(Pilha*));
	for(i=0;i<tamanho;i++)
	{
		if((p+i)==NULL)
		{
			exit(1);
		}
	}
	for(i=0;i<tamanho;i++)
	{
		p[i] = pilha_cria();
		if(p[i]==NULL)
		{
			exit(1);
		}
		inicia_pilha(p[i], limite);
	}
	return p;
}

void libera_pt_pt(Pilha** p, int tamanho)
{
	int i;
	for(i=0;i<tamanho;i++)
	{
		pilha_libera(p[i]);
	}

	free(p);
}

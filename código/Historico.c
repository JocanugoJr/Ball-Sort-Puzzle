#include "PilhasBolinhas.h"
#include "Historico.h"
#include <stdio.h>
#include <stdlib.h>

#define TUBOS_VAZIOS 2

//um tipo só para armazenar o historico(pilha)
HistoryH* cria_historico()
{
	HistoryH *hist = (HistoryH*) malloc(sizeof(HistoryH));
	hist->prim = NULL;
	hist->quant=0;
	return hist;
}
//pilha_push para os dois campos do nó da pilha Historico
void historico_insere(HistoryH* hist, int passos, int qtd)
{
	Pontuacao *novo;
	novo = (Pontuacao*) malloc(sizeof(Pontuacao));
	novo->passos = passos;
	novo->n=qtd;
	novo->prox = hist->prim;
	hist->prim = novo;
	hist->quant++;
}

//função para exibir o histórico
void exibe_historico(HistoryH* hist)
{
    int i=0, qtd=hist->quant;
    Pontuacao* p = hist->prim;
    printf("   __________________________________\n");
    printf("  | RODADAS | PASSOS | CORES | TUBOS |");
	while(p!=NULL)
	{
		printf("\n  |    %d    ", qtd-i);
		printf("|   %d   ", p->passos);
		if(p->passos<10)//quantidade de PASSOS
        {
            printf(" ");//caso o número mostrado por p->passos tiver 2 dígitos ou mais, não devo imprimir o espaço vazio, pois iria tirar a formatação da exibição
        }
        printf("|");

		printf("   %d  ", p->n);
		if(p->n<10)//quantidade de CORES
        {
            printf(" ");//caso o número mostrado por p->n tiver 2 dígitos ou mais, não devo imprimir o espaço vazio, pois iria tirar a formatação da exibição
        }
        printf("|");

        printf("   %d  ", p->n+TUBOS_VAZIOS);
        if(p->n+TUBOS_VAZIOS<10)//quantidade de TUBOS
        {
            printf(" ");//caso o número mostrado por p->n tiver 2 dígitos ou mais, não devo imprimir o espaço vazio, pois iria tirar a formatação da exibição
        }
        printf("|");

		p=p->prox;
		i++;
	}
    printf("\n   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
}

//libera histórico
void historico_libera (HistoryH* p)
{
    Pontuacao *t, *q = p->prim;
    while (q!=NULL)
    {
        t = q->prox;
        free(q);
        q = t;
    }
    free(p);
}

#include "PilhasBolinhas.h"
#include "GameplayBolinhas.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 4
#define TUBOS_VAZIOS 2

//TAD de Pilhas de bolas e de Sortear
int conta_cor_geral(Pilha** p, int bola, int tamanho)//conta as int bolas da mesma cor e retorna a quantidade para verifica_cor_geral
{
	Elemento* o;
	int contador=0;//só conta os adicionais
	int i;

	for(i=0;i<tamanho+TUBOS_VAZIOS;i++)
	{
		o= p[i]->prim;

		while(o!=NULL)
		{
			if(bola==o->info)//fazer uma outra função para impedir que se faça mais de MAXIMO-1 inserção de bolas da mesma cor num mesmo tubo
			{
				contador++;
			}
			o=o->prox;
		}
	}

	return contador;
}

//Essa função é para encotrar um tubo válido para ser inserido
int procura_espaco(Pilha** p, int tamanho, int bola)//procura um tubo com espaço vazio para fazer a inserção e retorna a sua posição no vetor de pilhas
{
	int i;

	for(i=0; i<tamanho;i++)
	{
		if(p[i]->prim != NULL)//se estiver com algum elemento no tubo, verifica se comporta mais uma bola da cor especificada
		{
			if(p[i]->qtd<p[i]->Max)
			{
				if(verifica_cor_tubo(p[i],bola))
				{
					return i;
				}
			}
		}
		else//se o tubo estiver vazio, evita a verificação no tubo
		{
			return i;
		}
	}

	return -1;
}

int verifica_cor_tubo(Pilha* p, int bola)/*vê quais cores tem dentro do tubo e retorna 0 caso a bola que for inserida seja
                                            MAXIMO bola no tubo, ou seja, impede de ter mais de 3 bolas iguais no mesmo tubo
                                            comparando a bola que vai entrar com as bolas que já estão no tubo; o somatório
                                            delas tem que ser menor ou igual à MAXIMO-1.*/
{
	Elemento* o = p->prim;
	int contador=1;//contador está em 1 para simulara entrada da bola de uma cor e somar com aquelas que estão no tubo. Caso a soma seja maior que MAXIMO - 1, então não insere.
	while(o!=NULL)
	{
		if(bola==o->info)//fazer uma outra função para impedir que se faça mais de MAXIMO-1 inserção de bolas da mesma cor num mesmo tubo
		{
			contador++;
		}

		if(contador>MAXIMO-1)
		{
			return 0;
		}

		o=o->prox;
	}
	return 1;
}

int verifica_cor_geral(Pilha** p, int n, int bola)//verifica se excedeu o máximo de bolas da mesma cor proposto para o exercício
{
	int cont=1;//cont tá 1 pq já está fazendo a contabilização do int bola;

	cont+=conta_cor_geral(p,bola, n);//conta quantas bolas da mesma cor tem em todos os tubos.
	if(cont>MAXIMO)
	{
		return 1;
	}

	return 0;
}

void sorte(Pilha** p, int n)/**Busca sortear com a função rand() os valores das pilhas e insere eles no primeiro espaço vazio
                                com a função procura_espaco(), além de impedir a inserção de mais de 4 números iguais dentro de
                                todos os tubos com a função verifica_cor_geral().*/
{
	int bola, i;
	int j;

	//sorteio
	srand(time(NULL));

	for(i=0;i<n*MAXIMO;i++)/*FAZER PELA QUANTIDADE DE BOLAS QUE PRECISAM SER INSERIDAS. NO CASO, 4xN.*/
	{
		do{
			bola=rand()%n+1;
		/*	scanf("%d", &bola);
			fflush(stdin);*/
			j = procura_espaco(p,n,bola);//ela procura a posição vazia que o número que chegar primeiro pode ocupar.
		}while(verifica_cor_geral(p,n,bola) || j==-1);//ele crasha pq a posição pilha[-1] não existe

		//inserção
		pilha_push(p[j],bola);
		p[j]->qtd++;
	}
}

//função de  mover as bolinhas
int move_bolinhas(Pilha** p, int x, int y, int tamanho)/**procura movimentar o conteúdo das pilhas com um pop e um push.
                                                            Além disso, retorna 1 para caso a movimentação tenha ocorrido
                                                            e 0 para caso a movimentação seja inválida.*/
{
	int auxValor;

	//funções de verificação para o tamanho máximo e depois se as cores das bolas->prim são iguais
	if(p[y]->qtd<p[y]->Max)
	{
		//if(p[y]->prim != NULL)
		if(pilha_vazia (p[y]))//se ela for vazia, faça:
		{
			auxValor = pilha_pop(p[x]);
			pilha_push(p[y], auxValor);
			p[x]->qtd--;
			p[y]->qtd++;

			return 1;
		}
		else//se tiver algum elemento, faca:
		{
		    if((p[x]->prim->info == p[y]->prim->info))
			{
				auxValor = pilha_pop(p[x]);
				pilha_push(p[y], auxValor);
				p[x]->qtd--;
				p[y]->qtd++;

				return 1;
			}
		}
	}
    printf("Movimentação inválida!\n");//setlocale
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "PilhasBolinhas.h"
#include "Historico.h"
#include "GameplayBolinhas.h"

#define MAXIMO 4
#define TUBOS_VAZIOS 2

void colorir(int cor)//utiliza da biblioteca windows.h para gerar as cores desejadas
{
	//a cor 1 é muito escura por isso não quis usar
	if(cor==1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	}
	else if(cor==8)//dá pra confundir fácil com o 7, por isso decidi mudar a sua cor
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	}
	else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
    }
}

//fazer com uma matriz, para armazenar os infos dessa pilha e poder printar em ordem
void imprint(Pilha** p, int tamanho)
{
	int mat[MAXIMO][tamanho];
	int cont=1, i, j;
	Elemento* o;

    for(j=0;j<tamanho;j++)
    {
        i=0;
        cont= p[j]->Max-p[j]->qtd;
        //adiciono a quantidade de espaços vazios o número 0;
        while(cont>0)
        {
            mat[i][j] = 0;
            i++;	//o problema é que o i zera quando sai do loop
            cont--;
        }

        o=p[j]->prim;
        while(o!=NULL)
        {
            mat[i][j] = o->info;
            o=o->prox;
            i++;
        }
    }

	for(i=0;i<MAXIMO;i++)
	{
		for(j=0;j<tamanho;j++)
		{
			printf("| ");
			colorir(mat[i][j]);
			printf("%d", mat[i][j]);
			colorir(7);
			if(mat[i][j]<10)//para não desformatar quando tiver um número de 2 dígitos
			{
				printf(" ");
			}
			printf("|\t");
		}
		printf("\n");
	}

	cont=0;
    while(cont<2)
    {
       for(j=0;j<tamanho;j++)
        {
            if(cont==0)
            {
                printf(" ¯¯¯ \t");//aqui que faço a base, mas a visualização depende se o setlocale vai funcionar ou não
            }
            else
            {
                printf("  %d  \t", j);//aqui que faço a base, mas a visualização depende se o setlocale vai funcionar ou não
            }
        }
        printf("\n");
        cont++;
    }


	printf("\n");
}

//função gameplay(conta os passos, além de retorná-los, e é a responsável por controlar toda a parte de gameplay do jogo.
int gameplay(Pilha** p, int tamanho)//tamanho == n+TUBOS_VAZIOS
{
	int passos=0;
	int x, y;

	while(1)
	{
		printf("De qual tubo para qual tubo?Ex.: Tirar do tubo '0'  e enviar para o tubo '1', insira: 0 1\nInsira -1 para sair.\n");
		scanf("%d", &x);

		if(x!=-1)
		{
			scanf("%d", &y);
			fflush(stdin);

			if((x>=0 && y>=0)&&(x<tamanho && y<tamanho) && (p[x]->prim!=NULL))
			{
				if(move_bolinhas(p, x, y, tamanho))//só adiciona passos, se for verdadeira a condição de movimentação
				{
				    passos++;
				}
				printf("\n");
				imprint	(p, tamanho);
			}
			else
			{
				printf("\nComando inválido!\n");//setlocale
			}
		}
		else
		{
			break;
		}
	}

	return passos;
}

int menu(HistoryH* hist)
{
    int option;
    do
    {
        printf("\nDigite '1' para continuar jogando ou '2' para ver o histórico ou '3' para sair.\n");
        scanf("%d", &option);
        fflush(stdin);
        switch(option)
        {
            case 1:
                colorir(3);
                printf("\nReiniciando...\n\n\n"); //só para mostrar que houve um reinício no jogo.
                colorir(7);
                break;
            case 2:
                //exibir o histórico
                exibe_historico(hist);
                break;
            case 3:
                colorir(3);
                printf("\nSaindo...\n\n");
                colorir(7);
                break;
            default:
                colorir(12);
                printf("Comando incompreendido!\n");
                colorir(7);
                break;
        }
    }while(option==2 || option>3 || option<1);

    return option;
}

int main(int argc, char *argv[]) {
	int n, option, passos;

	//armazena a quantidade de passos que o usuário jogou, além do n(cores e tubos) escolhidos naquela rodada.
	HistoryH* hist = cria_historico();

	setlocale(LC_ALL,"Portuguese");

    //o loop pro jogo ficar infinito começa aqui
	do//loop para reiniciar o jogo
	{

		do//loop para limitar a inserção de cores e tubos oferecida ao cliente.
		{
			printf("Digite quantas cores deseja começar:(Mínimo: 6 | Máximo: 12)\n");
			scanf("%d", &n);
			fflush(stdin);

			if(n>5 && n<13)
			{
				break;
			}
			else
			{
			    colorir(12);
				printf("O valor não respeita o intervalo informado!\n");
				colorir(7);
			}
		}while(1);//determinação do cliente


        Pilha** p = cria_pt_pt(n+TUBOS_VAZIOS, MAXIMO);

        /**O objetivo dela é sortear as primeiras bolas com até 4 bolas da mesma cor
        e distribuí-las para cada tubo,*/
        sorte(p,n);

        printf("\n");
        imprint	(p, n+TUBOS_VAZIOS);

        //para mover as bolinhas será necessário entrar num loop de gameplay ou função gameplay(com funcionalidades de ser infinita enquanto o usuário quiser e de fazer as movimentações da bola).
        passos=gameplay(p,n+TUBOS_VAZIOS);
        //imprimir se fez alguma movimentação ou não
        colorir(14);//só para que as mensagens terem o impacto devido.
        if(passos==0)
        {
            printf("\nRodada terminada com nenhum passo.\n");
        }
        else
        {
            printf("\nRodada se concluiu com %d passo(s).\n", passos);
        }
        colorir(7);//volta pra branco
        //libera a pilha quando termina a rodada, ou seja, quando o usuário cansar.
        libera_pt_pt(p, n+TUBOS_VAZIOS);

		//histórico entra em ação
		historico_insere(hist, passos, n);

		//re-jogar?
		option = menu(hist);

	}while(option==1);

	//desaloca histórico
	historico_libera(hist);

	return 0;
}
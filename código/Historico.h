#ifndef HISTORICO_H_INCLUDED
#define HISTORICO_H_INCLUDED

//struct pontuação
typedef struct _pontuacao
{
	int passos;
	int n;//que por determinação as cores e os tubos tem a mesma quantidade
	struct _pontuacao *prox;
}Pontuacao;
//struct histórico
typedef struct _historyh
{
	Pontuacao* prim;
	int quant;
}HistoryH;

HistoryH* cria_historico();
void historico_insere(HistoryH* hist, int passos, int qtd);
void exibe_historico(HistoryH* hist);
void historico_libera (HistoryH* p);


#endif // HISTORICO_H_INCLUDED

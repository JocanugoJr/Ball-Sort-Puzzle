#ifndef GAMEPLAYBOLINHAS_H_INCLUDED
#define GAMEPLAYBOLINHAS_H_INCLUDED

int conta_cor_geral(Pilha** p, int bola, int tamanho);
int procura_espaco(Pilha** p, int tamanho, int bola);
int verifica_cor_tubo(Pilha* p, int bola);
int verifica_cor_geral(Pilha** p, int n, int bola);
void sorte(Pilha** p, int n);
int move_bolinhas(Pilha** p, int x, int y, int tamanho);
//int gameplay(Pilha** p, int tamanho);

#endif // GAMEPLAYBOLINHAS_H_INCLUDED

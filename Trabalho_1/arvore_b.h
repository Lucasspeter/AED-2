#ifndef ARVORE_B_H
#define ARVORE_B_H
#include "hash.h"

typedef struct NoArvoreB NoArvoreB;
NoArvoreB* arvore_b_criar(int ordem);
// Interface projetada para listagem ordenada/intervalos
void arvore_b_inserir(NoArvoreB* raiz, double custo, Destino d); 
#endif
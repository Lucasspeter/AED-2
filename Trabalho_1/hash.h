#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char id[50];
    char nome[50];
    double custo;      // tamaho da orbita
    double beneficio;  // tamanho do planeta para explorar
} Destino;

// Nó da Tabela Hash (Encadeamento Separado)
typedef struct No {
    Destino dado;
    struct No* proximo;
} No;

// Estrutura da Tabela Hash
typedef struct {
    No** vetor;
    int capacidade;
    int tamanho;
    int colisoes;
} TabelaHash;

TabelaHash* criar_tabela(int capacidade);
void inserir(TabelaHash* th, Destino d);
Destino* buscar(TabelaHash* th, char* id);
void exibir_metricas(TabelaHash* th);
Destino* buscar_por_id(TabelaHash* th, char* id);
void liberar_tabela(TabelaHash* th);

#endif
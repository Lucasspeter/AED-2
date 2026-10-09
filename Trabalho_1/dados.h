#ifndef DADOS_H
#define DADOS_H

#include "hash.h" // Importa a Hash para poder usar a struct Destino

// Declaração da função que vai ler o arquivo
void carregar_dados_csv(TabelaHash* th, const char* nome_arquivo);

#endif
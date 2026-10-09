#ifndef CONSULTAS_H
#define CONSULTAS_H
#include "hash.h"

//Pesquisa (por atributo relevante: Nome)
Destino* pesquisar_por_nome(TabelaHash* th, char* nome);

//Listagem e filtragem (ex: beneficio >= X)
void listar_filtrados(TabelaHash* th, double min_beneficio);

//Operações adicionais (Relatório de Extremos de Custo)
void relatorio_extremos(TabelaHash* th);

#endif
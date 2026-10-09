#ifndef CONSULTAS_H
#define CONSULTAS_H
#include "hash.h"

// 6.2 Pesquisa (por atributo relevante: Nome)
Destino* pesquisar_por_nome(TabelaHash* th, char* nome);

// 6.3 Listagem e filtragem (ex: Potencial Científico mínimo)
void listar_filtrados(TabelaHash* th, double min_beneficio);

// 6.4 Operações adicionais (Relatório de Extremos de Custo)
void relatorio_extremos(TabelaHash* th);

#endif
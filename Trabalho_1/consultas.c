#include <stdio.h>
#include <string.h>
#include "consultas.h"

// 6.2 Pesquisa (Percorre a tabela buscando pelo atributo 'nome')
Destino* pesquisar_por_nome(TabelaHash* th, char* nome) {
    for (int i = 0; i < th->capacidade; i++) {
        No* atual = th->vetor[i];
        while (atual != NULL) {
            if (strcmp(atual->dado.nome, nome) == 0) {
                return &(atual->dado); // Encontrou
            }
            atual = atual->proximo;
        }
    }
    return NULL;
}

// 6.3 Listagem e filtragem (Gera listagem baseada em um critério)
void listar_filtrados(TabelaHash* th, double min_beneficio) {
    printf("\n--- Filtragem: Destinos com Beneficio >= %.2f ---\n", min_beneficio);
    int encontrou = 0;
    
    for (int i = 0; i < th->capacidade; i++) {
        No* atual = th->vetor[i];
        while (atual != NULL) {
            if (atual->dado.beneficio >= min_beneficio) {
                printf("- %s (ID: %s | Beneficio: %.2f | Custo: %.2f)\n", 
                       atual->dado.nome, atual->dado.id, atual->dado.beneficio, atual->dado.custo);
                encontrou = 1;
            }
            atual = atual->proximo;
        }
    }
    if (!encontrou) printf("Nenhum destino atende ao criterio.\n");
}

// 6.4 Operacao Adicional (Justificativa: Missões espaciais precisam 
// saber imediatamente o corpo celeste mais acessível e o mais custoso)
void relatorio_extremos(TabelaHash* th) {
    Destino* mais_barato = NULL;
    Destino* mais_caro = NULL;

    for (int i = 0; i < th->capacidade; i++) {
        No* atual = th->vetor[i];
        while (atual != NULL) {
            if (mais_barato == NULL || atual->dado.custo < mais_barato->custo) {
                mais_barato = &(atual->dado);
            }
            if (mais_caro == NULL || atual->dado.custo > mais_caro->custo) {
                mais_caro = &(atual->dado);
            }
            atual = atual->proximo;
        }
    }

    printf("\n--- Relatorio de Extremos da Galaxia ---\n");
    if (mais_barato) 
        printf("Destino Mais Acessivel: %s (Custo: %.2f)\n", mais_barato->nome, mais_barato->custo);
    if (mais_caro) 
        printf("Destino Mais Custoso: %s (Custo: %.2f)\n", mais_caro->nome, mais_caro->custo);
}
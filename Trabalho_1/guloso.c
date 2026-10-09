#include <stdio.h>
#include <stdlib.h>
#include "guloso.h"

// Estrutura auxiliar exigida pelo qsort
typedef struct {
    Destino d;
    double razao;
} Candidato;

// Função de comparação (Ordem Decrescente)
int comparar_candidatos(const void *a, const void *b) {
    Candidato *c1 = (Candidato *)a;
    Candidato *c2 = (Candidato *)b;
    if (c1->razao < c2->razao) return 1;
    if (c1->razao > c2->razao) return -1;
    return 0;
}

void executar_algoritmo_guloso(TabelaHash* th, double orcamento_maximo) {
    if (th->tamanho == 0) return;

    // 1. Aloca um vetor temporário com o tamanho exato de elementos da Hash
    Candidato* candidatos = (Candidato*) malloc(th->tamanho * sizeof(Candidato));
    int idx = 0;

    // 2. Varre a Tabela Hash e copia os dados para o vetor calculando a Razão (Guloso)
    for (int i = 0; i < th->capacidade; i++) {
        No* atual = th->vetor[i];
        while (atual != NULL) {
            candidatos[idx].d = atual->dado;
            candidatos[idx].razao = atual->dado.beneficio / atual->dado.custo; // Benefício por Custo
            idx++;
            atual = atual->proximo;
        }
    }

    // 3. Ordena o vetor usando qsort (Otimização Logística)
    qsort(candidatos, th->tamanho, sizeof(Candidato), comparar_candidatos);

    // 4. Seleção iterativa (Estratégia Gulosa)
    double custo_atual = 0.0;
    double beneficio_total = 0.0;
    
    printf("\n--- Planejamento de Missao (Algoritmo Guloso) ---\n");
    printf("Orcamento Maximo: %.2f\n", orcamento_maximo);
    
    for (int i = 0; i < th->tamanho; i++) {
        if (custo_atual + candidatos[i].d.custo <= orcamento_maximo) {
            printf(" -> Visitando: %s (Custo: %.2f | Beneficio: %.2f | Razao: %.6f)\n", 
                   candidatos[i].d.nome, candidatos[i].d.custo, candidatos[i].d.beneficio, candidatos[i].razao);
            
            custo_atual += candidatos[i].d.custo;
            beneficio_total += candidatos[i].d.beneficio;
        }
    }
    printf("--------------------------------------------------\n");
    printf("Custo Final Consumido: %.2f\n", custo_atual);
    printf("Beneficio Total Obtido: %.2f\n", beneficio_total);

    // 5. Libera a memória do vetor temporário
    free(candidatos);
}
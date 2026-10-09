#include <stdio.h>
#include "hash.h"
#include "dados.h"
#include "consultas.h"
#include "guloso.h" // Incluiu o guloso

int main() {
    printf("Iniciando Sistema de Gerenciamento Espacial...\n\n");

    // 1. Inicializa a Estrutura
    TabelaHash* minha_tabela = criar_tabela(50);

    // 2. Módulo de Aquisição (Carrega do arquivo CSV)
    carregar_dados_csv(minha_tabela, "corposCelestes.csv");

    // 3. Instrumentação Obrigatória
    exibir_metricas(minha_tabela);

    // 4. Testes de Funcionalidades (Requisitos 6.1 a 6.4)
    Destino* d1 = buscar_por_id(minha_tabela, "mars");
    if(d1) printf("\nBusca ID 'mars': Encontrado %s\n", d1->nome);
    
    listar_filtrados(minha_tabela, 2000.0);
    relatorio_extremos(minha_tabela);

    // 5. Algoritmo Guloso (Opção A)
    // Definimos um orçamento fictício de 1500 (ex: litros de combustível)
    executar_algoritmo_guloso(minha_tabela, 395000.00);

    // 6. Encerramento e Limpeza de Memória
    liberar_tabela(minha_tabela);
    printf("\nSistema encerrado. Memoria liberada com sucesso.\n");

    return 0;
}
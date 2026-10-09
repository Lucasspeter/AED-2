#include <stdio.h>
#include "hash.h"
#include "dados.h"
#include "consultas.h"
#include "guloso.h" // Incluiu o guloso

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



int main() {





    printf("Iniciando Sistema de Gerenciamento Espacial...\n\n");

    
    TabelaHash* minha_tabela = criar_tabela(50);

    
    carregar_dados_csv(minha_tabela, "corposCelestes.csv");

    
    exibir_metricas(minha_tabela);

    
    char id[50];
    printf("\nDigite o id do destino para buscar: ");
    scanf("%49s", id);

    Destino* d_id = buscar_por_id(minha_tabela, id);
    if (d_id != NULL) {
        printf("-> Encontrado: %s (ID: %s) | Custo: %.2f | Beneficio: %.2f\n", 
           d_id->nome, d_id->id, d_id->custo, d_id->beneficio);
    } else {
        printf("-> Destino '%s' nao foi encontrado.\n", id);
    }

    char nome_busca[50];
    printf("\nDigite o nome do destino para buscar: ");
    scanf("%49s", nome_busca);

    Destino* d_nome = pesquisar_por_nome(minha_tabela, nome_busca);
    if (d_nome != NULL) {
        printf("-> Encontrado: %s (ID: %s) | Custo: %.2f | Beneficio: %.2f\n", 
           d_nome->nome, d_nome->id, d_nome->custo, d_nome->beneficio);
    } else {
        printf("-> Destino '%s' nao foi encontrado.\n", nome_busca);
    }
    
    float beneficio_minimo;
    printf("\nDigite o beneficio minimo para filtragem: ");
    if (scanf("%f", &beneficio_minimo) == 1) {
        printf("\n--- Destinos com Beneficio >= %.2f ---\n", beneficio_minimo);
    listar_filtrados(minha_tabela, beneficio_minimo);
    } else {
        printf("Valor invalido digitado.\n");
        limpar_buffer();
    }
    
    relatorio_extremos(minha_tabela);

    
    
    double orcamento_missao;
    printf("\nDigite o Orcamento Maximo para a Missao: ");
    if (scanf("%lf", &orcamento_missao) == 1) {
        executar_algoritmo_guloso(minha_tabela, orcamento_missao);
    } else {
        printf("Valor de orcamento invalido.\n");
        limpar_buffer();
    }

    
    liberar_tabela(minha_tabela);
    printf("\nSistema encerrado. Memoria liberada com sucesso.\n");

    return 0;
}
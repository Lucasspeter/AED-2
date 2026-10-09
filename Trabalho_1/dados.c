#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

void carregar_dados_csv(TabelaHash* th, const char* corposCelestes) {
    FILE *arquivo = fopen(corposCelestes, "r");
    
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo %s!\n", corposCelestes);
        return; // Sai da função se der erro
    }

    char linha[256];
    
    // Pula a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    // Lê cada linha até o final do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        
        linha[strcspn(linha, "\n")] = 0; // Remove o "Enter" do final

        // Quebra a linha usando a vírgula como separador
        char *id = strtok(linha, ",");
        char *nome = strtok(NULL, ",");
        char *distancia_str = strtok(NULL, ",");
        char *potencial_str = strtok(NULL, ",");

        // Verifica se todas as colunas foram lidas corretamente para evitar falhas (Segmentation Fault)
        if (id != NULL && nome != NULL && distancia_str != NULL && potencial_str != NULL) {
            
            // 1. Cria a variável do tipo Destino
            Destino novo_destino;
            
            // 2. Copia os textos para dentro da struct
            strcpy(novo_destino.id, id);
            strcpy(novo_destino.nome, nome);
            novo_destino.custo = atof(distancia_str);
            novo_destino.beneficio = atof(potencial_str);

            // 3. Insere na Tabela Hash (Usando a função que estaria no seu hash.c)
            inserir(th, novo_destino); 
        }
    }

    fclose(arquivo);
    printf("Dados do arquivo %s carregados com sucesso na Tabela Hash!\n", corposCelestes);
}
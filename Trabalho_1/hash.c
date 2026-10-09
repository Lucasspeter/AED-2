#include "hash.h"

// Função Hash de string (djb2)
unsigned long hash_string(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

TabelaHash* criar_tabela(int capacidade) {
    TabelaHash* th = (TabelaHash*) malloc(sizeof(TabelaHash));
    th->capacidade = capacidade;
    th->tamanho = 0;
    th->colisoes = 0;
    th->vetor = (No**) calloc(capacidade, sizeof(No*));
    return th;
}

void inserir(TabelaHash* th, Destino d) {
    int indice = hash_string((unsigned char*)d.id) % th->capacidade;
    
    No* novo = (No*) malloc(sizeof(No));
    novo->dado = d;
    novo->proximo = NULL;

    // Se já existe elemento na posição, registra colisão
    if (th->vetor[indice] != NULL) {
        th->colisoes++; 
        novo->proximo = th->vetor[indice]; // Insere no início da lista
    }
    
    th->vetor[indice] = novo;
    th->tamanho++;
}

// Imprime as métricas instrumentadas exigidas
void exibir_metricas(TabelaHash* th) {
    double fator_carga = (double)th->tamanho / th->capacidade;
    printf("--- Metricas da Tabela Hash ---\n");
    printf("Total de Colisoes: %d\n", th->colisoes);
    printf("Fator de Carga Atual: %.2f\n", fator_carga);
}

// 6.1 Consulta de elementos (Busca direta na Tabela Hash por ID)
Destino* buscar_por_id(TabelaHash* th, char* id) {
    // 1. Calcula o mesmo índice usado na inserção
    int indice = hash_string((unsigned char*)id) % th->capacidade;
    
    // 2. Vai direto na posição do vetor
    No* atual = th->vetor[indice];
    
    // 3. Percorre a lista encadeada (caso tenha havido colisão)
    while (atual != NULL) {
        if (strcmp(atual->dado.id, id) == 0) {
            return &(atual->dado); // Retorna o endereço de memória do destino encontrado
        }
        atual = atual->proximo;
    }
    return NULL; // Se não encontrou, retorna nulo
}

// Libera toda a memoria alocada para evitar Memory Leaks
void liberar_tabela(TabelaHash* th) {
    for (int i = 0; i < th->capacidade; i++) {
        No* atual = th->vetor[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp); // Libera cada nó da lista encadeada
        }
    }
    free(th->vetor); // Libera o array de ponteiros
    free(th);        // Libera a estrutura principal
}
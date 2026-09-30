#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALFABETO_TAM 26


typedef struct trie_nodo_t {
    struct trie_nodo_t *filhos[ALFABETO_TAM];
    bool fim_de_palavra;
} trie_nodo_t;


trie_nodo_t* criar_nodo(void) {
    trie_nodo_t *p_nodo = (trie_nodo_t *)malloc(sizeof(trie_nodo_t));
    if (p_nodo) {
        p_nodo->fim_de_palavra = false;
        for (int i = 0; i < ALFABETO_TAM; i++) {
            p_nodo->filhos[i] = NULL;
        }
    }
    return p_nodo;
}


void inserir(trie_nodo_t *raiz, const char *palavra) {
    trie_nodo_t *atual = raiz;
    int tamanho = strlen(palavra);

    for (int nivel = 0; nivel < tamanho; nivel++) {
        int index = palavra[nivel] - 'a'; 
        if (atual->filhos[index] == NULL) {
            atual->filhos[index] = criar_nodo();
        }
        atual = atual->filhos[index];
    }
    atual->fim_de_palavra = true;
}

// Exercicio 1:

bool buscar_palavra(trie_nodo_t *raiz, const char *palavra) {
    trie_nodo_t *atual = raiz;
    int tamanho = strlen(palavra);

    for (int nivel = 0; nivel < tamanho; nivel++) {
        int index = palavra[nivel] - 'a';
        if (atual->filhos[index] == NULL) {
            return false; 
        }
        atual = atual->filhos[index];
    }

    
    return (atual != NULL && atual->fim_de_palavra);
}


// Exercicio 2: 

void coletar_palavras_rec(trie_nodo_t *nodo, char *prefixo_atual, int profundidade, char **palavras, int *qtd_palavras) {
    if (nodo == NULL) return;

    
    if (nodo->fim_de_palavra) {
        prefixo_atual[profundidade] = '\0'; 
        
        
        palavras[*qtd_palavras] = (char *)malloc((strlen(prefixo_atual) + 1) * sizeof(char));
        strcpy(palavras[*qtd_palavras], prefixo_atual);
        
        (*qtd_palavras)++;
    }

    
    for (int i = 0; i < ALFABETO_TAM; i++) {
        if (nodo->filhos[i] != NULL) {
            
            prefixo_atual[profundidade] = 'a' + i;
            
            
            coletar_palavras_rec(nodo->filhos[i], prefixo_atual, profundidade + 1, palavras, qtd_palavras);
        }
    }
}


void trie_busca_prefixo(trie_nodo_t *raiz, char *prefixo, char **palavras) {
    trie_nodo_t *atual = raiz;
    int tamanho_prefixo = strlen(prefixo);

    
    for (int i = 0; i < tamanho_prefixo; i++) {
        int index = prefixo[i] - 'a';
        if (atual->filhos[index] == NULL) {
            
            return;
        }
        atual = atual->filhos[index];
    }

    
    char buffer[100]; 
    strcpy(buffer, prefixo); 

    int qtd_palavras = 0; 

    
    coletar_palavras_rec(atual, buffer, tamanho_prefixo, palavras, &qtd_palavras);
    
    
    palavras[qtd_palavras] = NULL;
}


// testando:

int main() {
    trie_nodo_t *raiz = criar_nodo(); 

    
    inserir(raiz, "casa");
    inserir(raiz, "casarao");
    inserir(raiz, "castelo");
    inserir(raiz, "carro");
    inserir(raiz, "porta");

    
    char *palavras_encontradas[100];

    printf("Buscando palavras com prefixo 'cas':\n");
    trie_busca_prefixo(raiz, "cas", palavras_encontradas);

    
    for (int i = 0; palavras_encontradas[i] != NULL; i++) {
        printf("- %s\n", palavras_encontradas[i]);
        free(palavras_encontradas[i]); 
    }

    return 0;
}
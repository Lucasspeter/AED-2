#ifndef TRIE_H
#define TRIE_H
#include "hash.h" // Para reutilizar a struct Destino

typedef struct NoTrie NoTrie;
NoTrie* trie_criar();
void trie_inserir(NoTrie* raiz, const char* palavra, Destino d);
// Interface projetada para pesquisa de atributos relevantes (Ex: autocompletar nomes)
Destino* trie_buscar_prefixo(NoTrie* raiz, const char* prefixo);

#endif
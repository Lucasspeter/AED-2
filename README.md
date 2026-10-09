#  Crônicas do Espaço: Planejamento Algorítmico de Missões

**Autor:** Lucas Simoes Peter  
**Instituição:** Universidade Federal de Pelotas (UFPel) - Ciência da Computação  
**Disciplina:** Estruturas de Dados Avançadas  

Este repositório contém a Parte 1 do trabalho de desenvolvimento de um Sistema de Gerenciamento e Planejamento de Missões Espaciais, implementado em linguagem C. O sistema consome dados de uma API pública, estrutura as informações utilizando uma Tabela Hash e resolve um problema de otimização logística através de um algoritmo guloso.

---

##  1. Fonte de Dados

*   **API Escolhida:** The Solar System OpenData API.
*   **Justificativa da Escolha:** A API disponibiliza uma vasta quantidade de informações estruturadas em JSON sobre planetas, luas e asteroides do Sistema Solar. Os atributos físicos e orbitais fornecidos (como raio e distância) são ideais para fundamentar as métricas de "Custo" e "Benefício" exigidas pelo algoritmo de triagem de missões.
###  Endpoints Utilizados

* `GET /rest/bodies/` - Dados estruturados de planetas, luas, asteroides e corpos celestes.




*  Como o projeto adotou a estratégia de **Consumo Estático (Nível 2)**, a requisição foi feita previamente de forma externa para obter os registros brutos em formato JSON e convertê-los para leitura local pela aplicação em C:

```bash
# Exemplo de requisição via cURL no terminal
curl -X GET "[https://api.le-systeme-solaire.net/rest/bodies/](https://api.le-systeme-solaire.net/rest/bodies/)" -o planetas.json
*   **Estrutura dos Dados Obtidos:** A API retorna um JSON estruturado. Para a aplicação, foram filtrados e mapeados apenas os campos essenciais para a logística: `id` (identificador único), `englishName` (nome de exibição), `semimajorAxis` (distância orbital) e `meanRadius` (raio médio).
```
---

##  2. Modelagem

*   **Representação dos Elementos:** Os corpos celestes foram modelados no sistema através da estrutura genérica `Destino`, projetada para encapsular os atributos necessários de forma independente da API.
*   **Atributos Utilizados:**
    *   `id`: Chave primária alfanumérica utilizada para o cálculo da função Hash.
    *   `nome`: Nome descritivo do destino.
    *   `custo`: Mapeado a partir da distância orbital (`semimajorAxis`), representando o gasto logístico, de tempo e de combustível da agência espacial.
    *   `beneficio`: Mapeado a partir do tamanho do corpo celeste (`meanRadius`), representando a área potencial disponível para exploração científica.
*   **Decisões de Projeto:** O sistema foi estritamente modularizado em arquivos `.h` (interfaces genéricas) e `.c` (implementações). A lógica interna da estrutura de dados foi encapsulada, garantindo que o módulo principal e as consultas acessem os dados sem depender dos detalhes de alocação de memória e tratamento de colisões.
*   **Operações Implementadas:** 
    *   Carregamento e parsing de dados via `.csv`.
    *   Busca direta de elemento por ID.
    *   Pesquisa sequencial por atributo secundário (Nome).
    *   Filtragem por critério de benefício mínimo.
    *   Relatório operacional de extremos logísticos (Maior/Menor custo).

---

##  3. Estrutura de Dados

*   **Estrutura Escolhida:** Tabela Hash com tratamento de colisões por Encadeamento Separado (Listas Encadeadas).
*   **Justificativa da Escolha:** A Tabela Hash foi selecionada devido à sua eficiência $O(1)$ para a operação principal de qualquer sistema de gerenciamento: a busca direta e o carregamento de informações a partir de um identificador único. A implementação direta em C prioriza o gerenciamento explícito de memória através de ponteiros.
*   **Implementação e Instrumentação:** A estrutura foi codificada integralmente na aplicação. O núcleo da Tabela Hash foi instrumentado, injetando métricas para rastrear e imprimir em tempo real o **número exato de colisões** e o **fator de carga (load factor)** durante o processo de ingestão do catálogo de missões.
*   **Análise da Complexidade das Operações:**
    *   **Inserção / Busca por ID:** Média $O(1)$, Pior Caso $O(n)$ (colisão de todas as chaves no mesmo índice).
    *   **Pesquisa por Nome / Filtragem:** $O(n)$ (exige varredura sequencial nos vetores e listas, pois não é a chave indexada primária).

---

##  4. Análise de Complexidade Amortizada

A métrica tradicional de pior caso O(n) para a inserção em uma Tabela Hash descreve o cenário em que a tabela atinge o seu limite de fator de carga e exige o redimensionamento dinâmico (**Re-hashing**), forçando a expansão do vetor e a realocação de todos os elementos contidos. Avaliar a estrutura estritamente por esse gargalo isolado apresenta um cenário demasiadamente conservador.

> **Justificativa via Método Contábil (*Accounting Method*):**
> Pela aplicação do método contábil, demonstra-se que o custo médio de uma sucessão prolongada de operações permanece constante $O(1)$. Atribui-se um custo artificial fixo (ex: $3$ unidades computacionais) para cada inserção padrão que custa, na realidade, apenas $1$ unidade. A unidade base financia a inserção atual no espaço vazio, enquanto as $2$ unidades excedentes são armazenadas como "crédito amortizado" vinculado àquele elemento. Quando a estrutura engatilha o redimensionamento pesado $O(n)$, a operação de realocação não gera déficit, pois o custo linear exigido já foi integralmente pré-pago pelos créditos acumulados por cada elemento inserido em tempo $O(1)$. Portanto, o custo amortizado por operação é constante.

---

##  5. Planejamento de Missão (Algoritmo Guloso)

*   **Definição do Problema(Opção A):** A agência espacial possui uma quantidade fixa de recursos (orçamento/combustível) para investir em missões exploratórias. O sistema atua como um filtro logístico inteligente para selecionar o conjunto de destinos celestes que maximize o retorno global da exploração sem extrapolar o teto orçamentário.
*  **Estratégia Adotada e Critério de Escolha:** O algoritmo recebe um limite de recursos(ex: combustivel). Apos isso, algoritmo classifica os destinos calculando a proporção matemática de eficiência: Razão = Benefício/Custo = Raio Médio/Distância Orbital. 

### Essas métricas foram escolhidas pelos seguintes motivos logísticos e científicos:
* **Raio Médio (`meanRadius` - Benefício):** Quanto maior o corpo celeste, maior é a sua área de superfície disponível para exploração científica e maior a probabilidade de encontrar recursos minerais e geológicos de alto valor para a agência.
* **Distância Orbital (`semimajorAxis` - Custo):** Representa o raio médio da órbita. Quanto maior essa distância, maior é o percurso necessário, exigindo maior tempo de trânsito espacial, maior consumo de combustível/propulsão e elevando a complexidade e o custo logístico da missão.
*    O conjunto de dados extraído da Tabela Hash é ordenado de forma decrescente por este fator logístico. A seleção avança de maneira estritamente iterativa, preenchendo a missão com os destinos mais rentáveis e descartando os que excedem a capacidade restante do recurso.
*   **Limitações da Estratégia Gulosa:** O critério de escolha adota o paradigma iterativo de otimização local ("Greedy Choice"). O algoritmo acopla o melhor item disponível no momento sem avaliar as permutações futuras do orçamento.
    *   **Cenário de Falha:** Sendo um problema caracterizado como *Mochila 0/1 Discreta* (corpos celestes não podem ser explorados fracionadamente), o algoritmo falha em encontrar a solução ótima global caso o orçamento residual (após uma escolha hiper-eficiente, porém barata, como um asteroide próximo) seja insuficiente para bancar o próximo item massivo da fila. O sistema pulará o alvo primário de alto rendimento (ex: Júpiter ou Lua) e lotará o espaço logístico remanescente com "poeira espacial" de baixo custo, desperdiçando o teto de recursos com uma combinação subótima final que poderia ser evitada por um algoritmo de Programação Dinâmica.

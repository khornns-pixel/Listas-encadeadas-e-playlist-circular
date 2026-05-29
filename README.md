# Atividade Avaliativa 2 — Estruturas de Dados em C

Trabalho prático sobre manipulação de Listas Encadeadas Simples e Playlist Circular Duplamente Encadeada desenvolvido para a disciplina de Estrutura de Dados.

Integrantes do Grupo:
- Ketely Hornns Duarte Vicente - RA: 25251461-2
- Gabriel Cesar Marteloti da Luz - RA: 25068651-2
- Arthur Pacher dos Santos - RA: 25185872-2

Explicação da Solução Implementada:

Para cumprir as restrições do projeto (não utilizar vetores auxiliares, não usar variáveis globais e gerenciar a memória manualmente), a solução foi baseada estritamente na manipulação avançada de ponteiros. Abaixo está a explicação técnica de como cada parte foi resolvida:

Parte 1: Inserção em Posição Específica (`inserirPosicao`)
A lógica consiste em percorrer a lista utilizando um ponteiro auxiliar (`atual`) e um contador até chegar à posição anterior ($posicao - 1$) onde o novo elemento deve ser inserido. 
Se a posição for `0`, a cabeça da lista (`*head`) é atualizada diretamente.
Para posições no meio ou fim, os ponteiros são reconectados: o ponteiro `prox` do novo nó aponta para o nó seguinte, e o nó anterior passa a apontar para o novo nó.
Caso o ponteiro alcance `NULL` antes de chegar à posição desejada, o programa identifica como posição inválida, exibe o erro e libera a memória para evitar vazamentos.

Parte 2: Busca por Valor (`buscarValor`)
A busca foi implementada de forma sequencial pura. Um ponteiro percorre a lista nó por nó, enquanto uma variável inteira incrementa a posição a cada passo (começando em 0). 
* Se o valor do nó for igual ao buscado, a função retorna imediatamente a posição atual.
* Se a lista chegar ao fim (`NULL`) sem encontrar o elemento, a função retorna `-1`.

Parte 3: Inversão da Lista Encadeada Simples (`inverterLista`)
Para inverter a lista *in-place* (sem criar uma nova lista ou usar vetores), utilizamos a técnica de três ponteiros simultâneos: `anterior`, `atual` e `proximo`.
* A cada iteração do laço, salvamos o resto da lista no ponteiro `proximo`.
* Invertemos o sentido do ponteiro do nó atual (`atual->prox = anterior`).
* Deslocamos os ponteiros `anterior` e `atual` uma posição para a frente.
* Ao final, a cabeça da lista (`*head`) recebe o ponteiro `anterior`, que passou a ser o novo topo da lista.

Parte 4: Dividir Lista em Duas (`dividirLista`)
Utilizamos a técnica de **Ponteiro Rápido e Lento** (*Fast/Slow Pointer*). O ponteiro `rapido` avança duas posições por vez, enquanto o ponteiro `lento` avança apenas uma. 
* Quando o ponteiro `rapido` atinge o final da lista, o ponteiro `lento` estará exatamente na metade.
* Para atender ao requisito de deixar o elemento extra na primeira lista caso o total seja ímpar, adicionamos uma checagem após o laço.
* A separação ocorre quebrando o vínculo: a `lista1` aponta para o início original, a `lista2` aponta para o nó onde o `lento` parou, e o ponteiro `prox` do nó anterior ao lento é setado para `NULL`.

Parte 5: Playlist Circular Duplamente Encadeada
A estrutura foi estendida para conter os ponteiros `prox` e `ant`. 
* **Circularidade:** Na inserção, garantimos que o ponteiro `prox` do último nó aponte para o `head`, e o ponteiro `ant` do `head` aponte para o último nó.
* **Navegação:** As funções `proximaMusica` e `musicaAnterior` apenas movem o ponteiro atual para o endereço guardado em `prox` ou `ant`.
* **Controle Anti-Loop:** Para evitar loops infinitos nas listagens ou reproduções, a função `totalMusicas` conta os elementos dando apenas uma volta completa na estrutura (parando quando o ponteiro retorna ao `head`). Esse total é usado como limite nos laços de repetição de simulação.
## Funções Implementadas:
* **Parte 1:** Inserção em Posição Específica (`inserirPosicao`)
* **Parte 2:** Busca por Valor (`buscarValor`)
* **Parte 3:** Inversão da Lista Encadeada Simples (`inverterLista`)
* **Parte 4:** Divisão de Lista usando Ponteiro Rápido/Lento (`dividirLista`)
* **Parte 5:** Playlist Circular Duplamente Encadeada com controle anti-loop

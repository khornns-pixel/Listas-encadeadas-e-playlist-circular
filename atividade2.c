#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para as partes 1 a 4 lista encadeada simples
typedef struct NoSimples {
    int valor;
    struct NoSimples *prox;
} NoSimples;

// Estrutura para a parte 5 lista circular duplamente encadeada
typedef struct No {
    char musica[100];
    struct No *prox;
    struct No *ant;
} No;

// Parte 1 inserção em Posição Específica
void inserirPosicao(NoSimples **head, int valor, int posicao) {
    if (posicao < 0) {
        printf("Erro: Posicao invalida!\n");
        return;
    }

    NoSimples *novo = (NoSimples *)malloc(sizeof(NoSimples));
    if (!novo) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novo->valor = valor;

    if (posicao == 0) {
        novo->prox = *head;
        *head = novo;
        return;
    }

    NoSimples *atual = *head;
    int i = 0;

    while (atual != NULL && i < posicao - 1) {
        atual = atual->prox;
        i++;
    }

    if (atual == NULL) {
        printf("Erro: Posicao invalida!\n");
        free(novo);
        return;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

// Parte 2 busca por valor
int buscarValor(NoSimples *head, int valor) {
    NoSimples *atual = head;
    int posicao = 0;

    while (atual != NULL) {
        if (atual->valor == valor) {
            return posicao;
        }
        atual = atual->prox;
        posicao++;
    }

    return -1;
}

// Parte 3 inverte a lista In-place
void inverterLista(NoSimples **head) {
    NoSimples *anterior = NULL;
    NoSimples *atual = *head;
    NoSimples *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior; 
        anterior = atual; 
        atual = proximo;
    }

    *head = anterior;
}

// Parte 4 divide a lista em duas (Fast/Slow Pointer)
void dividirLista(NoSimples *head, NoSimples **lista1, NoSimples **lista2) {
    if (head == NULL) {
        *lista1 = NULL;
        *lista2 = NULL;
        return;
    }

    NoSimples *lento = head;
    NoSimples *rapido = head;
    NoSimples *anterior_lento = NULL;

    while (rapido != NULL && rapido->prox != NULL) {
        rapido = rapido->prox->prox;
        anterior_lento = lento;
        lento = lento->prox;
    }

    if (rapido != NULL) {
        anterior_lento = lento;
        lento = lento->prox;
    }

    *lista1 = head;
    *lista2 = lento;

    if (anterior_lento != NULL) {
        anterior_lento->prox = NULL;
    }
}

void exibirListaSimples(NoSimples *head) {
    NoSimples *atual = head;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void liberarListaSimples(NoSimples *head) {
    NoSimples *atual = head;
    while (atual != NULL) {
        NoSimples *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

// Parte 5 playlist circular duplamemnte encadeada
void adicionarMusica(No **head, char *nome) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) return;
    
    int i = 0;
    while (nome[i] != '\0' && i < 99) {
        novo->musica[i] = nome[i];
        i++;
    }
    novo->musica[i] = '\0';

    if (*head == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        *head = novo;
        return;
    }

    No *ultimo = (*head)->ant;

    ultimo->prox = novo;
    novo->ant = ultimo;
    novo->prox = *head;
    (*head)->ant = novo;
}

void proximaMusica(No **atual) {
    if (*atual != NULL) {
        *atual = (*atual)->prox;
    }
}

void musicaAnterior(No **atual) {
    if (*atual != NULL) {
        *atual = (*atual)->ant;
    }
}

void exibirPlaylist(No *head) {
    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    No *atual = head;
    printf("Playlist: ");
    do {
        printf("[%s] <-> ", atual->musica);
        atual = atual->prox;
    } while (atual != head);
    printf("(Volta ao inicio)\n");
}

int totalMusicas(No *head) {
    if (head == NULL) return 0;

    int contador = 0;
    No *atual = head;
    do {
        contador++;
        atual = atual->prox;
    } while (atual != head);

    return contador;
}

void liberarPlaylist(No **head) {
    if (*head == NULL) return;

    No *atual = *head;
    No *proximoNode;
    
    (*head)->ant->prox = NULL; 

    while (atual != NULL) {
        proximoNode = atual->prox;
        free(atual);
        atual = proximoNode;
    }
    *head = NULL;
}

int main() {
    //Testando tistas simples partes 1 a 4
    printf("=== TESTANDO LISTA SIMPLES ===\n");
    NoSimples *listaSimples = NULL;

    inserirPosicao(&listaSimples, 10, 0); 
    inserirPosicao(&listaSimples, 30, 1); 
    inserirPosicao(&listaSimples, 20, 1);
    printf("Lista Inicial: ");
    exibirListaSimples(listaSimples);

    printf("Buscando valor 20: Posicao %d\n", buscarValor(listaSimples, 20));
    printf("Buscando valor 99: Posicao %d\n", buscarValor(listaSimples, 99));

    printf("\nInvertendo a lista...\n");
    inverterLista(&listaSimples);
    printf("Lista Invertida: ");
    exibirListaSimples(listaSimples);

    liberarListaSimples(listaSimples);
    listaSimples = NULL;
    inserirPosicao(&listaSimples, 10, 0);
    inserirPosicao(&listaSimples, 20, 1);
    inserirPosicao(&listaSimples, 30, 2);
    inserirPosicao(&listaSimples, 40, 3);
    inserirPosicao(&listaSimples, 50, 4);
    printf("\nLista antes da divisao: ");
    exibirListaSimples(listaSimples);

    NoSimples *l1 = NULL, *l2 = NULL;
    dividirLista(listaSimples, &l1, &l2);
    printf("Lista 1 (maior ou igual se impar): ");
    exibirListaSimples(l1);
    printf("Lista 2: ");
    exibirListaSimples(l2);

    liberarListaSimples(l1); 
    liberarListaSimples(l2);

    // Testando a playlist circular parte 5
    printf("\n=== TESTANDO PLAYLIST CIRCULAR ===\n");
    No *playlist = NULL;

    adicionarMusica(&playlist, "Rock");
    adicionarMusica(&playlist, "Jazz");
    adicionarMusica(&playlist, "Pop");

    exibirPlaylist(playlist);
    printf("Total de musicas: %d\n", totalMusicas(playlist));

    printf("\nTocando a playlist (Simulacao de Fim):\n");
    No *trackAtual = playlist;
    int limite = totalMusicas(playlist);
    
    for (int i = 0; i < limite; i++) {
        printf("Tocando agora: %s\n", trackAtual->musica);
        proximaMusica(&trackAtual);
    }
    printf("Todas as musicas foram tocadas uma vez!\n");

    liberarPlaylist(&playlist);
    return 0;
}

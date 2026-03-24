#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TIPO char*
#define F_LEITURA " %s"
#define F_ESCRITA "%s"

typedef struct {
    TIPO *vetor;
    int tamanho;
    int quantidade;
} Lista;

Lista Lista_Criar(int tamanho) {
    Lista lista;
    lista.vetor = (TIPO *)malloc(tamanho * sizeof(TIPO));
    lista.tamanho = tamanho;
    lista.quantidade = 0;
    return lista;
}

void Lista_Mostrar(Lista *lista) {
    if (lista->quantidade == 0) {
        return;
    }
    for (int i = 0; i < lista->quantidade - 1; i++) {
        printf(F_ESCRITA " ", lista->vetor[i]);
    }
    if (lista->quantidade > 0)
        printf(F_ESCRITA, lista->vetor[lista->quantidade - 1]);
    printf("\n");
}

void Lista_Inserir(Lista *lista, TIPO valor){
    void DeslocarDireita(Lista *lista, int posicao) {
        for(int i = lista->quantidade; i > posicao; i--) {
            lista->vetor[i] = lista->vetor[i - 1];
        }
    }

    if (lista->quantidade >= lista->tamanho) {
        free(valor);
        return;
    }

    int p = 0;
    while (p < lista->quantidade && strcmp(lista->vetor[p], valor) < 0) {
        p++;
    }

    if (p < lista->quantidade && strcmp(lista->vetor[p], valor) == 0) {
        free(valor);
        return;
    }

    DeslocarDireita(lista, p);
    lista->vetor[p] = valor;
    lista->quantidade++;
}

void Lista_Excluir(Lista *lista, TIPO valor){
    void DeslocarEsquerda(Lista *lista, int posicao) {
        for(int i = posicao; i < lista->quantidade - 1; i++) {
            lista->vetor[i] = lista->vetor[i + 1];
        }
    }

    if (lista->quantidade == 0) {
        return;
    }
    
    int p = 0;
    while (p < lista->quantidade && strcmp(lista->vetor[p], valor) != 0) {
        p++;
    }

    if (p == lista->quantidade) {
        return;
    }
    free(lista->vetor[p]);
    DeslocarEsquerda(lista, p);
    lista->quantidade--;
}

void Lista_Buscar(Lista *lista, TIPO valor){
    for (int i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->vetor[i], valor) == 0) {
            printf("SIM\n");
            return;
        }
    }
    printf("NAO\n");
}

int main() {
    int n = 0;
    if (scanf("%d", &n) == EOF) return 0;

    Lista lista = Lista_Criar(n);
    char comando;
    char buffer[256];

    while (scanf(" %c", &comando) != EOF) {
        if (comando == 'I') {
            scanf(" %s", buffer);
            
            TIPO novaString = (TIPO)malloc((strlen(buffer) + 1) * sizeof(char));
            strcpy(novaString, buffer);
            
            Lista_Inserir(&lista, novaString);

        } else if (comando == 'R') {
            scanf(" %s", buffer);
            Lista_Excluir(&lista, buffer);
            
        } else if (comando == 'B') {
            scanf(" %s", buffer);
            Lista_Buscar(&lista, buffer);
            
        } else if (comando == 'M') {
            Lista_Mostrar(&lista);
        }
    }
    
    for (int i = 0; i < lista.quantidade; i++) {
        free(lista.vetor[i]);
    }
    free(lista.vetor);
    
    return 0;
}
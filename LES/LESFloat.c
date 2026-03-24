#include<stdio.h>
#include<stdlib.h>

#define TIPO float
#define F_LEITURA "%f"
#define F_ESCRITA "%.6g"

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
        printf(F_ESCRITA "\n", lista->vetor[lista->quantidade - 1]);
}

void Lista_Inserir(Lista *lista, TIPO valor){
    void DeslocarDireita(Lista *lista, int posicao) {
        for(int i = lista->quantidade; i > posicao; i--) {
            lista->vetor[i] = lista->vetor[i - 1];
        }
    }

    if (lista->quantidade >= lista->tamanho) {
        return;
    }

    int p = 0;
    while (p < lista->quantidade && lista->vetor[p] < valor) {
        p++;
    }

    if (p < lista->quantidade && lista->vetor[p] == valor) {
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
    while (p < lista->quantidade && lista->vetor[p] != valor) {
        p++;
    }

    if (p == lista->quantidade) {
        return;
    }

    DeslocarEsquerda(lista, p);
    lista->quantidade--;
}

void Lista_Buscar(Lista *lista, TIPO valor){
    for (int i = 0; i < lista->quantidade; i++) {
        if (lista->vetor[i] == valor) {
            printf("SIM\n");
            return;
        }
    }
    printf("NAO\n");
}

int main() {
    int n = 0;
    scanf("%d", &n);

    Lista lista = Lista_Criar(n);
    while (1) {
        char comando;
        TIPO valor;
        if(scanf(" %c", &comando) == EOF) {
            break;
        }

        if (comando == 'I') {
            scanf(F_LEITURA, &valor);
            if (valor < 0) {
                continue;
            }
            Lista_Inserir(&lista, valor);
        } else if (comando == 'R') {
            scanf(F_LEITURA, &valor);
            if (valor < 0) {
                continue;
            }
            Lista_Excluir(&lista, valor);
        } else if (comando == 'B') {
            scanf(F_LEITURA, &valor);
            if (valor < 0) {
                continue;
            }
            Lista_Buscar(&lista, valor);
        } else if (comando == 'M') {
            Lista_Mostrar(&lista);
        }
    }
    
    free(lista.vetor);
    return 0;
}
#include<stdio.h>
#include<stdlib.h>

#define TIPO int
#define F_LEITURA " %d"
#define F_ESCRITA "%d"


typedef struct {
    TIPO *vetor;
    int tamanho;
    int topo;
} Pilha;

Pilha Pilha_Criar(int tamanho) {
    Pilha pilha;
    pilha.vetor = (TIPO *)malloc(tamanho * sizeof(TIPO));
    pilha.tamanho = tamanho;
    pilha.topo = -1;
    return pilha;
}

void Pilha_Empilhar(Pilha *pilha, TIPO valor) {
    if (pilha->topo >= pilha->tamanho - 1) {
        return;
    }
    pilha->topo++;
    pilha->vetor[pilha->topo] = valor;
    return;
}

void Pilha_Desempilhar(Pilha *pilha) {
    if (pilha->topo <= -1){
        return;
    }
    TIPO valor = pilha->topo;
    pilha->topo--;
    return;
}

void Pilha_Topo(Pilha *pilha) {
    if (pilha->topo <= -1){
        return;
    }
    printf(F_ESCRITA "\n", pilha->vetor[pilha->topo]);
    return;
}

void Pilha_Mostrar_Base_Topo(Pilha *pilha){
    if (pilha->topo == -1) {
        return;
    }
    for (int i = 0; i < pilha->topo; i++) {
        printf(F_ESCRITA " ", pilha->vetor[i]);
    }
    printf(F_ESCRITA "\n", pilha->vetor[pilha->topo]);
    return;
}

void Pilha_Mostrar_Topo_Base(Pilha *pilha){
    if (pilha->topo == -1) {
        return;
    }
    for (int i = pilha->topo; i > 0; i--) {
        printf(F_ESCRITA " ", pilha->vetor[i]);
    }
    printf(F_ESCRITA "\n", pilha->vetor[0]);
    return;
}

int main() {
    int n = 0;
    scanf("%d", &n);

    Pilha pilha = Pilha_Criar(n);
    while (1) {
        char comando;
        TIPO valor;
        if(scanf(" %c", &comando) == EOF) {
            break;
        }

        if (comando == 'E') {
            scanf(F_LEITURA, &valor);
            Pilha_Empilhar(&pilha, valor);
        } else if (comando == 'D') {
            Pilha_Desempilhar(&pilha);
        } else if (comando == 'T') {
            Pilha_Topo(&pilha);
        } else if (comando == 'B') {
            Pilha_Mostrar_Base_Topo(&pilha);
        } else if (comando == 'X') {
            Pilha_Mostrar_Topo_Base(&pilha);
        }
    }
    
    free(pilha.vetor);
    return 0;
}
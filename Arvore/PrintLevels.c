#include<stdio.h>
#include<stdlib.h>


typedef struct No{
    int dado;
    struct No* esquerdo;
    struct No* direito;
    struct No* pai;
} No;

typedef struct Arvore{
    No* raiz;
    int quantidade;
} Arvore;

Arvore criarArvore(){
    Arvore arvore;
    arvore.raiz = NULL;
    arvore.quantidade = 0;
    return arvore;
}

No* criarNo(int dado){
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->pai = NULL;
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

void inserirValor(Arvore* arvore, int valor){
    No* novo = criarNo(valor);
    No* pai = NULL;
    No* atual = arvore->raiz;
    
    while(atual != NULL){
        pai = atual;
        if (valor < atual->dado){
            atual = atual->esquerdo;
        } else if(valor > atual->dado) {
            atual = atual->direito;
        } else {
            free(novo);
            return;
        }
    }

    if (pai != NULL){
        if (valor < pai->dado){
            pai->esquerdo = novo;
        } else {
            pai->direito = novo;
        }
        novo->pai = pai;
    } else {
        arvore->raiz = novo;
    }
    arvore->quantidade++;
}

void freeArvore(No* no){
    if (no != NULL){
        freeArvore(no->esquerdo);
        freeArvore(no->direito);
        free(no);
    }
}


void mostrarEmNiveis(Arvore* arvore){
    if (arvore->raiz == NULL){
        return;
    }
    No* fila[arvore->quantidade];
    int inicio = 0;
    int fim = 0;

    fila[fim++] = arvore->raiz;

    while (inicio < fim){
        No* atual = fila[inicio++];
        printf("%d\n", atual->dado);

        if (atual->esquerdo != NULL){
            fila[fim++] = atual->esquerdo;
        }
        if (atual->direito != NULL){
            fila[fim++] = atual->direito;
        }
    }
    return;

}

int main(){
    int n;
    int valor;
    Arvore arvore = criarArvore();
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++){
        scanf("%d", &valor);
        inserirValor(&arvore, valor);
    }

    mostrarEmNiveis(&arvore);

    if (arvore.raiz != NULL){
        freeArvore(arvore.raiz);
    }
    return 0;
}

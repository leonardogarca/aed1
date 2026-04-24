#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int dado;
    struct No* pai;
    struct No* esquerdo;
    struct No* direito;
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
    No* filho = arvore->raiz;
    
    while(filho != NULL){
        pai = filho;
        // CORREÇÃO: Duplicatas devem ir para a DIREITA.
        // Se novo->dado for IGUAL a filho->dado, ele deve ir pro direito.
        if(novo->dado >= filho->dado){ 
            filho = filho->direito;
        } else {
            filho = filho->esquerdo;
        }
    }
    
    if(pai != NULL){
        if(novo->dado >= pai->dado){ // CORREÇÃO aplicada aqui também
            pai->direito = novo;
        } else {
            pai->esquerdo = novo;
        }
        novo->pai = pai;
    } else {
        arvore->raiz = novo;
    }
    arvore->quantidade++;
}

void removerValor(Arvore* arvore, int valor){
    No* atual = arvore->raiz;
    
    // Busca o nó (a primeira ocorrência encontrada será a mais próxima da raiz) [cite: 14]
    while(atual != NULL && atual->dado != valor){
        if(valor < atual->dado){
            atual = atual->esquerdo;
        } else {
            atual = atual->direito; 
        }
    }

    // Se não achou, apenas ignora [cite: 13]
    if(atual == NULL) return; 

    // Caso 3: Nó tem dois filhos. Substitui pelo sucessor.
    if(atual->esquerdo != NULL && atual->direito != NULL){
        No* sucessor = atual->direito;
        while(sucessor->esquerdo != NULL){
            sucessor = sucessor->esquerdo;
        }
        // Copia o valor do sucessor para o nó atual
        atual->dado = sucessor->dado;
        // Agora, o nó que realmente vamos remover da memória é o sucessor
        atual = sucessor; 
    }

    // Neste ponto, 'atual' tem no máximo 1 filho (ou é folha).
    No* filho = (atual->esquerdo != NULL) ? atual->esquerdo : atual->direito;

    // Arruma o ponteiro 'pai' do filho, se existir
    if(filho != NULL){
        filho->pai = atual->pai;
    }

    // Arruma o ponteiro do pai do nó sendo removido
    if(atual->pai == NULL){
        arvore->raiz = filho; // O nó removido era a raiz
    } else if(atual == atual->pai->esquerdo){
        atual->pai->esquerdo = filho;
    } else {
        atual->pai->direito = filho;
    }

    printf("%d\n", valor); // A cada exclusão bem sucedida, mostra o valor [cite: 16]
    free(atual);
    arvore->quantidade--;
}

void preOrder(Arvore* arvore, No* no){
    if(no != NULL){
        printf("%d\n", no->dado); // Mostra os itens em pré-ordem, um por linha [cite: 8]
        preOrder(arvore, no->esquerdo);
        preOrder(arvore, no->direito);
    }
}

void inOrder(Arvore* arvore, No* no){
    if(no != NULL){
        inOrder(arvore, no->esquerdo);
        printf("%d\n", no->dado); // Mostra os itens em ordem, um por linha [cite: 8]
        inOrder(arvore, no->direito);
    }
}

void postOrder(Arvore* arvore, No* no){
    if(no != NULL){
        postOrder(arvore, no->esquerdo);
        postOrder(arvore, no->direito);
        printf("%d\n", no->dado); // Mostra os itens em pós-ordem, um por linha [cite: 8]
    }
}

int main(){
    Arvore arvore = criarArvore();
    int valor = 0;
    char comando[20];
    
    // Lê a entrada até o final do arquivo (EOF) [cite: 9]
    while(scanf("%s", comando) != EOF){
        if(strcmp(comando, "insert") == 0){
            scanf("%d", &valor);
            inserirValor(&arvore, valor);
        }
        else if(strcmp(comando, "delete") == 0){
            scanf("%d", &valor);
            removerValor(&arvore, valor);
        }
        else if(strcmp(comando, "pre-order") == 0){
            preOrder(&arvore, arvore.raiz);
        }
        else if(strcmp(comando, "in-order") == 0){
            inOrder(&arvore, arvore.raiz);
        }
        else if(strcmp(comando, "post-order") == 0){
            postOrder(&arvore, arvore.raiz);
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    int altura;
    struct No* esquerdo;
    struct No* direito;
} No;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int obterAltura(No* no) {
    if (no == NULL) return 0;
    return no->altura;
}

int fatorBalanceamento(No* no) {
    if (no == NULL) return 0;
    return obterAltura(no->esquerdo) - obterAltura(no->direito);
}

No* criarNoAVL(int dado) {
    No* no = (No*)malloc(sizeof(No));
    no->dado = dado;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1; // Folha começa com altura 1
    return no;
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerdo;
    No* T2 = x->direito;

    // Realiza a rotação
    x->direito = y;
    y->esquerdo = T2;

    // Atualiza as alturas (primeiro o y, depois o x que subiu)
    y->altura = max(obterAltura(y->esquerdo), obterAltura(y->direito)) + 1;
    x->altura = max(obterAltura(x->esquerdo), obterAltura(x->direito)) + 1;

    return x; // Nova raiz da subárvore
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direito;
    No* T2 = y->esquerdo;

    // Realiza a rotação
    y->esquerdo = x;
    x->direito = T2;

    // Atualiza as alturas
    x->altura = max(obterAltura(x->esquerdo), obterAltura(x->direito)) + 1;
    y->altura = max(obterAltura(y->esquerdo), obterAltura(y->direito)) + 1;

    return y; // Nova raiz da subárvore
}

No* inserirAVL(No* no, int dado) {
    // 1. Inserção padrão de BST
    if (no == NULL) return criarNoAVL(dado);

    if (dado < no->dado)
        no->esquerdo = inserirAVL(no->esquerdo, dado);
    else if (dado > no->dado)
        no->direito = inserirAVL(no->direito, dado);
    else
        return no; // Chaves duplicadas ignoradas

    // 2. Atualiza a altura do ancestral atual
    no->altura = 1 + max(obterAltura(no->esquerdo), obterAltura(no->direito));

    // 3. Verifica o balanceamento
    int balance = fatorBalanceamento(no);

    // 4. Se desbalanceou, trata os 4 casos possíveis:

    // Caso Esquerda-Esquerda (Pesa pra esquerda, filho pesa pra esquerda)
    if (balance > 1 && dado < no->esquerdo->dado)
        return rotacaoDireita(no);

    // Caso Direita-Direita (Pesa pra direita, filho pesa pra direita)
    if (balance < -1 && dado > no->direito->dado)
        return rotacaoEsquerda(no);

    // Caso Esquerda-Direita (Pesa pra esquerda, mas o filho pesa pra direita)
    if (balance > 1 && dado > no->esquerdo->dado) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo); // Alinha
        return rotacaoDireita(no);                    // Rotaciona
    }

    // Caso Direita-Esquerda (Pesa pra direita, mas o filho pesa pra esquerda)
    if (balance < -1 && dado < no->direito->dado) {
        no->direito = rotacaoDireita(no->direito);    // Alinha
        return rotacaoEsquerda(no);                   // Rotaciona
    }

    return no; // Retorna o nó original se não precisou rotacionar
}

No* minValorAVL(No* no) {
    No* atual = no;
    while (atual->esquerdo != NULL)
        atual = atual->esquerdo;
    return atual;
}

No* removerAVL(No* raiz, int dado) {
    // 1. Remoção padrão BST
    if (raiz == NULL) return raiz;

    if (dado < raiz->dado)
        raiz->esquerdo = removerAVL(raiz->esquerdo, dado);
    else if (dado > raiz->dado)
        raiz->direito = removerAVL(raiz->direito, dado);
    else {
        // Nó achado. Caso com um filho ou nenhum.
        if ((raiz->esquerdo == NULL) || (raiz->direito == NULL)) {
            No* temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

            if (temp == NULL) { // Sem filhos
                temp = raiz;
                raiz = NULL;
            } else { // Um filho
                *raiz = *temp; // Copia conteúdo do filho pro nó atual
            }
            free(temp);
        } else {
            // Caso com dois filhos: pega o sucessor (menor da direita)
            No* temp = minValorAVL(raiz->direito);
            raiz->dado = temp->dado;
            // Apaga o sucessor na subárvore direita
            raiz->direito = removerAVL(raiz->direito, temp->dado);
        }
    }

    // Se a árvore tinha só um nó que foi deletado, vaza
    if (raiz == NULL) return raiz;

    // 2. Atualiza a altura do nó atual
    raiz->altura = 1 + max(obterAltura(raiz->esquerdo), obterAltura(raiz->direito));

    // 3. Fator de balanceamento
    int balance = fatorBalanceamento(raiz);

    // 4. Casos de rotação
    
    // Esquerda-Esquerda
    if (balance > 1 && fatorBalanceamento(raiz->esquerdo) >= 0)
        return rotacaoDireita(raiz);

    // Esquerda-Direita
    if (balance > 1 && fatorBalanceamento(raiz->esquerdo) < 0) {
        raiz->esquerdo = rotacaoEsquerda(raiz->esquerdo);
        return rotacaoDireita(raiz);
    }

    // Direita-Direita
    if (balance < -1 && fatorBalanceamento(raiz->direito) <= 0)
        return rotacaoEsquerda(raiz);

    // Direita-Esquerda
    if (balance < -1 && fatorBalanceamento(raiz->direito) > 0) {
        raiz->direito = rotacaoDireita(raiz->direito);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

typedef struct Arvore {
    No* raiz;
    int quantidade;
} Arvore;

Arvore criarArvore() {
    Arvore arvore;
    arvore.raiz = NULL;
    arvore.quantidade = 0;
    return arvore;
}

// Função casca para a inserção
void inserirValor(Arvore* arvore, int valor) {
    // A função inserirAVL retorna o nó raiz atualizado após possíveis rotações
    arvore->raiz = inserirAVL(arvore->raiz, valor);
}

// Função casca para a remoção
void removerValor(Arvore* arvore, int valor) {
    // A função removerAVL retorna o nó raiz atualizado após possíveis rotações
    arvore->raiz = removerAVL(arvore->raiz, valor);
}

// Mantendo suas funções de impressão originais (apenas arrumando para imprimir em linha reta se preferir)
void preOrder(No* no) {
    if (no != NULL) {
        printf("%d\n", no->dado);
        preOrder(no->esquerdo);
        preOrder(no->direito);
    }
}

void inOrder(No* no) {
    if (no != NULL) {
        inOrder(no->esquerdo);
        printf("%d\n", no->dado);
        inOrder(no->direito);
    }
}

void postOrder(No* no) {
    if (no != NULL) {
        postOrder(no->esquerdo);
        postOrder(no->direito);
        printf("%d\n", no->dado);
    }
}

int main() {
    Arvore arvore = criarArvore();
    int valor = 0;
    char comando[20];
    
    // A entrada termina com o marcador de final de arquivo (EOF) [cite: 33, 95, 220]
    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "insert") == 0) {
            scanf("%d", &valor);
            inserirValor(&arvore, valor);
        }
        else if (strcmp(comando, "delete") == 0) {
            scanf("%d", &valor);
            removerValor(&arvore, valor);
        }
        else if (strcmp(comando, "pre-order") == 0) {
            preOrder(arvore.raiz);
        }
        else if (strcmp(comando, "in-order") == 0) {
            inOrder(arvore.raiz);
        }
        else if (strcmp(comando, "post-order") == 0) {
            postOrder(arvore.raiz);
        }
    }
    
    return 0;
}
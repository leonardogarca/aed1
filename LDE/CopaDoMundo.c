#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    char valor;
    struct No* proximo;
} No;

typedef struct Lista{
    No* inicio;
    No* fim;
} Lista;

No* No_Criar(char valor){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

Lista Lista_Criar(){
    Lista lista;
    lista.inicio = NULL;
    lista.fim = NULL;
    return lista;
}

void Lista_Inserir_Cauda(Lista* lista, char valor){
    No* novo = No_Criar(valor);
    if (lista->inicio == NULL){
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    return;
}

char Lista_Remover_Cabeca(Lista* lista){
    if (lista->inicio == NULL){
        return '\0';
    }
    No* temp = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    char valor = temp->valor;
    free(temp);
    if (lista->inicio == NULL){
        lista->fim = NULL;
    }
    return valor;
}

void Lista_Imprimir(Lista* lista){
    No* atual = lista->inicio;
    while(atual != NULL){
        printf("%c", atual->valor);
        if (atual->proximo != NULL){
            printf(" ");
        } else {
            printf("\n");
        }
        atual = atual->proximo;
    }
}

int main() {
    Lista lista = Lista_Criar();
    for (char time = 'A'; time <= 'P'; time++){
        Lista_Inserir_Cauda(&lista, time);
    }

    for (int i = 0; i < 15; i++){
        char time1 = Lista_Remover_Cabeca(&lista);
        char time2 = Lista_Remover_Cabeca(&lista);
        int gols1, gols2;
        scanf("%d %d", &gols1, &gols2);
        if (gols1 > gols2){
            Lista_Inserir_Cauda(&lista, time1);
        } else {
            Lista_Inserir_Cauda(&lista, time2);
        }
    }
    Lista_Imprimir(&lista);
    free(lista.inicio);
    return 0;

}
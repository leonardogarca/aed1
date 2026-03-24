#include<stdio.h>

typedef struct {
    int carro;
    char piloto[41];
    char equipe[41];
    double tempo;
} Registro;

void intercala(Registro* v, int e, int m, int d){
    int tamanho = d - e + 1;
    Registro temp[tamanho];
    
    int esq = e;         
    int dir = m + 1;     
    int i = 0;
    
    while(esq <= m && dir <= d){
        if(v[esq].tempo <= v[dir].tempo) {
            temp[i++] = v[esq++];
        } else {
            temp[i++] = v[dir++];
        }
    }
    
    while(esq <= m) {
        temp[i++] = v[esq++];
    }
    
    while(dir <= d) {
        temp[i++] = v[dir++];
    }
    
    for(i = 0; i < tamanho; i++) {
        v[e + i] = temp[i];
    }
}

void mergeSort(Registro* v, int n, int e, int d){
    if(e < d){
        int m = (e + d) / 2;
        mergeSort(v, n, e, m);
        mergeSort(v, n, m + 1, d);
        intercala(v, e, m, d);
    }
}

int main() {
    int n = 0;
    scanf("%d", &n);

    Registro vetor[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %s %s %lf", &vetor[i].carro, vetor[i].piloto, vetor[i].equipe, &vetor[i].tempo);
    }
    mergeSort(vetor, n, 0, n - 1);

    int i;
    scanf("%d", &i);

    i = i - 1;

    printf("%d %s %s\n", vetor[i].carro, vetor[i].piloto, vetor[i].equipe);
    return 0;
}
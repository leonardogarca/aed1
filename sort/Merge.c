#include<stdio.h>

void printArray(int* v, int n){
    for(int i = 0; i < n - 1; i++)
        printf("%d ", v[i]);
    printf("%d\n", v[n - 1]);
}

void intercala(int* v, int e, int m, int d){
    int tamanho = d - e + 1;
    int temp[tamanho];
    
    int esq = e;         
    int dir = m + 1;     
    int i = 0;
    
    while(esq <= m && dir <= d){
        if(v[esq] <= v[dir]) {
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

void mergeSort(int* v, int n, int e, int d){
    if(e < d){
        int m = (e + d) / 2;
        mergeSort(v, n, e, m);
        mergeSort(v, n, m + 1, d);
        printArray(v, n);
        intercala(v, e, m, d);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int v[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
    printArray(v, n);
    mergeSort(v, n, 0, n-1);
    printArray(v, n);
    return 0;
}
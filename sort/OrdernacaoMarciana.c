#include<stdio.h>

int valor_marte(int num) {
    if (num == 0) return 0;
    
    int ordem[] = {0, 8, 9, 7, 3, 1, 2, 6, 4, 5};
    int num_copia = num;
    int resultado = 0;
    int multiplicador = 1;

    while(num > 0){
        int digito = num % 10;
        resultado += multiplicador * ordem[digito];
        multiplicador *= 10;
        num /= 10;
    }
    return resultado;
}

int compara_marte(int a, int b) {
    int valor_a = valor_marte(a);
    int valor_b = valor_marte(b);

    return valor_a - valor_b;
}

void insertionSort(int vetor[], int n) {
    for (int i = 1; i < n; i++) {
        int key = vetor[i];
        int j = i - 1;
        while (j >= 0 && compara_marte(vetor[j], key) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int vetor[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    insertionSort(vetor, n);

    for (int i = 0; i < n - 1; i++) {
        printf("%d ", vetor[i]);
    }
    printf("%d\n", vetor[n - 1]);   
}
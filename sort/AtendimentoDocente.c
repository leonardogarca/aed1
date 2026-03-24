#include<stdio.h>
#include<stdlib.h>

typedef struct {
    char ra[12];
    char nome[101];
    int segundos;
} Atendimento;

void insertionSort(Atendimento* atendimentos, int n) {
    for (int i = 1; i < n; i++) {
        Atendimento key = atendimentos[i];
        int j = i - 1;
        while (j >= 0 && atendimentos[j].segundos < key.segundos) {
            atendimentos[j + 1] = atendimentos[j];
            j--;
        }
        atendimentos[j + 1] = key;
    }
}

int main(){
    int q = 0;
    scanf("%d", &q);
    Atendimento atendimentos[q];
    for(int i = 0; i < q; i++){
        int hora_entrada, minuto_entrada, segundo_entrada;
        int hora_saida, minuto_saida, segundo_saida;
        scanf("%s %s %d:%d:%d %d:%d:%d", atendimentos[i].ra, atendimentos[i].nome, &hora_entrada, &minuto_entrada, &segundo_entrada, 
            &hora_saida, &minuto_saida, &segundo_saida);
        int segundos_entrada = hora_entrada * 3600 + minuto_entrada * 60 + segundo_entrada;
        int segundos_saida = hora_saida * 3600 + minuto_saida * 60 + segundo_saida;
        if (segundos_saida < segundos_entrada) {
            segundos_saida += 24 * 3600; // Ajusta para o próximo dia
        }
        int segundos = segundos_saida - segundos_entrada;
        atendimentos[i].segundos = segundos;
    }
    insertionSort(atendimentos, q);
    for(int i = 0; i < q; i++){
        printf("[%s] %s\n", atendimentos[i].ra, atendimentos[i].nome);
    }
    return 0;
}
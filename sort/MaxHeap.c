#include<stdio.h>

void max_heapfy(int arr[], int n, int i) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int largest = i;

    if(l < n && arr[l] >= arr[largest]) {
        largest = l;
    }
    if(r < n && arr[r] >= arr[largest]) {
        largest = r;
    }
    if(largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        max_heapfy(arr, n, largest);
    }
}

int main() {
    while(1) {
        int n = 0;
        scanf("%d", &n);
        if(n == 0) {
            break;
        }
        int arr[n];
        for(int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        for(int i = n/2 - 1; i >= 0; i--) {
            max_heapfy(arr, n, i);
        }

        for(int i = 0; i < n-1; i++) {
            printf("%d ", arr[i]);
        }
        printf("%d\n", arr[n-1]);
    }

    return 0;
}
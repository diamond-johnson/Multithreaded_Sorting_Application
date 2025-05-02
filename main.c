#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int originalArray[SIZE] = {38, 27, 43, 3, 9, 82, 10, 15, 5, 1};
int sortedArray[SIZE];

typedef struct {
    int start;
    int end;
} ThreadParams;

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void* sort(void* params) {
    ThreadParams* p = (ThreadParams*)params;
    quicksort(originalArray, p->start, p->end);
    pthread_exit(0);
}

void* merge(void* params) {
    int mid = SIZE / 2;
    int i = 0, j = mid, k = 0;

    while (i < mid && j < SIZE) {
        if (originalArray[i] < originalArray[j]) {
            sortedArray[k++] = originalArray[i++];
        } else {
            sortedArray[k++] = originalArray[j++];
        }
    }

    while (i < mid) {
        sortedArray[k++] = originalArray[i++];
    }

    while (j < SIZE) {
        sortedArray[k++] = originalArray[j++];
    }

    pthread_exit(0);
}

int main() {
    pthread_t threads[3];
    ThreadParams params1 = {0, SIZE / 2 - 1};
    ThreadParams params2 = {SIZE / 2, SIZE - 1};
    pthread_create(&threads[0], NULL, sort, (void*)&params1);
    pthread_create(&threads[1], NULL, sort, (void*)&params2);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_create(&threads[2], NULL, merge, NULL);
    pthread_join(threads[2], NULL);

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");

    return 0;
}

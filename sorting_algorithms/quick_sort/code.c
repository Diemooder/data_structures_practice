#include <stdio.h>


int partition(int* array, int start, int end){
    int pivot = array[end];
    int i = start - 1;

    for(int j = start; j <= end - 1; j++){
        if(array[j] < pivot){
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    i++;
    int temp = array[i];
    array[i] = array[end];
    array[end] = temp;
    return i;
}

void quickSort(int* array, int start, int end){
    if(end <= start) return;

    int pivot = partition(array, start, end);
    quickSort(array, start, pivot-1);
    quickSort(array, pivot+1, end);
}

int main(){

    int array[] = {10,30, 38, 764, 18, 2, 3, 5, 49, 20, 53, 20};
    int size = sizeof(array) / sizeof(int);

    quickSort(array, 0, size-1);

    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }

    return 0;
}
#include <stdio.h>


void merge(int* left_array, int* right_array, int* array, int ll, int rl, int l){
    int i = 0, li = 0, ri = 0; //indices

    while(li < ll && ri < rl){
        if(left_array[li] < right_array[ri]) array[i++] = left_array[li++];
        else array[i++] = right_array[ri++];
    }
    
    while(li < ll) array[i++] = left_array[li++];
    while(ri < rl) array[i++] = right_array[ri++];
}

void mergeSort(int* array, int length){
    if(length <= 1) return;

    int middle = length/2;
    int leftArray[middle];
    int rightArray[length-middle]; 

    int i = 0; //left array
    int j = 0; //right array

    for(;i < length; i++){
        if(i < middle) leftArray[i] = array[i];
        else rightArray[j++] = array[i];
    }

    mergeSort(leftArray, middle);
    mergeSort(rightArray, length-middle);
    merge(leftArray, rightArray, array, middle, length-middle, length);
}

int main(){

    int a[] = {29, 2, 40, 42, 37, 10, 56, 5, 94, 73};
    int size = sizeof(a) / sizeof(int);

    mergeSort(a, size);

    for(int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    return 0;
}
#include <stdio.h>

void insert_element(int* a, int i){
    int key = a[i];
    int j = i - 1;
    while(j >= 0 && a[j] > key){
        a[j+1] = a[j];
        j = j-1;
    }
    a[j+1] = key;
}

void ins_Sort(int* a, int length){
    int i = 1;
    while(i < length){
        insert_element(a, i);
        i++;
    }
}

void display(int* a, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(){

     int a[] = {10, 32, 44, 54, 2, 30, 989, 44, 38, 21, 440};
    int size = sizeof(a)/sizeof(int); //this is the size

    display(a, size);
    ins_Sort(a, size);
    display(a, size);

    return 0;
}
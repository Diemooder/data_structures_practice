#include <stdio.h>


void swap(int* a, int x, int y){
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

int locOfSmallest(int* a, int s, int e){
    int i = s;
    int j = i;
    while(i <= e){
        if(a[i] < a[j]){
            j = i;
        }
        i = i + 1;
    }
    return j;
}

void display(int* a, int n){
    int i = 0;
    while(i < n){
        printf("%d ", a[i]);
        i++;
    }
    printf("\n");
}

void selSort(int* a, int n){
    int i = 0;
    while(i < n-1){
        int j = locOfSmallest(a, i, n-1);
        swap(a, i, j);
        i++;
    }
}

int main(){

    int a[] = {10, 32, 44, 54, 2, 30, 989, 44, 38, 21, 440};
    int size = sizeof(a)/sizeof(int); //this is the size

    display(a, size);
    selSort(a, size);
    display(a, size);
    return 0;
}
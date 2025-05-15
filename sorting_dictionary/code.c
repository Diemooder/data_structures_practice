#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char* entry;
    char* word;
}DictionaryEntry;

//swap function
void swap(int* a, int x, int y){
    int t = a[x];
    a[x] = a[y];
    a[y] = t;
}

//insert sort
void insert_sort(int* a, int n){
    int i, j, key;
    for(i = 1; i < n; i++){
        key = a[i];
        for(j = i-1; j >= 0 && a[j] > key; j--){
            a[j+1] = a[j];
        }
        a[j+1] = key;
    }
}

//partitioner of quick sort, returns pivot
int partitioner(int *a, int start, int end){
    int pivot = a[end];
    int i = start - 1;
    for(int j = start; j<=end; j++){
        if(a[j] < pivot){
            i++;
            swap(a, a[j], a[i]);
        }
    }
    i++;
    swap(a, end, i);
    return i;
}

//quick sort
void quick_sort(int* a, int start, int end){
    if(end <= start) return;

    int pivot = partitioner(a, start, end);
    quick_sort(a, start, pivot-1);
    quick_sort(a, pivot+1, end);
}

//heapify
void heapify(int* a, int root, int n){
    int child, rootkey;
    int temp;
    temp = a[root];
    child = 2 * root;
    while(child <= n){
        if((child < n) && (a[child] < a[child + 1])) child++;
        if(rootkey > a[child]) break;
        else{
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

//heap sort
void heapsort(int* a, int n){
    int i;
    for(i = n / 2; i > 0; i--) heapify(a, i, n);
    for(i = n - 1; i > 0; i--){
        swap(a, a[1], a[i+1]);
        heapify(a, 1, i);
    }
}

//search separator
int search_separator(char* word, char separator){
    for(int i = 0; i < strlen(word); i++){
        if(word[i] == separator) return i;
    }
    return -1;
}

//remove newline
void remove_newline(char* str) {
    size_t len = strlen(str);
    while (len > 0 && str[len - 1] == '\n' || str[len - 1] == '\r') {
        str[len - 1] = '\0';
        len--;
    }
}

int main(){
    FILE* file = fopen("randdict_utf8.TXT", "r");

    char line[256];
    int dictionary_max_size = 20;
    DictionaryEntry* dictionary = malloc(dictionary_max_size * sizeof(DictionaryEntry));

    int currentSize = 0;
    if(file != NULL){
        while(fgets(line,sizeof(line), file)){
            DictionaryEntry current;
            current.entry = malloc(strlen(line) + 1);
            remove_newline(line);
            strcpy(current.entry, line);

            char word[30] = {0,};
            strncpy(word, line, search_separator(line, ':')-1);
            current.word = malloc(strlen(word) + 1);
            for(int i = 0; i < strlen(word); i++) word[i] = tolower(word[i]);
            strcpy(current.word, word);

            dictionary[currentSize++] = current;

            if(currentSize >= dictionary_max_size){
                dictionary_max_size *= 2;
                dictionary = realloc(dictionary, dictionary_max_size * sizeof(DictionaryEntry));
            }
        }
        fclose(file);
    }

    
    
    return 0;
}
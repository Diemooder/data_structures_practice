#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

typedef struct{
    char* entry;
    char* word;
    int number;
}DictionaryEntry;

//swap function
void swap(DictionaryEntry* a, int x, int y){
    DictionaryEntry t = a[x];
    a[x] = a[y];
    a[y] = t;
}

//partitioner of quick sort, returns pivot
int partitioner(DictionaryEntry *a, int start, int end){
    DictionaryEntry pivot = a[end];
    int i = start - 1;
    for(int j = start; j<=end; j++){
        if(strcmp(a[j].word,pivot.word) < 0){
            i++;
            swap(a, j, i);
        }
    }
    i++;
    swap(a, end, i);
    return i;
}

//quick sort
void quick_sort(DictionaryEntry* a, int start, int end){
    while (start < end) {
        int pivot = partitioner(a, start, end);

        if (pivot - start < end - pivot) {
            quick_sort(a, start, pivot - 1);
            start = pivot + 1;
        } else {
            quick_sort(a, pivot + 1, end);
            end = pivot - 1;
        }
    }
}

//insert sort
void insert_sort(DictionaryEntry* a, int n){
    int i, j;
    DictionaryEntry key;
    for(i = 1; i < n; i++){
        key = a[i];
        for(j = i-1; j >= 0 && strcmp(a[j].word, key.word) > 0; j--){
            a[j+1] = a[j];
        }
        a[j+1] = key;
    }
}

//heapify
void heapify(DictionaryEntry* a, int root, int n){
    int child;
    DictionaryEntry temp, rootkey;
    temp = a[root];
    rootkey = a[root];
    child = 2 * root;
    while(child <= n){
        if((child < n) && (strcmp(a[child].word, a[child + 1].word) < 0)) child++;
        if(strcmp(rootkey.word, a[child].word) > 0) break;
        else{
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

//heap sort
void heapsort(DictionaryEntry* a, int n){
    int i;
    for(i = n / 2; i > 0; i--) heapify(a, i, n);
    for(i = n - 1; i > 0; i--){
        swap(a, 1, i+1);
        heapify(a, 1, i);
    }
}

void personal_sort(DictionaryEntry* a, int start, int end, int depth_limit){
    if (end - start < 32) { //32 is the sweet spot
        insert_sort(a + start, end - start + 1);
        return;
    }
    if (depth_limit == 0) {
        heapsort(a + start, end - start + 1);
        return;
    }
    while (start < end) {
        int pivot = partitioner(a, start, end);

        if (pivot - start < end - pivot) {
            quick_sort(a, start, pivot - 1);
            start = pivot + 1;
        } else {
            quick_sort(a, pivot + 1, end);
            end = pivot - 1;
        }
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

//Initialize dictionary array
DictionaryEntry* array_initializer(int* currentSize){
    //open file
    FILE* file = fopen("randdict_utf8.TXT", "r");

    //buffer for entry
    char line[256];
    int dictionary_max_size = 20;
    DictionaryEntry* dictionary = malloc(dictionary_max_size * sizeof(DictionaryEntry));

    //if file does not exist
    if(file != NULL){
        //for every while there are lines in our file
        while(fgets(line,sizeof(line), file)){
            DictionaryEntry current; //the entry to add
            current.entry = malloc(strlen(line) + 1); //assign memory to entry
            remove_newline(line); //remove new line
            strcpy(current.entry, line); // add line to entry

            char word[30] = {0,}; //space for word
            strncpy(word, line, search_separator(line, ':')-1); //copy the word in word
            current.word = malloc(strlen(word) + 1); //space for word in entry
            for(int i = 0; i < strlen(word); i++) word[i] = tolower(word[i]); // to lower
            strcpy(current.word, word); //copy word to word entry

            dictionary[(*currentSize)++] = current;

            if((*currentSize) >= dictionary_max_size){
                dictionary_max_size *= 2;
                dictionary = realloc(dictionary, dictionary_max_size * sizeof(DictionaryEntry));
            }
        }
        fclose(file);
    }
    return dictionary;
}

//comparison function for qsort
int compare_dictionary_entries(const void* a, const void* b) {
    DictionaryEntry* entryA = (DictionaryEntry*)a;
    DictionaryEntry* entryB = (DictionaryEntry*)b;
    return strcmp(entryA->word, entryB->word);
}


//function time measurer
double measure_time(int x, DictionaryEntry* a, int n){ 
    clock_t t;
    t = clock();
    switch(x){
        case 2:
            quick_sort(a, 0, n-1);
            break;
        case 3:
            personal_sort(a, 0, n-1,2 * (int) (log2(n)));
            break;
        case 4:
            qsort(a, n, sizeof(DictionaryEntry), compare_dictionary_entries);
            break;
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    return time_taken;
}

//number assigner
void num_assign(DictionaryEntry* a, int n) {for(int i = 0; i < n; i++) a[i].number = i+1;}

int main(){
    int size = 0, size1 = 0, size2 = 0;
    DictionaryEntry* dictionary = array_initializer(&size);
    DictionaryEntry* dictionary1 = array_initializer(&size1);
    DictionaryEntry* dictionary2 = array_initializer(&size2);

    //CALCULATE AND SHOW TIME TAKEN
    double own_time = measure_time(2, dictionary, size); //MY IMPLEMENTATION
    double qsort_time = measure_time(4, dictionary1, size1); //C IMPLEMENTATION
    double personal_time = measure_time(3, dictionary2, size2); //PERSONAL IMPLEMENTATION

    printf("My personal sort time: %fs\n", own_time); //MY IMPLEMENTATION
    printf("C's         sort time: %fs\n", qsort_time); //C IMPLEMENTATION
    printf("Custom Best sort time: %fs\n", personal_time); //PERSONAL IMPLEMENTATION
    return 0;
}
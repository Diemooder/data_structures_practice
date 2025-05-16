#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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

//print array
void print_array(DictionaryEntry* a, int n){
    for(int i = 0; i < n; i++) printf("Entry: %s Word: %s\n", a[i].entry, a[i].word);
}

//function time measurer
double measure_time(int x, DictionaryEntry* a, int n){ 
    clock_t t;
    t = clock();
    switch(x){
        case 1:
            insert_sort(a, n);
            break;
        case 2:
            quick_sort(a, 0, n-1);
            break;
        case 3:
            heapsort(a, n-1);
            break;
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    return time_taken;
}

//number assigner
void num_assign(DictionaryEntry* a, int n) {for(int i = 0; i < n; i++) a[i].number = i+1;}

//BINARY SEARCH FUNCTION
DictionaryEntry search_word(DictionaryEntry* a, int n, char* objective, int* cmp_cnt){
    for(int i = 0; i < strlen(objective); i++) objective[i] = tolower(objective[i]); //to lower case
    int middle, start = 0, end = n - 1;
    while(start <= end){
        middle = (start + end) / 2;
        (*cmp_cnt)++;
        int cmp_result = strcmp(a[middle].word, objective);
        if(cmp_result == 0) return a[middle];
        else if(cmp_result > 0) end = middle - 1;
        else start = middle + 1;
    }
    DictionaryEntry notFound = {"Not found", "Undefined", -1};
    return notFound;
}


int main(){
    int size = 0, size2 = 0, size3= 0;
    DictionaryEntry* dictionary = array_initializer(&size);
    DictionaryEntry* dictionary2 = array_initializer(&size2);
    DictionaryEntry* dictionary3 = array_initializer(&size3); 

    //CALCULATE AND SHOW TIME TAKEN
    double inst_time = measure_time(1, dictionary, size);
    double quik_time = measure_time(2, dictionary2, size2);
    double heap_time = measure_time(3, dictionary3, size3);

    printf("Insertion sort time: %fs\n", inst_time);
    printf("Quick sort time    : %fs\n", quik_time);
    printf("Heap sort time     : %fs\n", heap_time);

    //SEARCH RELATED CODE

    //assign numbers for words
    num_assign(dictionary, size);

    //search
    char objective[256];
    while(1){
        //input scan
        printf("Search for word (-1 to exit): ");
        scanf("%s", objective);

        //if wants to exit
        if(strcmp("-1", objective) == 0) break;

        //search for word
        int comparisson_count = 0;
        DictionaryEntry result = search_word(dictionary, size-1, objective, &comparisson_count);
        printf("(%d:%d) %s\n\n", result.number, comparisson_count, result.entry);
    }
    return 0;
}
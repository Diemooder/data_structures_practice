#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int size;
    int head;
    int tail;
    char** link;
}ListNode;


ListNode create(int size){
    char** array = malloc(size * sizeof(char*));
    ListNode list_node = {size,-1, -1, array};
    return list_node;
}

int is_empty(ListNode* list){return (list->tail == -1) ? 1 : 0;}

int is_full(ListNode* list){return (list->tail + 1) == list->size ? 1 : 0;}

char* peek(ListNode* list){
    if(is_empty(list)){
        printf("ERROR: Peek on empty queue\n");
        exit(1);
    }
    return list->link[list->head];
}

void print_queue(ListNode* List){
    printf("head: %d\n", List->head);
    printf("tail: %d\n", List->tail);
    printf("[");
    for(int i = List->head; i < List->size; i++){
        printf("%s", List->link[(i) % List->size]);
        if(i < (List->size - 1)) printf(", ");
    }
    printf("]\n");
}


void enqueue(ListNode* list, char* data){
    if(is_full(list)){
        printf("ERROR: Cannot add to full list");
        exit(1);
    }
    if(is_empty(list)){
        list->head++;
        list->tail++;
        list->link[list->tail] = data;
    }else{
        int next_pos = (list->tail + 1) % list->size;
        list->link[next_pos] = data;
        list->tail++;
    }
    print_queue(list);
}

char* dequeue(ListNode* List){
    if(is_empty(List)){
        printf("ERROR: Cannot dequeue from empty queue");
        exit(1);
    }
    char* return_string = List->link[List->head];
    if(List->head == List->tail) List->head = List->tail = -1;
    else List->head = (List->head + 1) % List->size;
    print_queue(List);
    return return_string;
}

int main(){
    ListNode queue = create(5);
    enqueue(&queue, "Diego");
    enqueue(&queue, "MIDU");
    enqueue(&queue, "Jesus");
    dequeue(&queue);
    // enqueue(&queue, "Dani");
    // enqueue(&queue, "Santi");
    // enqueue(&queue, "Papa");
    return 0;
}
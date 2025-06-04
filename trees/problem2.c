#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char* word;
    char* meaning;
    struct Node *left, *right;
} Node;

// Create a node
Node* create_node(char* word, char* meaning) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->word = strdup(word);
    new_node->meaning = strdup(meaning);
    new_node->left = new_node->right = NULL;
    return new_node;
}

// Insert element to a tree
Node* add(Node* root, Node* new_node) {
    if (root == NULL) return new_node;
    int bigger = strcmp(new_node->word, root->word);
    if (bigger < 0) root->left = add(root->left, new_node);
    else if (bigger > 0) root->right = add(root->right, new_node);
    return root;
}

// Count the number of nodes
int num_nodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + num_nodes(root->left) + num_nodes(root->right);
}

// Get the height of the tree
int tree_height(Node* root) {
    if (root == NULL) return 0;
    int height_left = tree_height(root->left);
    int height_right = tree_height(root->right);
    return (height_left > height_right ? height_left : height_right) + 1;
}

// Binary search tree
int binary_search(Node* root, char* word, int level) {
    if (root == NULL) return -1;
    int comparison = strcmp(root->word, word);
    if (comparison == 0) {
        printf("%s (레벨 : %d)\n", root->meaning, level);
        return level;
    }
    else if (comparison < 0) return binary_search(root->right, word, level + 1);
    else return binary_search(root->left, word, level + 1);
}

// Remove newline for simplicity
void remove_newline(char* str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

// Trim leading and trailing whitespace
void trim_whitespace(char* str) {
    // Trim trailing whitespace
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
    // Trim leading whitespace
    char* start = str;
    while (*start == ' ') start++;
    if (start != str) memmove(str, start, strlen(start) + 1);
}

// Search separator
int search_separator(char* word, char separator) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == separator) return i;
    }
    return -1;
}

// Line handler
Node* line_handler(char* line) {
    remove_newline(line);

    char word[30] = {0};
    char* definition;

    // Find the colon separator
    int separator_locator = search_separator(line, ':');
    if (separator_locator == -1 || strlen(line) == 0) return NULL; // Invalid or empty line

    // Copy the word up to the colon, excluding trailing space
    int word_end = separator_locator - 1;
    while (word_end >= 0 && line[word_end] == ' ') word_end--; // Skip trailing spaces
    if (word_end < 0) return NULL; // No valid word found
    strncpy(word, line, word_end + 1);
    word[word_end + 1] = '\0'; // Null-terminate

    // Definition starts after the colon and space
    definition = line + separator_locator + 2;

    return create_node(word, definition);
}

// Partition for quicksort
int partition(char** array, int start, int end) {
    char* pivot = array[end];
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (strcmp(array[j], pivot) < 0) {
            i++;
            char* temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    char* temp = array[i + 1];
    array[i + 1] = array[end];
    array[end] = temp;
    return i + 1;
}

// Quicksort
void quickSort(char** array, int start, int end) {
    if (end <= start) return;
    int pivot = partition(array, start, end);
    quickSort(array, start, pivot - 1);
    quickSort(array, pivot + 1, end);
}

// Create a list with all dictionary lines
char** lines_getter(int *count) {
    FILE* file = fopen("randdict_utf8.TXT", "r");
    if (!file) {
        printf("File not found.\n");
        return NULL;
    }

    char line[256];
    char** dictionary = malloc(500000 * sizeof(char*));
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        remove_newline(line);
        if (strlen(line) > 0) { // Skip empty lines
            dictionary[line_count++] = strdup(line);
        }
    }
    fclose(file);
    *count = line_count;

    // Sort the dictionary
    quickSort(dictionary, 0, line_count - 1);
    return dictionary;
}

// Create the tree from sorted list
Node* Create_tree(char** sorted_list, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    Node* root = line_handler(sorted_list[mid]);

    root->left = Create_tree(sorted_list, start, mid - 1);
    root->right = Create_tree(sorted_list, mid + 1, end);

    return root;
}

// Free dictionary array
void free_dictionary(char** dictionary, int count) {
    for (int i = 0; i < count; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
}

// Free tree memory
void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->word);
    free(root->meaning);
    free(root);
}

int main() {
    Node* rootNode = NULL;
    int length = 0;
    char** dictionary = lines_getter(&length);
    if (dictionary == NULL) return 1;

    rootNode = Create_tree(dictionary, 0, length - 1);

    // Print dictionary details
    printf("사전 파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n", num_nodes(rootNode));
    printf("트리의 전체 높이는 %d입니다. 트리의 노드 수는 %d개 입니다\n\n", tree_height(rootNode), num_nodes(rootNode));

    // Search functionality
    char input[100];
    while (1) {
        printf("단어를 입력하세요: ");
        if (!fgets(input, sizeof(input), stdin)) break;
        trim_whitespace(input);
        if (strlen(input) == 0) break;
        if (binary_search(rootNode, input, 1) == -1) printf("해당 단어가 없습니다.\n");
    }

    // Free memory
    free_dictionary(dictionary, length);
    free_tree(rootNode);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node{
	char* word;
	char* meaning;
	struct Node *left, *right;
}Node;

//CREATE A NODE
Node* create_node(char* word, char* meaning){
	Node* new_node = (Node*) malloc(sizeof(Node));
	new_node->word = strdup(word);
	new_node->meaning = strdup(meaning);
	new_node->left = new_node->right = NULL;
	return new_node;
}

//INSERT ELEMENT TO A TREE
Node* add(Node* root, Node* new_node){
	//If we reached the bottom, we return a created node
	if(root == NULL) return new_node;

	//Compare the weight of a word (define left or right)
	int bigger = strcmp(new_node->word, root->word);

	//if bigger, then go left, if smaller, then go right
	if(bigger < 0) root->left = add(root->left, new_node);
	else if(bigger > 0) root->right = add(root->right, new_node);

	//in case the word was equal, just return without creating
	return root;
}

//COUNT THE NUMBER OF NODES THERE ARE
int num_nodes(Node* root){
	//if we reached the bottom and the left or right node was NULL
	if(root == NULL) return 0;
	//as we are traversing each node, recursively, we will be adding 1 for each node
	return 1 + num_nodes(root->left) + num_nodes(root->right);
}

//GET THE HEIGHT OF THE TREE
int tree_height(Node* root){
	//if we reached the bottom
	if(root == NULL) return 0;
	//recursively go through each node, and branch, left and right
	int height_left = tree_height(root->left);
	int height_right = tree_height(root->right);
	//return the node with the biggest size, recursively, this will give us the longest branch
	return (height_left > height_right ? height_left : height_right) + 1;
}

//BINARY SEARCH TREE
int binary_search(Node* root, char* word, int level){
	//when we reach the bottom, as usual
	if(root == NULL) return -1;
	//word comparison
	int comparison = strcmp(root->word, word);
	//if we found the word
	if(comparison == 0){
		printf("%s (레벨 : %d)\n", root->meaning, level);
		return level;
	}
	//if the root word is bigger, then we go right, if its smaller, we go left
	else if(comparison < 0) return binary_search(root->right, word, level + 1);
	else return binary_search(root->left, word, level + 1);
}

//remove the newline for simplicity
void remove_newline(char* str) {
    size_t len = strlen(str);
    while (len > 0 && str[len - 1] == '\n' || str[len - 1] == '\r') {
        str[len - 1] = '\0';
        len--;
    }
}


//search separator
int search_separator(char* word, char separator){
    for(int i = 0; i < strlen(word); i++){
        if(word[i] == separator) return i;
    }
    return -1;
}

//line handler
Node* line_handler(char* line){
	//we remove the newlines
	remove_newline(line);

	char word[30] = {0, }; //space for word
	char* definition; //pointer for the definition
	
	int separator_locator = search_separator(line, ':') - 1;
	strncpy(word, line, separator_locator);
	definition = line + separator_locator + 2;

	return create_node(word, definition);
}



//we create the tree, we pass the root node and return the root
Node* Create_tree(Node* root){
	//open file
	FILE* file = fopen("randdict_utf8.TXT", "r");
	
	//check if file is found
	if(!file){
		printf("File not found.\n");
		return NULL;
	}
	//buffer for entry
	char line[256];
	
	//insert elements
	while (fgets(line, sizeof(line), file)) {
        	Node* node = line_handler(line);
        	if (node != NULL) root = add(root, node);
    	}
	fclose(file);
	return root;
}

//Memory free for tree
void free_tree(Node* root){
	if(root == NULL) return;
	
	free_tree(root->left);
	free_tree(root->right);

	free(root->word);
	free(root->meaning);
	free(root);	
}

//YOU ARE STILL FIGURING OUT HOW TO WORK OUT ON THIS TREE

int main(){
	Node* rootNode = NULL;
	rootNode = Create_tree(rootNode);

	//Print the dictionary details before search
	printf("사전 파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n", num_nodes(rootNode)); 
	printf("트리의 전체 높이는 %d입니다. 트리의 노드 수는 %d개 입니다\n\n", tree_height(rootNode), num_nodes(rootNode)); 	

	//Search functionality
	char input[100];
	while(1){
		printf("단어를 입력하세요: ");
		if(!fgets(input, sizeof(input), stdin)) break;
		remove_newline(input);
		if(strlen(input) == 0) break;
		if(binary_search(rootNode, input, 1) == -1) printf("해당 단어가 없습니다.\n");
	}

	//Free memory
	free_tree(rootNode);
	return 0;
}

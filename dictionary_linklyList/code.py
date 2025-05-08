class Linked_node:
    def __init__(self, prev=None, next=None, value=None):
        self.prev = prev
        self.next = next
        self.value = value

class Linked_list:
    def __init__(self):
        self.size = 0
        self.head = None
        self.tail = None

    def return_size(self):
        return self.size
    
    def add_Node(self, word, definition):
        newNode = Linked_node(None, None, (word,definition)) #gen new node

        if self.head is None: #in case we are just starting the linked list
            self.head = newNode
            self.size += 1
            return
        
        #we find the position where the word is bigger than the word at hand
        current_node = self.head
        while current_node is not None and current_node.value[0] < word:
            current_node = current_node.next
        
        if current_node is self.head:
            newNode.next = self.head
            self.head.prev = newNode
            self.head = newNode
        elif current_node is None:
            tail = self.head
            while tail.next:
                tail = tail.next
            tail.next = newNode
            newNode.prev = tail
            self.tail = newNode
        else:
            prevNode = current_node.prev
            prevNode.next = newNode
            newNode.prev = prevNode
            newNode.next = current_node
            current_node.prev = newNode
        self.size +=1
    
    def search_Node(self, word):
        currentNode = self.head
        num = 1
        if(word[0].lower() > 'm'):
            currentNode = self.tail
            num = self.size
            while currentNode and currentNode.value[0] != word:
                currentNode = currentNode.prev
                num -= 1
                if(currentNode.value[0][0] < 'm'): break
        else:
            while currentNode and currentNode.value[0] != word:
                currentNode = currentNode.next
                num += 1
                if(currentNode.value[0][0] > 'm'): break

        if not currentNode or currentNode.value[0] != word:
            return (-1,"Not found\n")
        else:
            return (num, currentNode.value[1])

#create the dictionary
dictionary = Linked_list()

#open the file
with open("randdict_utf8.TXT") as f:
    for x in f:
        value = x.split(":") #split each word by [word, definition]
        dictionary.add_Node(value[0].strip().lower(), value[1])

while(True):
    wordToSearch = input("Search for word (lowercase) (-1 to exit): ")
    if(wordToSearch == "-1"): break
    foundMatch = dictionary.search_Node(wordToSearch)
    print(f"({foundMatch[0]}) {foundMatch[1]}")
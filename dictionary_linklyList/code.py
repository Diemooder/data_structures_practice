class Linked_node:
    def __init__(self, prev=None, next=None, value=None):
        self.prev = prev
        self.next = next
        self.value = value

class Linked_list:
    def __init__(self):
        self.size = 0
        self.head = None
    
    def add_Node(self, value, position):
        if(position == 0): #if we want to add a new head
            newNode = Linked_node(None, self.head, value) #create node
            if self.head: #if the head existed before
                self.head.prev = newNode #define the prev of the current head to the new head
            self.head = newNode #replace self.head with the new head node
        else: #any other position
            current = self.head #set the current position starting from head
            
            for i in range(position - 1): #travel to the desired position
                current = current.next

            newNode = Linked_node(current,current.next, value) #create the new node
            if(current.next): #if there was a node after the position
                current.next.prev = newNode #redefine the prev of the next node
            current.next = newNode #define the next of the new node to the next
        self.size += 1


#open the file
with open("randdict_utf8.TXT") as f:
    for x in f:
        print(x)
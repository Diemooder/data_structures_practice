class Node:
    def __init__(self, data = 0, next = None):
        self.data = data
        self.next = next

class Queue:
    def __init__(self, head = None, tail = None):
        self.head = None
        self.tail = None

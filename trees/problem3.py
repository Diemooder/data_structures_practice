from collections import deque

class TreeNode:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

#tokenizer number helper (to not repeat myself)
def append_Num(characters, num_string, foundNum, prev_Num):
    if foundNum: #If there is a number stored in num_string
        characters.append(num_string) #append it
        return "", False, True #return new updated values
    return num_string, foundNum, prev_Num #do nothing if no number stored

#detector and revisionist of a string expression
def tokenizer(recieved_expression):
    characters = [] #array to return

    foundNum = False #to keep track of numbers 
    num_string = "" #storage for numbers until finished (helps with numbers with more than 1 digit)
    prev_Num = False #helps to maintain the number operator number operator order
    open_parenthesis = 0
    prev_closing_parenthesis = False

    for char in recieved_expression: #for each char
        if(char != " "): #if it is not a space
            if char.isdigit(): #if it is a number
                foundNum = True #mark that we found a number
                num_string += char #we add the number to our current number string
            else: #if it is an operator
                if char not in {'+', '-', '*', '/', '(', ')'}: #if it is not any of the valid operators
                    raise ValueError("Invalid Input: Illegal input detected") #throw error
                else: #if it is 
                    if prev_Num or (char in {'(', ')'}) or prev_closing_parenthesis: #check if the previous added element was a number, if it is
                        if(open_parenthesis == 0 and char == ')'): raise ValueError("Invalid Input: Illegal parenthesis") #In case we try to close a non existing parenthesis
                        else: #if we are not
                            if(foundNum and char == ')'): #this prevents rejecting '2)' like parts
                                num_string, foundNum, prev_Num = append_Num(characters, num_string, foundNum, prev_Num)
                            if char == '(': open_parenthesis += 1 #track opened parenthesis
                            characters.append(char) #add the operator
                            if char == ')': #track closed parenthesis
                                open_parenthesis -= 1
                                prev_closing_parenthesis = True #this and the below line prevent ') *' alike expressions to be completely rejected
                            else: prev_closing_parenthesis = False
                            prev_Num = False #set that the previous added was not a number (so an operator)
                    else: #if it is not
                        raise ValueError("Invalid Input: Illegal sequential operators") #throw error
        else: #if it is a space
            if not prev_Num: #if the previous was not a number
                num_string, foundNum, prev_Num = append_Num(characters, num_string, foundNum, prev_Num) #add the number (or at least try)
            else: #if it was
                raise ValueError("Invalid Input: Illegal sequential numbers") #throw error
    append_Num(characters, num_string, foundNum, prev_Num) #add the last number
    if(open_parenthesis > 0): raise ValueError("Invalid Input: No matched parenthesis") #in case there are remaining parenthesis
    if(not characters[-1].isdigit() and characters[-1] != ')'): raise ValueError("Invalid Input: Illegal final symbol") #in case there are left over symbols
            
    return characters #return

#Converts infix to postfix to build the tree easily
def infix_to_postfix(tokens):
    stack = [] #stack for the algorithm
    postfix = [] #the return array

    #precedence dictionary
    precedence = {
        '*' : 1,
        '/' : 1,
        '+' : 0,
        '-' : 0,
    }

    for token in tokens: #loop through the tokens
        if token.isdigit(): #if it is a digit
            postfix.append(token) #we just add it to the postfix 
        else: #if it is not
            if(len(stack) == 0): stack.append(token) #if the stack is empty, just push
            elif(token == '('): stack.append(token) #if it is a parenthesis, just push
            elif(token == ')'): #if it is closing parenthesis
                top = stack.pop() #top element
                while(top != '('): #while the top is not an opening parenthesis
                    postfix.append(top) #push to output
                    top = stack.pop() #get new top
            elif token in precedence: #for any other token
                #while the stack is not empty, and the stack is not an opening parenthesis, and the top is equal or greater precedence than the token
                while (stack and stack[-1] != '(' and precedence[stack[-1]] >= precedence[token]):
                    postfix.append(stack.pop()) #pop top and add to postfix
                stack.append(token) #if it is no greater precedence, just push the token to stack

    
    while(len(stack) != 0): #push remaining stack
        postfix.append(stack.pop())
    
    return postfix.copy()

#Create the tree with the postfix conversion
def create_tree(postfix_tokens):
    stack = [] #stack for building

    for token in postfix_tokens:
        if token.isdigit(): #if it is a digit
            stack.append(TreeNode(token)) #create a node and push to stack
        else: #if it is an operator
            right_node = stack.pop() #pop one Node for the right Node
            left_node = stack.pop()  #pop another for the left Node
            root_node = TreeNode(token) #create new node as current token as the value (basically operator)

            root_node.right = right_node #connect the popped right node to root
            root_node.left =left_node #connect the popped left node to root

            stack.append(root_node) #push this new tree to stack
    
    return stack.pop() #return root node (which would be the unique element on the stack at the end)

#prints the tree like the tree command in Linux btw
def print_tree(node, prefix="", is_left=True): #prefix tracks the indentation and lines, left defines which connector to use
    if node is not None: #if node still exists
        connector = "└── " if is_left else "├── " #if the current node is form the left side (first detected) we select one connector or other
        print(prefix + connector + str(node.value)) #we print the prefix, the chosen conector and the value
        
        # Compute prefix for leafs
        if node.left or node.right:
            # If it's the last child, don't draw vertical line below
            child_prefix = prefix + ("    " if is_left else "│   ")
            print_tree(node.left, child_prefix, False)  # left goes first
            print_tree(node.right, child_prefix, True) # then right

#TRAVERSALS
def preorder_traversal(node):
    if node is None: return []
    return [node.value] + preorder_traversal(node.left) + preorder_traversal(node.right)

def inorder_traversal(node):
    if node is None: return []
    return inorder_traversal(node.left) + [node.value] + inorder_traversal(node.right)

def postorder_traversal(node):
    if node is None: return []
    return postorder_traversal(node.left) + postorder_traversal(node.right) + [node.value]

#Level order traversal
def level_order_traversal(node):
    if node is None: #if the node is nothing 
        return []
    
    array = [] #the return array
    queue = deque([node]) #declare a queue, using the queue library for simplicity

    while queue: #whilethere are elements in queue
        node = queue.popleft() #take the first added node to the queue and pop it
        array.append(node.value) #add the value of that popped node

        if node.left: queue.append(node.left) #add to the queue the left node if it exists
        if node.right: queue.append(node.right) #the same with the right
    
    return array

#evaluation
def evaluate_expression(node):
    if(node.value.isdigit()): #if the current node in the recursion is a number
        return int(node.value) #return it
    else: #if it is not a value, it is an operator
        #detect for each operator and implement the recursiveness
        if node.value == '+':
            return evaluate_expression(node.left) + evaluate_expression(node.right)
        elif node.value == '-':
            return evaluate_expression(node.left) - evaluate_expression(node.right)
        elif node.value == '/':
            return evaluate_expression(node.left) // evaluate_expression(node.right)
        elif node.value == '*':
            return evaluate_expression(node.left) * evaluate_expression(node.right)


#"MAIN" LOOP
expression = ""
while True:
    expression = input("Enter an expression with spaces for desired behavior\nNO:  2+3*4\nYES: 2 + 3 * 4\n:")

    if len(expression) == 0:
        break

    tokenized_input = tokenizer(expression)             #convert to array, check for errors also
    postfix_input = infix_to_postfix(tokenized_input)   #convert to postfix notation
    tree = create_tree(postfix_input)                   #create the tree
    print_tree(tree)
    preorder = ' '.join(preorder_traversal(tree))       #get the different orders, pre, in, post and level
    print(f"전위표기 : {preorder}")
    inorder = ' '.join(inorder_traversal(tree))
    print(f"중위표기 : {inorder}")
    postorder = ' '.join(postorder_traversal(tree))
    print(f"후위표기 : {postorder}")
    levelorder = ' '.join(level_order_traversal(tree))
    print(f"레벨 순회: {levelorder}")
    evaluation = evaluate_expression(tree)              #evaluate the tree
    print(f"결과값 : {evaluation}")    
#tokenizer number helper (to not repeat myself)
def append_Num(characters, num_string, foundNum, prev_Num):
    if foundNum: #If there is a number stored in num_string
        characters.append(num_string) #append it
        return "", False, True #return new updated values
    return num_string, foundNum, prev_Num #do nothing if no number stored


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
            
    return characters #retrn

def infix_to_postfix(tokens):
    stack = []
    postfix = []

    for token in tokens:
        if token.isdigit():
            postfix.append(token)             
        else:
            if(len(stack) == 0): stack.append(token)

tokenized_input = tokenizer("(2 * 2)(2 * 2)")
print(tokenized_input)

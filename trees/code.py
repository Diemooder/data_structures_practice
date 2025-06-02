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

    for char in recieved_expression: #for each char
        if(char != " "): #if it is not a space
            if char.isdigit(): #if it is a number
                foundNum = True #mark that we found a number
                num_string += char #we add the number to our current number string
            else: #if it is an operator
                if char not in {'+', '-', '*', '/', '(', ')'}: #if it is not any of the valid operators
                    raise ValueError("Invalid Input: Illegal input detected") #throw error
                else: #if it is 
                    if prev_Num: #check if the previous added element was a number, if it is
                        characters.append(char) #add the operator
                        prev_Num = False #set that the previous added was not a number (so an operator)
                    else: #if it is not
                        raise ValueError("Invalid Input: Illegal sequential operators") #throw error
        else: #if it is a space
            if not prev_Num: #if the previous was not a number
                num_string, foundNum, prev_Num = append_Num(characters, num_string, foundNum, prev_Num) #add the number (or at least try)
            else: #if it was
                raise ValueError("Invalid Input: Illegal sequential numbers") #throw error
    append_Num(characters, num_string, foundNum, prev_Num) #add the last number
            
    return characters #return


print(tokenizer("23 + 211 + 42 - 1 + 31111"))

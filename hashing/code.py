from collections import deque

#We retrieve the maze from a specified file name
def retrieve_maze(filename):
    try: #try to open file
        with open(filename, 'r') as file: #open the file
            header = file.readline() #get the rows and cols row
            cols, rows = map(int, header.strip().split()) #format the row and store the values

            maze = [list(line.rstrip('\n')) for line in file] #convert each row to a list
    except FileNotFoundError: #if not found
        print("File not Found")
        exit(0)
    return maze, rows, cols

#Convert to formatted maze and return it
def convert_maze(maze, rows, cols):
    converted_maze = [] #The maze we will return
    for i in range(rows): 
        row_list = [] #the list of the rows cells
        cell_row = 2 * i + 1 #get the row cell location
        for j in range(cols):
            cell_col = 2 * j + 1 #get the col cell location

            #dictionary for the maze array
            cell = {
                "visited" : False,
                "sides" : {
                    "up" : False,
                    "down" : False,
                    "left" : False,
                    "right" : False
                }
            }
            
            cell_up = maze[cell_row - 1][cell_col] #get the upper bound
            cell_down = maze[cell_row + 1][cell_col] #get the lower bound
            cell_left = maze[cell_row][cell_col - 1] #get the left bound
            cell_right = maze[cell_row][cell_col + 1] #get the right bound

            if(cell_up == "-"): #if there is a wall on top
                cell["sides"]["up"] = True #mark True if there is, repeat below
            if(cell_down == "-"):
                cell["sides"]["down"] = True
            if(cell_left == "|"):
                cell["sides"]["left"] = True
            if(cell_right == "|"):
                cell["sides"]["right"] = True
            row_list.append(cell) #add to current row list
        converted_maze.append(row_list) #add to completed maze
    return converted_maze #return the maze


#path finder
def path_finder(maze, rows, cols):
    #define the stack that tracks our progrss
    stack = deque()
    stack.append((0, 0)) #starting from position 0,0
    print("PUSH(0,0)")

    #mark the start as visited
    maze[0][0]["visited"] = True
    
    #to see if we found a path or not
    found = False

    #Define directions to facilitate search
    directions = {
        "up" : (-1, 0),
        "down" : (1, 0),
        "left" : (0, -1),
        "right" : (0, 1)
    }

    #while the stack exists
    while stack:
        #get the row anc col of the top element (last visited cell)
        row, col = stack[-1]

        #start with the presumption that it is a dead end
        is_dead_end = True

        #check every direction
        for direction, (drow, dcol) in directions.items():
            #define the position of the direction we are looking
            curr_row, curr_col = row + drow, col + dcol

            #check if the positions we are looking at are in bounds of the maze
            if 0 <= curr_row < rows and 0 <= curr_col < cols:
                #if the cell we are looking is not a wall and if it is not visited
                if not maze[row][col]["sides"][direction] and not maze[curr_row][curr_col]["visited"]:
                    maze[curr_row][curr_col]["visited"] = True #mark the visiting cell as true
                    stack.append((curr_row, curr_col)) #push the discovered cell to the path, making it the current one
                    print(f"PUSH({curr_row}, {curr_col})") #print it as our professor's wish
                    is_dead_end = False #mark that the path was not a dead end
                    break #break of the LOOP, not if
        
        #if after looking at all directions, we found it was a dead end
        if is_dead_end:
            popped_row, popped_col = stack.pop() #pop the top element (the current one)
            print(f"POP({popped_row}, {popped_col})") #print it as our professor's wish
        
        #if the stack exists and the top stack is the bottom right corner
        if stack and stack[-1] == (rows - 1, cols -1):
            print("Found the goal!") #print that we found the goal
            found = True #mark found as true
            break #break of the while
    
    #if it is found
    if found:
        print("길이 1개 있음") #print that we found 1 path
    else:
        print("길이 없음") #print that we didn't

    return list(stack) #return the list version of the stack (the path) for later use

#print the path found
def print_path(maze, path):
    for cell in path: #for every cell of the path
        maze[2 * cell[0] + 1][2 * cell[1] + 1] = "O" #replace the empty space with an O
    
    #print the maze
    for row in maze:
        print("".join(row))


#MAZE MAIN LOOP

#ask for the file name
file_name = input("미로 파일의 이름을 입력하세요 : ")

#get the maze from the file
maze, rows, cols = retrieve_maze(file_name)

#convert it to a maze we can scan
converted_maze = convert_maze(maze, rows, cols)

#find and get the path
path = path_finder(converted_maze, rows, cols)

#print the maze with path
print_path(maze, path)
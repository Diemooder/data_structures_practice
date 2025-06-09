from collections import deque

#We retrieve the maze from a specified file name
def retrieve_maze(filename):
    with open(filename, 'r') as file: #open the file
        header = file.readline() #get the rows and cols row
        cols, rows = map(int, header.strip().split()) #format the row and store the values

        maze = [list(line.rstrip('\n')) for line in file] #convert each row to a list
    
    print(f"We got a maze with {rows} rows and {cols} cols")
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
                "location" : f"({cell_row}, {cell_col})",
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

    #Define directions to facilitate search
    directions = {
        "up" : (-1, 0),
        "down" : (1, 0),
        "left" : (0, -1),
        "right" : (0, 1)
    }

    #while the stack exists
    while stack:
        row, col = stack[-1]

        is_dead_end = True

        for direction, (drow, dcol) in directions.items():
            curr_row, curr_col = row + drow, col + dcol

            if 0 <= curr_row < rows and 0 <= curr_col < cols:
                if not maze[row][col]["sides"][direction] and not maze[curr_row][curr_col]["visited"]:
                    maze[curr_row][curr_col]["visited"] = True
                    stack.append((curr_row, curr_col))
                    print(f"PUSH({curr_row}, {curr_col})")
                    is_dead_end = False
                    break
            
        if is_dead_end:
            popped_row, popped_col = stack.pop()
            print(f"POP({popped_row}, {popped_col})")
        
        if stack and stack[-1] == (rows - 1, cols -1):
            print("Found the goal!")
            break
    

maze, rows, cols = retrieve_maze("maze1.txt")

converted_maze = convert_maze(maze, rows, cols)

path_finder(converted_maze, rows, cols)
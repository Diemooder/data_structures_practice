#define the hash function, recieves a word
def hash_fn(word, table_size):
    hash_value = 0 #the index tha we will return
    for char in word:
        #we get each character of the word and sum it, at first I intended to do only that, but realized that words with the same letters would be in the same bucket. So I added * 31 to give "weights" to the characters in the order of their appereance. 31 is chosen as it seems to act nice with ASCII and the modular, already used in other languages implemented hash functions.
        hash_value = (hash_value * 31 + ord(char)) % table_size
    return hash_value

#to not repeat code, declare bucket getter
def bucket_getter(hash_table, table_size, word):
    return hash_table[hash_fn(word, table_size)]

#define the insert function
def insert(hash_table, word, definition, table_size):
    #get the bucket
    bucket = bucket_getter(hash_table, table_size, word)

    #add the new entry to the bucket
    bucket.append({"word": word, "definition": definition})

    #check if the bucket has collisions or not
    return 1 if len(bucket ) > 1 else 0

#define the search function
def search(hash_table, word, table_size):
    #get the bucket
    bucket = bucket_getter(hash_table, table_size, word)

    #we store the steps of how deep we go into the bucket
    steps = 0
    for entry in bucket:
        steps += 1 #for every entry
        if entry["word"] == word: #if word found
            return entry["definition"], steps #return in a tuple with steps
    return None, steps #in case the word is not found

#define the hash construction function
def hash_construction(filename, table, table_size):
    try: #try to find a file with that name and action
        collisions = 0 #collisions storer
        with open(filename, "r", encoding='utf-8') as file: #open the file
            for line in file: 
                word, definition = line.strip().split(":", 1) #split word and definition
                word = word.strip() #clean spaces of word and definition
                definition= definition.strip()
                #as defined before, the insert returns 1 for each collition it detects
                collisions += insert(table, word, definition, table_size) 
        return collisions #return collisions when making the hash table
    except FileNotFoundError:
        print("File not found")
        exit(0)


#Define the table
table_size = 75000
hash_table = [[] for _ in range(table_size)]

#construct the table and get the collisions and print them
collisions = hash_construction("randdict_utf8.TXT", hash_table, table_size)
print(f"Current hash function get's us {collisions} collisions")

#MAIN LOOP

while True:
    #get the word to search
    word = input("Enter a word to search (leave empty to quit): ")
    if word == "": #exit if empty
        break
    
    #search the word and track the steps
    result, steps = search(hash_table, word, table_size)

    #display the result if found
    if result:
        print(f"Took {steps} steps")
        print(f"{word}: {result}")
    else:
        print("Word not found")

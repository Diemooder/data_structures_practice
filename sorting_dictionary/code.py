import time

class DictionaryEntry:
    def __init__(self, entry='', word='', number=0):
        self.entry = entry
        self.word = word
        self.number = number

#swap function
def swap(a, x, y):
    try:
        a[x], a[y] = a[y], a[x]
    except IndexError:
        print("", end="")

#insert sort
def insert_sort(a):
    for i in range(1, len(a)):
        key = a[i]
        j = i - 1
        while j >= 0 and a[j].word > key.word:
            a[j + 1] = a[j]
            j -= 1
        a[j + 1] = key
    print("OK")

#partitioner of quick sort, returns pivot
def partitioner(a,start,end):
    pivot = a[end]
    i = start - 1
    for j in range(start, end + 1):
        if a[j].word < pivot.word:
            i += 1
            swap(a, j, i)
    i += 1
    swap(a, end, i)
    return i

#quick sort
def quick_sort(a, start, end):
    while(start < end):
        pivot = partitioner(a, start, end)

        if(pivot - start < end - pivot):
            quick_sort(a, start, pivot - 1)
            start = pivot + 1
        else:
            quick_sort(a, pivot + 1, end)
            end = pivot - 1

#heapify
def heapify(a, root, n):
    temp = a[root]
    rootkey = a[root]
    child = 2 * root
    while(child < n):
        if((child < n) and a[child].word < a[child+1].word): child += 1
        if(rootkey.word > a[child].word): break
        else:
            a[child // 2] = a[child]
            child *= 2
    a[child // 2] = temp

#heap sort
def heapsort(a):
    n = len(a)
    for i in range(n // 2, 0, -1): heapify(a, i, n)
    for i in range(n - 1, 0, -1):
        swap(a, 1, i+1)
        heapify(a, 1, i)

#Initialize dictionary array
def array_initializer():
    dictionary = []
    try:
        with open("randdict_utf8.TXT", "r") as file:
            for line in file:
                entry_text = line.strip()
                word_text = line.split(":")[0].strip().lower()
                dictionary.append(DictionaryEntry(entry_text, word_text))
        return dictionary  
    except FileNotFoundError:
        print("FIle not found")
        return []

#print array
def print_array(a):
    for element in a:
        print(f"Entry: {a[i].entry} Word: {a[i].word}")

#function time measurer
def measure_time(x, a):
    #start timer
    start_time = time.perf_counter()
    if(x == 1): insert_sort(a)
    elif(x == 2): quick_sort(a,0,len(a)-1)
    elif(x == 3): heapsort(a)
    #end timer
    end_time = time.perf_counter()
    #calculate time
    elapsed = end_time - start_time
    return elapsed

#number assigner
def num_assign(a): 
    for i in range(len(a)): a[i].number = i+1

#BINARY SEARCH FUNCTION
def search_word(a, objective):
    cmp_cnt = 0
    objective = objective.lower()
    start, end = 0, len(a) - 1
    while(start <= end):
        middle = (start+end) // 2
        cmp_cnt += 1
        if(a[middle].word == objective): return a[middle], cmp_cnt
        elif(a[middle].word > objective): end = middle -1
        elif(a[middle].word < objective): start = middle + 1
    return DictionaryEntry("Not found", "Undefined", -1), cmp_cnt


def main():
    # Initialize dictionaries
    dictionary = array_initializer()
    dictionary2 = array_initializer()
    dictionary3 = array_initializer()

    # Calculate and show sort times
    #inst_time = measure_time(1, dictionary)
    quik_time = measure_time(2, dictionary)
    heap_time = measure_time(3, dictionary3)

    #print(f"Insertion sort time: {inst_time:.6f} seconds")
    print(f"Quick sort time    : {quik_time:.6f} seconds")
    print(f"Heap sort time     : {heap_time:.6f} seconds")

    # Assign numbers to the sorted dictionary
    num_assign(dictionary)

    # Search loop
    while True:
        objective = input("Search for word (-1 to exit): ").strip()
        if objective == "-1":
            break

        result, comparisons = search_word(dictionary, objective)
        
        if result.number == -1:
            print("(Not found)")
        else:
            print(f"({result.number}: {comparisons}) {result.entry}\n")

main()
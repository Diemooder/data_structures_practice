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


def sort_key(entry):
    return entry.word

#function time measurer
def measure_time(x, a):
    #start timer
    start_time = time.perf_counter()
    if(x == 1): quick_sort(a,0,len(a)-1)
    elif(x == 2): a.sort(key=sort_key)
    #end timer
    end_time = time.perf_counter()
    #calculate time
    elapsed = end_time - start_time
    return elapsed

def main():
    # Initialize dictionaries
    dictionary = array_initializer()
    dictionary2 = array_initializer()

    # Calculate and show sort times
    myqt_time = measure_time(1, dictionary)
    quik_time = measure_time(2, dictionary2)

    print(f"My Quick sort time: {myqt_time:.6f} seconds")
    print(f"Pythons  sort time: {quik_time:.6f} seconds")
main()
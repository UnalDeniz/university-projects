#Student Name: Deniz Ünal
#Student Number: 2019400234
#Compile Status: Compiling
#Program Status: Working
 
from mpi4py import MPI
import argparse

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    # To get the arguments with the corresponding flags argparse module is used.
    parser=argparse.ArgumentParser()
    parser.add_argument('--input_file')
    parser.add_argument('--merge_method')
    parser.add_argument('--test_file')
    args=parser.parse_args()
    size = comm.Get_size()

    # Input file is read line by line and put into an array.
    input_file = open(args.input_file)
    line = input_file.readline()
    input_list = []
    while line:
        input_list.append(line)
        line = input_file.readline()
    # share is the number of sentences each worker gets.
    share = len(input_list) // (size-1)
    # extra is there for the cases which sentence count doesn't dvisible by worker count.
    # In such a case extra is distributed to some workers one by one.
    extra = len(input_list) % (size-1)
    start = 0
    # end is the index which current partition of the array will end. 
    end = share
    input_file.close()

    # Test file is read and split into an array which all indexes corresponds to a bigram.
    test_file = open(args.test_file)
    test_str = test_file.read()
    test_list = test_str.split('\n')

    for i in range(size-1, 0, -1):
        # If there is an extra gives one more sentence to each worker
        # and decreases the extra sentence count.
        if extra > 0:
            end += 1
            extra -= 1
        # part is the array of sentences that the worker will get.
        part = input_list[start:end]
        # In the next itearation start of the part will be end of current 
        # (array partitions doesn't involve the last index).
        start = end
        end += share
        # Each worker will get corresponding sentences, merge argument 
        # and number of workers as its data.
        data={'input':part, 'size':size, 'merge_method':args.merge_method}
        comm.send(data, dest=i, tag=(10+i))

    # bi_count and mono_count holds bigrams, monograms and their corresponding counts.
    bi_count = {}
    mono_count = {}
    total_bi_count = 0
    total_mono_count = 0

    for i in range(size-1, 0, -1):
        # Gets the data from each worker and sums them to get the total count.
        recieved_data = comm.recv(source=i, tag=(20+i))
        recieved_bi = recieved_data['bigram']
        recieved_mono = recieved_data['monogram']
        for x in recieved_bi.keys():
            total_bi_count += recieved_bi[x]
            # setdefault is used to start the count from 0 if it is the first occurence of a bigram.
            bi_count[x] = bi_count.setdefault(x, 0) + recieved_bi[x]
        for x in recieved_mono.keys():
            total_mono_count += recieved_mono[x]
            mono_count[x] = mono_count.setdefault(x, 0) + recieved_mono[x]
        # If the merge type is workers master should only get data from the last worker.
        if args.merge_method == 'WORKERS': break

    # Gets each bigram from the array that holds bigrams from the test file.
    # Gets the count for both of them and divides it to the count for the
    # first word to get the probability of the bigram and prints it.
    for test in test_list:
        # Skips if there is no bigram in an test file line.
        if test == '': continue
        # If are occurrences in the sample, key would be in dictionary so gets the information from there.
        if test in bi_count.keys():
            union_count = bi_count[test]
            single_count = mono_count[test.split(' ')[0]]
            print(test, union_count / single_count)
        # If there is no occurrence in the sample, key would not be in dictionary so prints 0 manually.
        else:
            print(test, 0, '(no occurrence in sample)')

else:
    data = comm.recv(source=0, tag=(10+rank))
    print('rank:', rank, '    number of sentences:', len(data['input']))

    # bi_count and mono_count holds bigrams, monograms and their corresponding counts.
    bi_count = {}
    mono_count = {}

    # The array that holds the input sentences read word by word 
    # and the counts are incremented accordingly.
    for line in data['input']:
        line_arr = line.split(' ')
        for i in range(len(line_arr)):
            monogram = line_arr[i]
            mono_count[monogram] = mono_count.setdefault(monogram, 0) + 1
            if i < len(line_arr) - 1:
                bigram = ' '.join([line_arr[i], line_arr[i+1]])
                bi_count[bigram] = bi_count.setdefault(bigram, 0) + 1

    # If the merge method is master all workers directly send data to master.
    if data['merge_method'] == "MASTER":
        data = {'bigram':bi_count, 'monogram':mono_count}
        comm.send(data, dest=0, tag=(20+rank))
    # If the merge method is workers each worker gets data from 
    # previous worker merges it with its own data and sends it to next worker.
    elif data['merge_method'] == "WORKERS":
        # If rank is 1 there is no previous data.
        if rank > 1:
            recieved_data = comm.recv(source=(rank-1), tag=(14+rank))
            recieved_bi = recieved_data['bigram']
            recieved_mono = recieved_data['monogram']
            for x in recieved_bi.keys():
                bi_count[x] = bi_count.setdefault(x, 0) + recieved_bi[x]	
            for x in recieved_mono.keys():
                mono_count[x] = mono_count.setdefault(x, 0) + recieved_mono[x]

        size = data['size']
        data={'bigram':bi_count, 'monogram':mono_count}

        # Sends it to next worker.
        if rank < size-1:
            comm.send(data, dest=(rank+1), tag=(15+rank))
        # Last worker sends the completed data to master.
        else:
            comm.send(data, dest=0, tag=(20+rank))
    # There is no other valid merge method so throws error.
    else:
        print("Invalid merge method, terminating the program.")
        exit()


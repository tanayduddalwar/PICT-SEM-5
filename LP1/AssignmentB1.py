import threading
import time
import random

# Define the number of philosophers and forks
num_philosophers = 5
num_forks = num_philosophers

# Define semaphores for the forks and the mutex
forks = []
for i in range(num_forks):
    forks.append(threading.Semaphore(1))

mutex = threading.Semaphore(1)
# mutex to ensure that only one philosopher can or will be able to pick folk at a time.Here we have declared the acqure of the folksd in critical section so there is lock on the folk i.e mutex.


# Define the philosopher thread function
def philosopher(index):
    while True:
        print(f"Philosopher {index} is thinking...")
        time.sleep(random.randint(1, 5))
        
        mutex.acquire() # it acquires the lock for a ph
        
        left_fork_index = index
        right_fork_index = (index + 1) % num_forks
        
        forks[left_fork_index].acquire()
        print(f"Philosopher {index} has acquired left fork...")
        forks[right_fork_index].acquire()
        print(f"Philosopher {index} has acquired right fork...")
        
        mutex.release() # removes the lokc for a ph
        
        print(f"Philosopher {index} is eating...")
        time.sleep(random.randint(1, 5)) # can take any time to eat between 1 and 5 sec as it generates it randomly.
        
        forks[left_fork_index].release()
        print(f"Philosopher {index} has released left fork...")
        forks[right_fork_index].release()
        print(f"Philosopher {index} has releasedf right fork...")

# Create a thread for each philosopher
philosopher_threads = []
for i in range(num_philosophers):
    philosopher_threads.append(threading.Thread(target=philosopher, args=(i,)))
    #threading.Thread(target=philosopher, args=(i,)): Within each iteration of the loop, a new Thread object is created using Python's threading.Thread class.
    #target=philosopher: This specifies that the target function (the function that the thread will execute) is philosopher.
    #args=(i,): This provides the arguments to the philosopher function. Here, it's passing i, which is the index of the philosopher. This typically helps in identifying which philosopher each thread represents.
    
# Start the philosopher threads
for thread in philosopher_threads:
    thread.start()
    
# Wait for the philosopher threads to complete
for thread in philosopher_threads:
    thread.join()

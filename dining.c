#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];            // Keeps track of each philosopher's state
int phil[N] = {0, 1, 2, 3, 4};  // Array of philosophers
sem_t mutex;             // Mutex to control access to critical section
sem_t S[N];              // Semaphore for each philosopher

// Function to check if a philosopher can eat
void test(int philosopher) {
    if (state[philosopher] == HUNGRY && state[(philosopher + 4) % N] != EATING && state[(philosopher + 1) % N] != EATING) {
        // If the philosopher is hungry and both neighbors are not eating
        state[philosopher] = EATING;
        sleep(1);  // Simulate eating
        printf("Philosopher %d takes forks %d and %d\n", philosopher + 1,(philosopher + 4) % N + 1, philosopher + 1);
        printf("Philosopher %d is Eating\n", philosopher + 1);
        sem_post(&S[philosopher]);  // Signal that the philosopher can eat
    }
}

// Function for a philosopher to pick up forks
void take_forks(int philosopher) {
    sem_wait(&mutex);  // Enter critical section
    state[philosopher] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopher + 1);
    test(philosopher);  // Try to acquire forks
    sem_post(&mutex);  // Exit critical section
    sem_wait(&S[philosopher]);  // Wait if forks are not available
    sleep(1);
}

// Function for a philosopher to put down forks
void put_forks(int philosopher) {
    sem_wait(&mutex);  // Enter critical section
    state[philosopher] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\n", philosopher + 1, (philosopher + 4) % N + 1, philosopher + 1);
    printf("Philosopher %d is Thinking\n", philosopher + 1);
    // Check if neighbors can now eat
    test((philosopher + 4) % N);
    test((philosopher + 1) % N);
    sem_post(&mutex);  // Exit critical section
}

// Function for philosopher behavior (thinking, eating)
void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);  // Simulate thinking
        take_forks(*i);  // Try to pick up forks
        sleep(0);  // Simulate eating
        put_forks(*i);  // Put down forks
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    // Initialize semaphores
    sem_init(&mutex, 0, 1);  // Mutex semaphore, initially unlocked
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);  // Philosopher-specific semaphores
    // Create philosopher threads
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is Thinking\n", i + 1);
    }
    for (i = 0; i < N; i++) // Wait for all threads to complete
        pthread_join(thread_id[i], NULL);
    sem_destroy(&mutex); // Destroy semaphores
    for (i = 0; i < N; i++)
        sem_destroy(&S[i]);
    return 0;
}
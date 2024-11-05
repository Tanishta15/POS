#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5  // Size of the bounded buffer

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0;               // Index for the producer
int out = 0;              // Index for the consumer
sem_t empty;              // Semaphore to track empty slots
sem_t full;               // Semaphore to track filled slots
pthread_mutex_t mutex;    // Mutex to protect buffer access

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce an item (a random number)
        sem_wait(&empty);     // Wait for an empty slot
        pthread_mutex_lock(&mutex);  // Lock the buffer
        buffer[in] = item; // Critical section to add an item to the buffer
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);      // Signal that an item is available
        sleep(1);  // Simulate production time
    }
}
void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);       // Wait for an available item
        pthread_mutex_lock(&mutex);  // Lock the buffer
        item = buffer[out]; // Critical section to remove an item from the buffer
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);      // Signal that an empty slot is available
        sleep(1);  // Simulate consumption time
    }
}
int main() {
    pthread_t prod_thread, cons_thread;
    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // BUFFER_SIZE empty slots initially
    sem_init(&full, 0, 0);             // 0 full slots initially
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex
    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    // Wait for the threads to finish (in this example, they run indefinitely)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
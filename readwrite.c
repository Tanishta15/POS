#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0;        // Keeps track of the number of readers accessing the resource
sem_t resource;            // Semaphore to control access to the shared resource (for writers)
sem_t read_count_access;   // Semaphore to control access to the read_count variable

void* reader(void* arg) {
    int reader_id = *(int*)arg;
    // Reader wants to enter
    sem_wait(&read_count_access);  // Ensure exclusive access to read_count
    read_count++;                  // Increment the count of readers
    if (read_count == 1) {
        sem_wait(&resource);       // First reader locks the resource
    }
    sem_post(&read_count_access);  // Release access to read_count
    printf("Reader %d is reading the resource\n", reader_id); // Reading section
    sleep(1); // Simulate reading activity
    // Reader wants to leave
    sem_wait(&read_count_access);  // Ensure exclusive access to read_count
    read_count--;                  // Decrement the count of readers
    if (read_count == 0) {
        sem_post(&resource);       // Last reader unlocks the resource
    }
    sem_post(&read_count_access);  // Release access to read_count
    return NULL;
}

// Function for writers
void* writer(void* arg) {
    int writer_id = *(int*)arg;
    // Writer wants to enter
    sem_wait(&resource);           // Writers need exclusive access to the resource
    printf("Writer %d is writing to the resource\n", writer_id); // Writing section
    sleep(1); // Simulate writing activity
    // Writer is done
    sem_post(&resource);           // Release the resource for others
    return NULL;
}

int main() {
    int num_readers = 5, num_writers = 3;
    sem_init(&resource, 0, 1);           // Binary semaphore for resource access (1 indicates available)
    sem_init(&read_count_access, 0, 1);  // Binary semaphore for read_count access (1 indicates available)
    
    // Create arrays to store reader and writer thread IDs
    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    // Create reader and writer threads
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    // Join reader and writer threads
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }
    // Destroy semaphores
    sem_destroy(&resource);
    sem_destroy(&read_count_access);
    return 0;
}
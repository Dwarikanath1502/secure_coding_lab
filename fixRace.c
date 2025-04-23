#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Shared counter
int counter = 0;

// Mutex for synchronizing access to counter
pthread_mutex_t lock;

void* incrementCounter(void* arg) {
    for (int i = 0; i < 50000; ++i) {
        pthread_mutex_lock(&lock);     // Lock before accessing the shared variable
        int temp = counter;
        usleep(1);                     // Simulate delay
        counter = temp + 1;
        pthread_mutex_unlock(&lock);   // Unlock after updating
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    printf("Expected Final Counter: 100000\n");
    printf("Actual Final Counter: %d\n", counter);

    return 0;
}

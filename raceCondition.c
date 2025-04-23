#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;

void* incrementCounter(void* arg) {
    for (int i = 0; i < 50000; ++i) {
        int temp = counter;
        usleep(1); // Add tiny delay to increase race condition chance
        counter = temp + 1;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Expected Final Counter: 100000\n");
    printf("Actual Final Counter: %d\n", counter);

    return 0;
}

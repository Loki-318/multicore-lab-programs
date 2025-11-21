#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;     
int in = 0;         
int out = 0;        

pthread_mutex_t lock;
pthread_cond_t not_full;
pthread_cond_t not_empty;

void* producer(void* arg) {
    while (1) {
        int item = rand() % 100;  

        pthread_mutex_lock(&lock);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &lock);
        }

        buffer[in] = item;
        printf("Producer produced: %d\n", item);

        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);

        sleep(1); 
    }
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);

        while (count == 0) {
            pthread_cond_wait(&not_empty, &lock);
        }

        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);

        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);

        sleep(2); 
    }
}

int main() {
    pthread_t prod, cons;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}

#include <stdio.h> 
#include <pthread.h> 
#define SIZE 100  
int data[SIZE];  
int found_index = -1; 
pthread_mutex_t lock;  
void* search(void* arg) { 
    int start = *(int*)arg;  
    for (int i = start; i < start + SIZE / 4; i++) { 
        if (data[i] == 50) {  
            pthread_mutex_lock(&lock); 
            found_index = i;  
            pthread_mutex_unlock(&lock); 
            return NULL;  
        } 
    } 
    return NULL;  
} 
int main() { 
    pthread_t threads[4]; 
    int thread_ids[4];  
    for (int i = 0; i < SIZE; i++) { 
        data[i] = i + 1;  
    } 
    pthread_mutex_init(&lock, NULL);  
    for (int i = 0; i < 4; i++) { 
        thread_ids[i] = i * (SIZE / 4); 
        pthread_create(&threads[i], NULL, search, (void*)&thread_ids[i]);  
    } 
    for (int i = 0; i < 4; i++) { 
        pthread_join(threads[i], NULL);  
    } 
    if (found_index != -1) { 
        printf("Number 50 found at index: %d\n", found_index);  
    } else { 
        printf("Number 50 not found.\n"); 
    } 
    pthread_mutex_destroy(&lock); 
    return 0; 
}
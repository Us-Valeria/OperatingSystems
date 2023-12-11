#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

struct portion{
    struct portion* next;
};

struct portion *buffer = NULL;

void* producer(void*);
void* consumer(void*);

pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t buffer_size;
int i;

int main(){    
    sem_init(&buffer_size, 0, 0);
    pthread_t producer_id, consumer_id[3];
    pthread_create(&producer_id, NULL, &producer, NULL);
    for(i = 0; i < 3; i++) pthread_create(&consumer_id[i], NULL, &consumer, NULL);
    pthread_join(producer_id, NULL);
    for(i = 0; i < 3; i++) pthread_join(consumer_id[i], NULL);
    return 0;
}

void* producer(void* params){
    while(1){
        if(i++ > 200) break;
        usleep(100);
        struct portion *new_portion;
        new_portion = (struct portion*)calloc(1, sizeof(struct portion));
        pthread_mutex_lock(&Mutex);
        new_portion->next = buffer;
        buffer = new_portion;
        sem_post(&buffer_size);
        printf("Added to buffer: %p\n", (void*)new_portion);
        pthread_mutex_unlock(&Mutex);
    };
    return 0;
}

void* consumer(void* params){
    while(1){
        struct portion *next_portion;
        sem_wait(&buffer_size);
        pthread_mutex_lock(&Mutex);
        next_portion = buffer;
        buffer = buffer->next;
        pthread_mutex_unlock(&Mutex);
        printf("Removed from buffer: %p\n", (void*)next_portion);
        free(next_portion);
    }
    return 0;
}
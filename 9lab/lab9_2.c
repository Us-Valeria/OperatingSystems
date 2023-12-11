#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

char sh[6];

void* Thread(void* pParams);

int readyFlags[2];
int turn;

void EnterCriticalRegion(int threadId) {
    readyFlags[threadId] = 1;
    turn = 1 - threadId;
    while (turn == 1 - threadId && readyFlags[1 - threadId]);
}

void LeaveCriticalRegion(int threadId) {
    readyFlags[threadId] = 0;
}

int main(void) {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &Thread, NULL);
    while (1) {  
        EnterCriticalRegion(0);
        printf("%s\n", sh);
        LeaveCriticalRegion(0);
        turn = 1;
    }
}

void* Thread(void* pParams) {
    int counter = 0;
    while (1) {
        EnterCriticalRegion(1);
        if (counter % 2) {
            sh[0] = 'H';
            sh[1] = 'e';
            sh[2] = 'l';
            sh[3] = 'l';
            sh[4] = 'o';
            sh[5] = '\0';
        }
        else {
            sh[0] = 'B';
            sh[1] = 'y';
            sh[2] = 'e';
            sh[3] = '_';
            sh[4] = 'u';
            sh[5] = '\0';
        }
        counter++;
        LeaveCriticalRegion(1);
        turn = 0;
    }
    return NULL;
}
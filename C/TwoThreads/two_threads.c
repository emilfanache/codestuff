/*
 * TwoThreads.cpp
 *
 *  Created on: Mar. 13, 2021
 *      Author: Emil Fanache
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char* buffer = NULL;
const int BUFFER_SIZE = 100;

pthread_mutex_t m_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bufferHasData = PTHREAD_COND_INITIALIZER;

void buildBufferData(char** buffer) {
    char start = 'A';
    const int LETTERS_IN_ALPHABET = 26;

    if (!buffer)
        return;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        (*buffer)[i] = start + (i % LETTERS_IN_ALPHABET);
    }

    printf("Buffer data has been written!\n");
}

void* theOneHandler(void* arg) {
    int argId = *((int*)arg);

    printf("theOne started -> tid = %d\n", argId);

    pthread_mutex_lock(&m_lock);

    pthread_cond_wait(&bufferHasData, &m_lock);
    printf("Buffer content is: %s\n", buffer);

    pthread_mutex_unlock(&m_lock);

    printf("theOne ended\n");
    pthread_exit(NULL);
}

void* theOtherHandler(void* arg) {
    int argId = *((int*)arg);
    printf("theOther started -> tid = %d\n", argId);

    pthread_mutex_lock(&m_lock);

    buildBufferData(&buffer);
    pthread_cond_signal(&bufferHasData);

    pthread_mutex_unlock(&m_lock);

    printf("theOther ended\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t theOne;
    pthread_t theOther;
    int status;
    int theOneId = 1234;
    int theOtherId = 5678;
    pthread_attr_t attr;

    buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    if (!buffer) {
        printf("Memory allocation error at line %d\n", __LINE__);
        exit(-1);
    }

    // innit attributes and make the threads joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    status = pthread_create(&theOne, NULL, theOneHandler, (void*)&theOneId);
    if (status > 0) {
        free(buffer);
        printf("Error %d on creating thread: theOne\n", status);
        exit(-1);
    }

    // make sure the thread is running first
    sleep(1);

    status =
        pthread_create(&theOther, NULL, theOtherHandler, (void*)&theOtherId);
    if (status > 0) {
        free(buffer);
        printf("Error %d on creating thread: theOther\n", status);
        exit(-1);
    }

    pthread_attr_destroy(&attr);

    status = pthread_join(theOne, NULL);
    if (status != 0) {
        free(buffer);
        printf("Error %d on joining thread: theOne\n", status);
        exit(-1);
    }

    status = pthread_join(theOther, NULL);
    if (status != 0) {
        free(buffer);
        printf("Error %d on joining thread: theOther\n", status);
        exit(-1);
    }

    printf("Done!\n");

    // terminate current thread but keep all the other going
    pthread_exit(NULL);

    free(buffer);
    return 0;
}

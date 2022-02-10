/**
 * @file ping-pong.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief  Using two threads make a program to print “Ping - Pong” every second to the terminal.
 *         A thread shall print Ping and the other thread shall Pong to the terminal.
 *         Using binary semaphores ensure the right order so that the output
 *         looks like:
 *            Ping - Pong
 *            Ping - Pong
 *            Ping - Pong
 *            ...
 * @version 0.1
 * @date 2021-06-21
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

static void *print_ping(void *); // The ping thread function
static void *print_pong(void *); // The pong thread function

static sem_t ping, pong; // Two semaphores to manage the order

int main(void)
{
    pthread_t ping_thread, pong_thread;
    sem_init(&ping, 0, 1); // Binary semaphore acts like a mutex
    sem_init(&pong, 0, 0); // Binary semaphore acts like a mutex

    // Create and check the ping thread
    if (pthread_create(&ping_thread, NULL, print_ping, NULL))
    {
        printf("Faild to create ping_thread!\n");
        exit(1);
    }

    // Create and check the pong thread
    if (pthread_create(&pong_thread, NULL, print_pong, NULL))
    {
        printf("Faild to create pong_thread!\n");
        exit(1);
    }

    // Wait on the threads to get completed
    pthread_join(ping_thread, NULL);
    pthread_join(pong_thread, NULL);

    // Release the semaphores
    sem_destroy(&ping);
    sem_destroy(&pong);

    return 0;
}

static void *print_ping(void *arg)
{
    (void)arg;

    while (1)
    {
        sleep(1);
        sem_wait(&ping);
        printf("Ping - ");
        sem_post(&pong);
    }

    pthread_exit(NULL); // Exit the thread without a return value
}

static void *print_pong(void *arg)
{
    (void)arg;

    while (1)
    {
        sem_wait(&pong);
        printf("Pong\n");
        sem_post(&ping);
    }

    pthread_exit(NULL); // Exit the thread without a return value
}

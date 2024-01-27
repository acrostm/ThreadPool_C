#include "threadpool.h"

#include <pthread.h>

// Task struct
typedef struct Task
{
    void (*function)(void *arg);
    void *arg;
} Task;

// ThreadPool struct
struct ThreadPool
{
    // Task queue
    Task *taskQ;
    int queueCapacity; // total queue size
    int queueSize;     // current queue size
    int queueFront;    // get from the queue head
    int queueEnd;      // put to queue end

    pthread_t managerID;       // manager thread ID
    pthread_t *threadIDs;      // a list for working thread IDs
    int minNum, maxNum;        // the minimum and maximum thread numbers
    int busyNum;               // number of working threads
    int aliveNum;              // number of the alive threads
    int exitNum;               // number of thread to be destroyed
    pthread_mutex_t mutexPool; // lock the threadpool for operation
    pthread_mutex_t mutexBusy; // lock the busyNum for operation
    pthread_cond_t notFull;    // if the TaskQ full
    pthread_cond_t notEmpty;   // if the TaskQ empty

    int shutdown; // if the threadpool is to be destroyed, 1 for destroy, 0 for not destroy
};

ThreadPool *threadpoolCreate(int min, int max, int queueSize)
{
    ThreadPool *pool = (ThreadPool *)malloc(sizeof(ThreadPool));
    do
    {
        if (pool == NULL)
        {
            printf("malloc threadpoll failed...\n");
            break;
        }

        pool->threadIDs = (pthread_t *)malloc(sizeof(pthread_t) * max);
        if (pool->threadIDs == NULL)
        {
            printf("malloc threadIDs failed...\n");
            break;
        }
        memset(pool->threadIDs, 0, sizeof(pthread_t) * max);

        pool->minNum = min;
        pool->maxNum = max;
        pool->busyNum = 0;
        pool->aliveNum = min;
        pool->exitNum = 0;

        if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
            pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
            pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
            pthread_cond_init(&pool->notFull, NULL) != 0)
        {
            printf("mutex or condition init fail...\n");
            break;
        }

        // Task queue
        pool->taskQ = malloc(sizeof(Task) * queueSize);
        pool->queueCapacity = queueSize;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueEnd = 0;

        pool->shutdown = 0;

        // create thread
        pthread_create(&pool->managerID, NULL, manager, NULL);
        for (int i = 0; i < min; ++i)
        {
            pthread_create(&pool->threadIDs[i], NULL, worker, NULL);
        }

        return pool;
    } while (0);

    // release resource
    if (pool->threadIDs) free(pool->threadIDs);
    if (pool->taskQ) free(pool->taskQ);
    if (pool) free(pool);
    return NULL;
}

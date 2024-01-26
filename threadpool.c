#include "threadpool.h"

#include <pthread.h>

// Task struct
typedef struct Task
{
    void (*function) (void* arg);
    void* arg;
} Task;

// ThreadPool struct
struct ThreadPool
{
    // Task queue
    Task* taskQ;
    int queueCapacity;          // total queue size
    int queueSize;              // current queue size
    int queueFront;             // get from the queue head
    int queueEnd;               // put to queue end

    pthread_t managerID;        // manager thread ID
    pthread_t *threadIDs;       // a list for working thread IDs
    int minNum, maxNum;         // the minimum and maximum thread numbers
    int busyNum;                // number of working threads
    int aliveNum;               // number of the alive threads
    int exitNum;                // number of thread to be destroyed
    pthread_mutex_t mutexPool;  // lock the threadpool for operation
    pthread_mutex_t mutexBusy   // lock the busyNum for operation
    pthread_cond_t notFull;     // if the TaskQ full
    pthread_cond_t notEmpty;    // if the TaskQ empty

    int shutdown;               // if the threadpool is to be destroyed, 1 for destroy, 0 for not destroy
}

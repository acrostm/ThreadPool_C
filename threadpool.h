#ifndef _THREADPOOL_H
#define _THREADPOOL_H

typedef struct ThreadPool ThreadPool;
// create threadpool and initiate
ThreadPool *threadPoolCreate(int min, int max, int queueSize);

// destroy threadpool
int threadPoolDestroy(ThreadPool* pool);

// add task to threadpool
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);

// get the number of working thread
int threadPoolBusyNum(ThreadPool* pool);

// get the number of alive thread
int threadPoolAliveNum(ThreadPool* pool);

//////////
void* worker(void* arg);
void* manager(void* arg);
void threadExit(ThreadPool* pool);

#endif // _THREADPOOL_H

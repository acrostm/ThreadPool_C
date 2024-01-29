#ifndef _THREADPOOL_H
#define _THREADPOOL_H

typedef struct ThreadPool ThreadPool;
// create threadpool and initiate
ThreadPool *threadPoolCreate(int min, int max, int queueSize);

// destroy threadpool

// add task to threadpool

// get the number of working thread

// get the number of alive thread

//////////
void* worker(void* arg);
void* manager(void* arg);
void threadExit(ThreadPool* pool);
#endif // _THREADPOOL_H

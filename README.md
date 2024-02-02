# ThreadPool Project

## Overview

This project is an implementation of a thread pool in C, providing a simple and efficient way to manage and execute tasks concurrently using a pool of worker threads. 

## Features

The thread pool supports the following functions:

### 1. `ThreadPool* threadPoolCreate(int min, int max, int queueSize);`

- Creates a thread pool with the specified minimum and maximum number of threads and a maximum task queue size.
- Parameters:
  - `min`: Minimum number of worker threads.
  - `max`: Maximum number of worker threads.
  - `queueSize`: Maximum size of the task queue.

### 2. `int threadPoolDestroy(ThreadPool* pool);`

- Destroys the thread pool, freeing up allocated resources.
- Parameters:
  - `pool`: Pointer to the thread pool structure.

### 3. `void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);`

- Adds a task to the thread pool for execution.
- Parameters:
  - `pool`: Pointer to the thread pool structure.
  - `func`: Pointer to the function representing the task.
  - `arg`: Argument to be passed to the task function.

### 4. `int threadPoolBusyNum(ThreadPool* pool);`

- Retrieves the number of busy (working) threads in the thread pool.
- Parameters:
  - `pool`: Pointer to the thread pool structure.
- Returns:
  - Number of busy threads.

### 5. `int threadPoolAliveNum(ThreadPool* pool);`

- Retrieves the number of alive (active) threads in the thread pool.
- Parameters:
  - `pool`: Pointer to the thread pool structure.
- Returns:
  - Number of alive threads.

### 6. `void* worker(void* arg);`

- Task function representing the worker thread (consumer thread).
- Parameters:
  - `arg`: Argument (typically a thread pool pointer).

### 7. `void* manager(void* arg);`

- Task function representing the manager thread.
- Parameters:
  - `arg`: Argument (typically a thread pool pointer).

### 8. `void threadExit(ThreadPool* pool);`

- Initiates the exit process for a single thread in the thread pool.
- Parameters:
  - `pool`: Pointer to the thread pool structure.

## Usage

To use the thread pool in your project, follow these steps:

1. Include the `"threadpool.h"` header file in your project.
2. Implement the necessary functionality using the provided functions.
3. Compile your project, linking it with the thread pool implementation.

Replace `taskFunction` with the actual function you want to execute concurrently.

/* Austin Siford
 * absiford@mix.wvu.edu
 * 800083596
 */
 
 /* Nick Trefz 
 * natrefz@mix.wvu.edu
 * 800071978
 */
#ifndef FINAL_THREAD_POOL_H
#define FINAL_THREAD_POOL_H

#include "queue.h"
#include "job.h"
#include <pthread.h>

typedef struct ThreadPool {
	int number_of_workers;
	int is_active;
	Queue* queue;
	pthread_t* workers;
	pthread_attr_t joinable;
} ThreadPool;

#define TRUE 1
#define FALSE 0

ThreadPool* CreateThreadPool(const int num);
void DestroyThreadPool(ThreadPool *pool);
void EnqueueJob(ThreadPool *pool, Job* job);
void ExecuteJobs(ThreadPool* pool);
void* ExecuteSingleJob(void* thread_pool);
int IsThreadPoolActive(ThreadPool *pool);
int GetNumberOfRemainingJobs(ThreadPool *pool);

#endif

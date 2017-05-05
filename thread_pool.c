/* Austin Siford
 * absiford@mix.wvu.edu
 * 800083596
 */
 
 /* Nick Trefz 
 * natrefz@mix.wvu.edu
 * 800071978
 */
#include "job.h"
#include "thread_pool.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

ThreadPool* CreateThreadPool(const int num) {
  if (num < 1) {
    return NULL;
  }
  ThreadPool* pool = (ThreadPool*) malloc(sizeof(struct ThreadPool));
  pool->number_of_workers = num;
  pool->is_active = FALSE;
  pool->queue = CreateQueue();
  pool->workers = (pthread_t*)malloc(sizeof(pthread_t) * num);
  pthread_attr_init(&pool->joinable);
  pthread_attr_setdetachstate(&pool->joinable, PTHREAD_CREATE_JOINABLE);
  return pool;
}

void DestroyThreadPool(ThreadPool* pool) {
  if (!pool) {
    return;
  }
  pool->number_of_workers = 0;
  pool->is_active = FALSE;
  free(pool->workers);
  pool->workers = NULL;
  DestroyQueue(pool->queue);
  pool->queue = NULL;
  pool = NULL;
}

void EnqueueJob(ThreadPool *pool, Job *job) {
  if (!pool || !job) {
    return;
  }
  Enqueue(pool->queue, job);
}

void ExecuteJobs(ThreadPool* thread_pool) {
  if (!thread_pool) {
    return;
  }
  ThreadPool* pool = (ThreadPool*)thread_pool;
  pool->is_active = TRUE;
  int i;
  for (i=0; i<pool->number_of_workers; ++i) {
    
    if (pthread_create(&pool->workers[i],
		       &pool->joinable,
		       &ExecuteSingleJob,
		       pool)) {
      printf("Could not create a thread in ExecuteJobs\n");
      return;
    }
  }
  for (i=0; i<pool->number_of_workers; ++i) {
    pthread_join(pool->workers[i], NULL);
  }
}

void* ExecuteSingleJob(void* thread_pool) {
  if (!thread_pool) {
    return NULL;
  }
  ThreadPool* pool = (ThreadPool*)thread_pool;
  Job* current_job;
  while (GetNumberOfRemainingJobs(pool)) {
    current_job = Dequeue(pool->queue);
    if (current_job) {
      (current_job->job_description)(current_job->input,current_job->output);
    }
    DestroyJob(current_job);
  }
  pthread_exit(NULL);
} 

int IsThreadPoolActive(ThreadPool *pool) {
  if(!pool) {
    return FALSE;
  }
  return pool->is_active;
}

int GetNumberOfRemainingJobs(ThreadPool *pool) {
  if(!pool) {
    return 0;
  }
  if (!pool->queue) {
    return 0;
  }
  return pool->queue->size; 
}

/* Austin Siford
 * absiford@mix.wvu.edu
 *
 */
 
 /* Nick Trefz 
 * natrefz@mix.wvu.edu
 * 800071978
 */
 
#include "job.h"
#include <pthread.h>
#ifndef FINAL_PROJECT_QUEUE_HEADER_H_

#define FINAL_PROJECT_QUEUE_HEADER_H_

typedef struct Queue {
	Job* first;
	int size;
	pthread_mutex_t mutex;
} Queue;

Queue* CreateQueue();
void DestroyQueue();
void Enqueue(Queue* queue, Job* job);
Job* Dequeue(Queue* queue);
int GetQueueSize(Queue* queue);
#endif

/* Austin Siford
 * absiford@mix.wvu.edu
 * 800083596
 */
 
 /* Nick Trefz 
 * natrefz@mix.wvu.edu
 * 800071978
 */

#include "queue.h"
#include <stdlib.h>
#include <string.h>

Queue* CreateQueue(){
	Queue* queue = (Queue*)malloc(sizeof(struct Queue));
	if (!queue) {
		return NULL;
	}
	if (pthread_mutex_init(&(queue->mutex), NULL)) {
		return NULL;
	}
	queue->first = NULL;
	queue->size = 0;
	return queue;
}
void DestroyQueue(Queue* queue) {
	if (!queue) {
		return;
	}
	while (queue->first) {
		Job* temp = queue->first;
		queue-> first = temp->next;
		DestroyJob(temp);
		temp = NULL;
	}
	if (queue->first) {
		free(queue->first);
		queue->first = NULL;
	}
	queue->size = 0;
	queue = NULL;
}
void Enqueue(Queue* queue, Job* job) {
	if (!queue || !job) {
		return;
	}
	pthread_mutex_lock(&(queue->mutex));
	if (queue->size > 0) {
		int i = 1;
		Job* lastjob = queue->first;
		for (i=1; i<queue->size; ++i) {
			lastjob = lastjob->next;
		}
		if (!lastjob) {
			return;
		}
		lastjob->next = job;
	} else {
		queue->first = job;
	}
	queue->size += 1;	
	pthread_mutex_unlock(&(queue->mutex));
}
Job* Dequeue(Queue* queue) {
	if (!queue) {
		return NULL;
	}
	if (!queue->first) {
		return NULL;
	}
	pthread_mutex_lock(&(queue->mutex));
	Job* job_to_return = queue->first;
	queue->first = job_to_return->next;
	queue->size -= 1;
	pthread_mutex_unlock(&(queue->mutex));
	return job_to_return;
}
int GetQueueSize(Queue* queue) {
	if (!queue) {
		return -1;
	}
	pthread_mutex_lock(&(queue->mutex));
	int r = queue->size;
	pthread_mutex_unlock(&(queue->mutex));
	return r;
}

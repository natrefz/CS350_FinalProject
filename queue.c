/* Austin Siford
 * absiford@mix.wvu.edu
 *
 */
 
 /* Nick Trefz 
 * natrefz@mix.wvu.edu
 * 800071978
 */

#include "queue.h"
#include <stdlib.h>
#include <string.h>

Job* CreateJob(char* filename) {
	if (!filename) {
		return NULL;
	}
	Job* job = (Job*)malloc(sizeof(Job));
	strcpy(job->file_name, &filename[0]);
	job->next = NULL;
	return job;
}
void DeleteJob(Job* job) {
	if (!job) {
		return;
	}
	if (job->next) {
		job->next = NULL;
	}
	free(job);
	job = NULL;
}
Queue* CreateQueue(){
	Queue* queue = (Queue*)malloc(sizeof(struct Queue));
	if (!queue) {
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
		DeleteJob(temp);
	}
	if (queue->first) {
		free(queue->first);
		queue->first = NULL;
	}
	free(queue);
	queue = NULL;
}
void Enqueue(Queue* queue, Job* job) {
	if (!queue || !job) {
		return;
	}
	int i = 1;
	Job* lastjob = queue->first;
	for ( ; i<queue->size; ++i) {
		lastjob = lastjob->next;
	}
	if (!lastjob) {
		return;
	}
	lastjob->next = job;
	queue->size += 1;
}
Job* Dequeue(Queue* queue) {
	if (!queue) {
		return NULL;
	}
	Job* job_to_return = queue->first;
	queue->first = job_to_return->next;
	return job_to_return;
}
int GetQueueSize(Queue* queue) {
	if (!queue) {
		return -1;
	}
	return queue->size;
}
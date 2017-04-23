/* Austin Siford
 * absiford@mix.wvu.edu
 *
 */
 
 /* Nick Trefz 
 * natrefz@mix.wvu.edu
 * 800071978
 */
 
#ifndef FINAL_PROJECT_QUEUE_HEADER_H_

#define FINAL_PROJECT_QUEUE_HEADER_H_

typedef struct Job {
	char file_name[255];
	struct Job* next;	
} Job;

typedef struct Queue {
	Job* first;
	int size;
} Queue;

Job* CreateJob(char* filename);
void DeleteJob(Job* job);
Queue* CreateQueue();
void DestroyQueue();
void Enqueue(Queue* queue, Job* job);
int GetQueueSize(Queue* queue);
#endif
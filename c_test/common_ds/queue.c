#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct queue_t_
{
	void **front;
	void **rear;
	unsigned long long size;
}queue_t;


#define queue_isempty(queue) (queue->front == queue->rear)
#define queue_isfull(queue) (((unsigned long long)(queue->rear+sizeof(queue->rear))%queue->size) == queue->front)

int queue_init(queue_t *queue, unsigned long long size)
{
	queue->front = (void**)calloc(size, sizeof(void*));
	if(NULL == queue->front)
	{
		printf("error: calloc failed\n");
		return -1;
	}
	queue->rear = queue->front;
	queue->size = size;
	return 0;	
}

int queue_en(queue_t *queue, void *node)
{
	if(queue_isfull(queue))
	{
		printf("error:queue is full.\n");
		return -1;
	}
	
	*(queue->rear) = node;
	queue->rear = (unsigned long long)( queue->rear + (int)sizeof(queue->rear) ) % queue->size;
	return 0;
}

int queue_de(queue_t *queue, void **node)
{
	if( queue_isempty(queue) )
	{
		printf("error:queue is empty\n");
		return -1;
	}
	
	*node = *(queue->front);
	*(queue->front) = NULL;
	queue->front = (unsigned long long)(queue->front + sizeof(queue->front)) % queue->size;
	return 0;
}

void queuen_free(queue_t *queue)
{
	free(queue->front);
	queue->front = NULL;
	queue->rear  = NULL;
	queue->size  = 0;
}

#if 1
typedef struct student_t_
{
	int number;
	char *name;
	int age;
}student_t;

void print_student(student_t st)
{
	printf("student:%s number[%d] age:%d\n", st.name, st.number, st.age);
}
int main(void)
{
	student_t test[]=
	{
		{1,"zenghua",28},
		{2,"zengtao",27},
		{3,"zengguowu",61},
		{4,"zhangguoqing",50},
		{5,"zengxiumei",30}
	};
	int i = 0;
	int size = sizeof(test)/sizeof(test[0]);
	queue_t student_queue;
	queue_init(&student_queue,size);
	
	student_t *st = NULL;
	for(i=0;i<size;i++)
	{
		queue_en(&student_queue, (void*)&test[i]);		
	}
	for(i=0;i<size;i++)
	{
		queue_en(&student_queue,(void*)&st);
		print_student(*st);
	}
	queuen_free(&student_queue);
	return 0;
}
#endif

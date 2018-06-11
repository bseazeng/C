#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t_
{
	void **base;
	void **top;
	unsigned long long size;
}stack_t;

#define RETURN_OK 0
#define RETURN_ERR 1
#define RETURN_STACK_EMPTY 2

#define stack_maxsize(stack) (stack->size)
#define stack_isempty(stack) (stack->top == stack->base)
#define stack_depth(stack) (stack->top-stack->base)
#define stack_gettop(stack) ((stack->top == stack->base)?NULL:*(stack->top-1))

int stack_init(stack_t *stack, unsigned long long size)
{
	memset(stack, 0, sizeof(stack_t));
	
	stack->base = (void**)calloc(size,sizeof(void*));
	if( NULL == stack->base)
	{
		return RETURN_ERR;
	}
	
	stack->top = stack->base;
	stack->size = size;
	return RETURN_OK;
}

int stack_push(stack_t *stack, void *node)
{
	if( stack->top - stack->base >= stack->size )
	{
		return RETURN_ERR;
	}
	
	*(stack->top) = node;
	stack->top++;
	return RETURN_OK;
}

int stack_pop(stack_t *stack, void **node)
{
	if( stack->top == stack->base)
	{
		return RETURN_STACK_EMPTY;
	}
	stack->top--;
	*node = *(stack->top);
	*(stack->top) = NULL;
	return RETURN_OK;
}

void stack_free(stack_t *stack)
{
	free(stack->base);
	stack->base = NULL;
	stack->top = NULL;
	stack->size = 0;
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
	stack_t student_stack;
	stack_init(&student_stack,size);
	
	student_t *st = NULL;
	for(i=0;i<size;i++)
	{
		stack_push(&student_stack, (void*)&test[i]);		
	}
	for(i=0;i<size;i++)
	{
		stack_pop(&student_stack,(void*)&st);
		print_student(*st);
	}
	stack_free(&student_stack);
	return RETURN_OK;
}
#endif

/*队列（queue)*/
/*链表实现*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
typedef int Item;
typedef struct queue_type* Queue;
 
struct node                        /*队列元素*/
{
	Item val;
	struct node* next;
};
struct queue_type                  /*队首指针与队尾指针*/
{
	struct node* first;
	struct node* last;
};
 
 
/**************************************************
* 辅助函数：
*       1.错误处理
*       2.判断队列是否为空
*
***************************************************/
 
//1.错误处理
static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
 
//2.判断队列是否为空
bool is_empty(Queue q)
{
	if (q->first == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 
/**********************************************************
* 队列的操作：
*         1.构建新队列
*         2.入队
*         3.搜索
*         4.出队
*         5.清空队列
*         6.破坏队列
*
***********************************************************/
 
//1.构建新队列
Queue create(void)
{
	Queue q = malloc(sizeof(struct queue_type));
	if (q == NULL)
	{
		terminate("Error: malloc failed in create.");
	}
 
	q->first = q->last = NULL;
	return q;
}
 
//2.入队
void enqueue(Queue q, Item n)
{
	struct node* new_node = malloc(sizeof(struct node));
	if (new_node==NULL)
	{
		terminate("Error: malloc failed in enqueue.");
	}
 
	new_node->val = n;
	new_node->next = NULL;
	if (is_empty(q) == true)                   /*空队列*/
	{
		q->first = q->last = new_node;
	}
	else                                       /*队列不为空*/
	{
		q->last->next = new_node;
		q->last = new_node;
	}
}
 
//3.搜索
struct node* search(Queue q, Item n)
{
	struct node* p;
 
	for (p = q->first; p != NULL; p=p->next)
	{
		if (p->val == n)
		{
			return p;
		}
	}
 
	return NULL;                        /*n没有找到*/
}
 
//4.出队
Item dequeue(Queue q)
{
	struct node* old_first;
	Item n;
 
	if (is_empty(q)==true)
	{
		terminate("Error in dequeue: queue is empty.");
	}
 
	old_first = q->first;
	n = old_first->val;
	if (q->first == q->last)             /*队列中只有一个元素*/
	{
		q->first = q->last = NULL;
	}
	else                                 /*队列中有两个及以上的元素*/
	{
		q->first = q->first->next;
	}
	free(old_first);
	return n;
}
 
//5.清空队列
void make_empty(Queue q)
{
	while (is_empty(q) == false)
	{
		pop(q);
	}
}
 
//6.破坏队列
void destroy(Queue q)
{
	make_empty(q);
	free(q);
}

/*栈（stack)*/
/*链表实现*/
 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
typedef int Item;
typedef struct stack_type* Stack;
 
struct node                   /*栈元素*/
{
	Item val;
	struct node* next;
};
struct stack_type             /*栈顶指针*/
{
	struct node* top;
};
 
/**************************************************
* 辅助函数：
*       1.错误处理
*       2.判断栈是否为空
*
****************************************************/
 
//1.错误处理
static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
 
//2.判断栈是否为空
bool is_empty(Stack s)
{
	if (s->top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 
/************************************************
* 栈的操作：
*       1.构建新栈
*       2.压栈
*       3.搜索
*       4.返回栈顶元素
*       5.出栈
*       6.清空栈
*       7.破坏栈
*
**************************************************/
 
//1.构建新栈
Stack create(void)
{
	Stack s = malloc(sizeof(struct stack_type));
	if (s == NULL)
	{
		printf("Error: malloc failed in create.\n");
		exit(EXIT_FAILURE);
	}
 
	s->top = NULL;
	return s;                      /*返回栈顶指针*/
}
 
//2.压栈
void push(Stack s, Item n)
{
	struct node* new_node = malloc(sizeof(struct node));
	if (new_node == NULL)
	{
		terminate("Error: malloc failed in push.");
	}
 
	new_node->val = n;
	new_node->next = s->top;
	s->top = new_node;
}
 
//3.搜索
struct node* search(Stack s, Item n)
{
	while (s->top != NULL)
	{
		if (s->top->val == n)
		{
			return s->top;
		}
		else
		{
			s->top = s->top->next;
		}
	}
 
	return NULL;                      /*n没有找到*/
}
 
//4.返回栈顶元素
Item top(Stack s)
{
	return s->top->val;
}
 
//5.出栈
Item pop(Stack s)
{
	struct node* old_top;
	Item n;
 
	if (is_empty(s) == true)
	{
		terminate("Error in pop: stack is empty.");
	}
 
	old_top = s->top;
	n = old_top->val;
	s->top = old_top->next;
	free(old_top);
	return n;
}
 
//6.清空栈
void make_empty(Stack s)
{
	while (is_empty(s) == true)
	{
		pop(s);
	}
}
 
//7.破坏栈
void destroy(Stack s)
{
	make_empty(s);
	free(s);
}

/*单链表(single linked list)*/
 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
struct node                    /*结点结构的描述*/
{
	int val;
	struct node* next;
};
 
struct node* first = NULL;     /*first指针始终指向链表的第一个结点，
							  把first初始化为NULL表示链表初始为空*/
 
 
/***************************************************
*链表的两个基本操作：
* 1.遍历链表，搜索n
* 2.判断链表是否为空
* 
****************************************************/
 
//1.遍历链表，搜索n
struct node* search_list(struct node* list, int n)
{
	struct node* p;
 
	for (p = list; p != NULL; p = p->next)
	{
		if (p->val == n)
		{
			return p;
		}
	}
 
	return NULL;
}
 
//2.判断链表是否为空
bool is_empty(struct node* list)
{
	if (list == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 
/*******************************************************************
 *插入：                                                
 *    1.在表头插入结点                                   
 *    2.在表尾插入结点                                   
 *    3.在指定结点前插入结点                              
 *函数调用： 
 *    1,2:
 *       first = add_to_list(first, 10);
 *		 3:
 *       first = add_to_list(first, 20, 30);
 *
 * 因为首结点有可能发生变化，所以需要更新指向原链表首结点的指针first,
 * 但因为C语言函数的“传值调用”，在函数内对list的改变无法影响到函数外
 * 的first,用add_to_list函数的返回值（更新后的list）直接更新first就
 * 可以解决
 *    
 *******************************************************************/
 
//1.在表头插入结点
struct node* add_to_list(struct node* list, int n)
{
	struct node* new_node;
 
	new_node = malloc(sizeof(struct node));
	if (new_node == NULL)
	{
		printf("Error: malloc failed in add_to_list.\n");
		exit(EXIT_FAILURE);
	}
	
	new_node->val = n;
	new_node->next = list;
	return new_node;
}
 
//2.在表尾插入结点
struct node* add_to_list(struct node* list, int n)
{
	struct node* last, * old_last;
 
	last = malloc(sizeof(struct node));
	if (last == NULL)
	{
		printf("Error: malloc fialed in add_to_list.\n");
		exit(EXIT_FAILURE);
	}
 
	last->val = n;
	last->next = NULL;
 
	if (is_empty(list) == true)                               /*空链表的情况*/
	{
		return last;
	}
	else                                                      /*非空链表的情况*/
	{
		for (old_last = list;
			old_last != NULL && old_last->next != NULL;
			old_last = old_last->next)
			;
		old_last->next = last;
		return list;
	}
}
 
//3.在指定结点前插入一个新结点
struct node* add_to_list(struct node* list, int m, int n)
{
	struct node* cur, * prev, * new_node;
 
	new_node = malloc(sizeof(struct node));
	if (new_node == NULL)
	{
		printf("Error: malloc failed in add_to_list.\n");
		exit(EXIT_FAILURE);
	}
 
	for (cur = list, prev = NULL;
		cur != NULL && cur->val != m;
		prev = cur, cur = cur->next)
		;
 
	if (cur == NULL)                      /*链表为空或m没有找到*/
	{
		printf("%d was not found.\n", m);
		return list;
	}
	else if (prev == NULL)                /*m为首结点的情况*/
	{
		new_node->val = n;
		new_node->next = list;
		return new_node;
	}
	else                                  /*m不为首结点的情况*/
	{
		new_node->val = n;
		prev->next = new_node;
		new_node->next = cur;
		return list;
	}
}
 
/****************************************************************
 *删除：
 *    1.从表头删除结点
 *    2.从表尾删除结点
 *    3.删除指定结点    
 *函数调用：
 *    1，2：
          first = delete_from_list(first);
         3：
		  first = delete_from_list(first，10);
 * 原理同add_to_list
 *
 *****************************************************************/
 
//1.从表头删除结点
struct node* delete_from_list(struct node* list)
{
	struct node* old_frist;
 
	if (is_empty(list) == true)
	{
		printf("List is empty.\n");
		exit(EXIT_FAILURE);
	}
 
	old_frist = list;
	list = list->next;
	free(old_frist);
 
	return list;
}
 
//2.从表尾删除结点
struct node* delete_from_list(struct node* list)
{
	struct node* cur, * prev;
 
	if (is_empty(list) == true)
	{
		printf("List is empty.\n");
		exit(EXIT_FAILURE);
	}
 
	for (cur = list, prev = NULL;
		cur != NULL && cur->next != NULL;
		prev = cur, cur = cur->next)
		;
 
	if (prev == NULL)               /*只有一个结点的情况*/
	{
		list = list->next;
	}
	else                            /*有两个及以上的结点*/
	{
		prev->next = NULL;
	}
	free(cur);
	return list;
}
 
//3.删除指定结点
struct node* delete_from_list(struct node* list, int n)
{
	struct node* cur, * prev;
 
	if (is_empty(list) == true)
	{
		printf("List is empty.\n");
		exit(EXIT_FAILURE);
	}
 
	for (cur = list, prev = NULL;
		cur != NULL && cur->val != n;
		prev = cur, cur = cur->next)
		;
 
	if (cur == NULL)                          /*找不到n的情况*/
	{
		printf("%d was not found.\n", n);
		return list;
	}
	else if (prev == NULL)                    /*只有一个结点的情况*/
	{
		list = list->next;
	}
	else                                      /*有两个及以上结点的情况*/
	{
		prev->next = cur->next;
	}
	free(cur);
	return list;
}

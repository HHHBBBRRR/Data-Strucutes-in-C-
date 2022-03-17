/*散列表（hash table)*/
/*分离链接法*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

#define MAX_SIZE 1000

typedef int Item;
typedef struct node* Position;
typedef struct hash_table* Hash;

struct node
{
	Item val;
	struct node* next;
};

struct hash_table
{
	int size;
	struct node* list;
};

/*******************************************
* 辅助函数：
*       1.错误处理函数
*       2.求下一个素数函数
*       3.哈希函数
*
********************************************/

//1.错误处理函数
static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

//2.求下一个素数函数
static int next_prime(int n)
{
	int i, p = (n % 2) ? n + 2 : n + 1;

	while (p <= MAX_SIZE)
	{
		for (i = (int)sqrt(p); i > 2; i--)
		{
			if (!(p % i))
			{
				break;
			}
		}
		if (i == 2)
		{
			break;
		}
		else
		{
			p += 2;
		}
	}

	return p;
}

//3.哈希函数
static Item hash_function(int size, Item n)
{
	return n % size;
}

/****************************************************************
* 哈希表基本操作：
*          1.构造哈希表
*          2.查找
*          3.插入
*          4.删除
*          5.破坏哈希表
*
*****************************************************************/

//1.构造哈希表
Hash create(int size)
{
	Hash h = malloc(sizeof(struct hash_table));
	if (h == NULL)
	{
		terminate("Error: malloc failed in create.");
	}

	h->size = next_prime(size);
	h->list = malloc(h->size * sizeof(struct node));
	if (h->list == NULL)
	{
		terminate("Error: malloc failed in create.");
	}

	for (int i = 0; i < h->size; i++)            /*初始化表头，将表头元素的值设为0*/
	{
		h->list[i].val = 0;
		h->list[i].next = NULL;
	}

	return h;
}

//2.查找
bool find(Hash h, Item n)
{
	int pos;
	Position curr;

	pos = hash_function(h->size, n);
	curr = h->list[pos].next;
	while (curr != NULL && curr->val != n)
	{
		curr = curr->next;
	}

	if (curr == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//3.插入
void insert(Hash h, Item n)
{
	if (find(h, n) == false)
	{
		int pos;
		Position new_node;

		pos = hash_function(h->size, n);
		new_node = malloc(sizeof(struct node));
		if (new_node == NULL)
		{
			terminate("Error: malloc failed in insert.");
		}

		new_node->val = n;
		new_node->next = h->list[pos].next;
		h->list[pos].next = new_node;
	}
	/*如果find(h, n) == true，说明n已经在散列表中，那么我们什么都不做*/
}

//4.删除
void delete(Hash h, Item n)
{
	if (find(h, n) == true)
	{
		int pos;
		Position curr, next_node;

		pos = hash_function(h->size, n);
		curr = h->list[pos].next;
		next_node = curr->next;

		if (curr->val == n)
		{
			h->list[pos].next = curr->next;
			free(curr);
		}
		else
		{
			while (next_node->val != n)
			{
				curr = next_node;
				next_node = next_node->next;
			}
			curr->next = next_node->next;
			free(next_node);
		}
	}
	/*如果find(h, n) == false，说明n不在散列表中，那么我们什么都不做*/
}

//5.破坏哈希表
void destroy(Hash h)
{
	for (int i = 0; i < h->size; i++)
	{
		while (h->list[i].next != NULL)
		{
			Position prev, curr;

			for (prev = h->list[i].next, curr = prev->next;
				curr != NULL && curr->next != NULL;
				prev = curr, curr = curr->next)
				;
			if (curr != NULL)
			{
				prev->next = NULL;
				free(curr);
			}
			else
			{
				h->list[i].next = NULL;
				free(prev);
			}
		}
	}

	free(h);
}

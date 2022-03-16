#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

static void terminate(const char* message)
{
	printf("%s", message);
	exit(EXIT_FAILURE);
}

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

static Item hash_function(int size, Item n)
{
	return n % size;
}

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

	for (int i = 0; i < h->size; i++)
	{
		h->list[i].val = 0;
		h->list[i].next = NULL;
	}

	return h;
}

Position find(Hash h, Item n)
{
	Position curr;
	int pos;

	pos = hash_function(h->size, n);
	curr = h->list[pos].next;
	while (curr != NULL && curr->val != n)
	{
		curr = curr->next;
	}

	return curr;
}

void insert(Hash h, Item n)
{
	if (find(h, n) == NULL)
	{
		int pos;
		Position new_node;

		pos = hash_function(h->size, n);
		if (new_node==NULL)
		{
			terminate("Error: malloc failed in insert.");
		}

		new_node->val = n;
		new_node->next = h->list[pos].next;
		h->list[pos].next = new_node;
	}
	//如果pos != NULL,说明n已经在散列表中，那么我们什么都不做
}

void delete(Hash h, Item n)
{
	Position old_node = find(h, n);
	if (old_node!=NULL)
	{
		Position curr;
		int pos;

		pos = hash_function(h->size, n);
		curr= h->list[pos].next;
		while (curr!=old_node)
		{

		}


	}
	//如果pos == NULL,说明n不在散列表中，那么我们什么都不做
}

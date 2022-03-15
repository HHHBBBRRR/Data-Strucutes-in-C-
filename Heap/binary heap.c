/*堆(heap)*/
/*以最大堆为例*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_DATE 1000

typedef int Item;
typedef struct heap_type* Heap;

struct heap_type             /*堆的声明*/
{
	int capacity;
	int size;
	Item* elements;
};

//辅助函数：错误处理函数
static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

/****************************************************
* 堆的基本操作：
*           1.创建新堆
*           2.判断堆是否为空
*           3.判断堆是否为满
*           4.插入元素
*           5.建造堆 
*           6.更新键值
*           7.删除最大元素
*           8.删除指定元素
*
*****************************************************/

//1.创建新堆
Heap create(int max_size)
{
	Heap h = malloc(sizeof(struct heap_type));
	if (h == NULL)
	{
		terminate("Error: malloc failed in create.");
	}

	h->elements = malloc((max_size + 1) * sizeof(Item));  /*因为堆从elements[1]开始储存元素，故max_size + 1*/
	if (h->elements == NULL)
	{
		terminate("Out of space.");
	}

	h->capacity = max_size;
	h->size = 0;
	h->elements[0] = MAX_DATE;                            /*elements[0]定义为比所有元素都大的“哨兵”*/

	return h;
}

//2.判断堆是否为空
bool is_empty(Heap h)
{
	if (h->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//3.判断堆是否为满
bool is_full(Heap h)
{
	if (h->size == h->capacity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//4.插入元素
void insert(Heap h, Item val)
{
	if (is_full(h) == true)
	{
		terminate("Error in insert: heap is full.");
	}

	(h->size)++;
	int i = h->size;
	while (h->elements[i / 2] < val)              /*不断上滤*/
	{
		h->elements[i] = h->elements[i / 2];
		i /= 2;
	}
	h->elements[i] = val;
}

//5.建造堆                               /*O（N）*/
void build(Heap h)                      /*假设这时候堆为空*/
{
	printf("Enter size of heap: ");
	scanf_s("%d", &h->size);
	printf("Enter your date: ");        
	for (int i = 1; i <= h->size; i++)
	{
		scanf_s("%d", &h->elements[i]);
	}

	for (int i = h->size / 2; i > 0; i--)      /*从堆中最后一个父节点开始*/
	{
		int parent, child;
		Item temp = h->elements[i];

		for (parent = i; parent * 2 <= h->size; parent = child)
		{
			child = parent * 2;
			if (child != h->size && h->elements[child + 1] > h->elements[child])
			{
				child++;
			}

			if (temp >= h->elements[child])
			{
				break;
			}
			else
			{
				h->elements[parent] = h->elements[child];
			}
		}
		h->elements[parent] = temp;
	}
	/*还有一种方法，即不断调用insert函数，此时O(N log N)*/
}

//6.更新键值
void update_key(Heap h, int n, Item val)
{
	int parent, child;
	Item temp;

	if (n > h->size || n < 1)
	{
		terminate("Error in update_key.");
	}

	if (h->elements[n] < val)                /*值变大，需要不断上滤*/
	{
		h->elements[n] = val;

		for (parent = n / 2, child = n;
			parent > 0;
			parent /= 2, child /= 2)
		{
			temp = h->elements[parent];

			if (h->elements[parent] >= h->elements[child])
			{
				break;
			}
			else
			{
				h->elements[parent] = h->elements[child];
				h->elements[child] = temp;
			}
		}
	}
	else if (h->elements[n] > val)                  /*值变小，需不断下滤*/
	{
		h->elements[n] = val;

		for (parent = n, child = n * 2;
			parent * 2 <= h->size;
			parent = child, child = parent * 2)
		{
			temp = h->elements[parent];

			if (child != h->size && h->elements[child + 1] > h->elements[child])
			{
				child++;
			}

			if (h->elements[parent] >= h->elements[child])
			{
				break;
			}
			else
			{
				h->elements[parent] = h->elements[child];
				h->elements[child] = temp;
			}
		}
	}
	/*还有一种情况：h->elements[n] == val，这时什么都不做*/
}

//7.删除最大元素
Item delete_max(Heap h)
{
	int child, parent;
	Item max_element, temp;

	if (is_empty(h) == true)
	{
		terminate("Error in delete_max: heap is empty.");
	}

	max_element = h->elements[1];
	temp = h->elements[h->size];
	(h->size)--;

	for (parent = 1; parent * 2 <= h->size; parent = child)
	{
		child = parent * 2;
		if (child != h->size && h->elements[child + 1] > h->elements[child])
		{
			child++;
		}

		if (temp >= h->elements[child])
		{
			break;
		}
		else
		{
			h->elements[parent] = h->elements[child];
		}
	}
	h->elements[parent] = temp;

	return max_element;
}

//8.删除指定元素
void delete(Heap h, int n)
{
	if (n > h->size || n < 1)
	{
		terminate("Error in delete");
	}

	update_key(h, n, MAX_DATE);
	delete_max(h);
}

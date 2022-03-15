/*哈希表（hash table)*/
/*开放定址法*/
 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
 
#define MAX_SIZE 1000
 
typedef int Item;
typedef enum { Legitimate, Empty, Deleted } Entry_type;
typedef struct hash_entry Cell;
typedef struct hash_table* Hash;
 
struct hash_entry
{
	Item val;
	Entry_type info;
};
 
struct hash_table
{
	int size;
	Cell* cells;
};
 
/*******************************************
* 辅助函数：
*       1.错误处理函数
*       2.求下一个素数函数
*       3.哈希函数
*       4.第二个哈希函数
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
 
//4.第二个哈希函数
static Item hash_function_two(Item r, int n)     /*用于双散列法*/
{
	return r - (n % r);
}
 
/****************************************************************
* 哈希表基本操作：
*          1.构造哈希表
*          2.查找
*          3.插入
*          4.删除
*          5.再散列
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
	h->cells = malloc(h->size * sizeof(Cell));
	if (h->cells == NULL)
	{
		terminate("Error: malloc failed in create.");
	}
 
	for (int i = 0; i < h->size; i++)
	{
		h->cells[i].info = Empty;
	}
 
	return h;
}
 
//2.查找
 
//2.1线性探测法
int find(Hash h, Item n)
{
	int curr_pos, new_pos, coll_num;
 
	coll_num = 0;
	curr_pos = new_pos = hash_function(h->size, n);
 
	while (h->cells[new_pos].info != Empty && h->cells[new_pos].val != n)
	{
		coll_num++;
		new_pos = curr_pos + coll_num;
		while (new_pos >= h->size)
		{
			new_pos -= h->size;
		}
	}
 
	return new_pos;
}
 
//2.2平方探测法
int find(Hash h, Item n)
{
	int curr_pos, new_pos, coll_num;
 
	coll_num = 0;
	curr_pos = new_pos = hash_function(h->size, n);
 
	while (h->cells[new_pos].info != Empty && h->cells[new_pos].val != n)
	{
		coll_num++;
		if (coll_num % 2 != 0)
		{
			new_pos = curr_pos + ((coll_num + 1) / 2 * (coll_num + 1) / 2);
			while (new_pos >= h->size)
			{
				new_pos -= h->size;
			}
		}
		else
		{
			new_pos = curr_pos - (coll_num / 2 * coll_num / 2);
			while (new_pos < 0)
			{
				new_pos += h->size;
			}
		}
	}
 
	return new_pos;
}
 
//2.3双散列法
int find(Hash h, Item n)
{
	int r = 7;                         /*r为小于h->size的素数，最好是h->size的上一个素数，这里取7*/
	int curr_pos, new_pos, coll_num;
 
	coll_num = 0;
	curr_pos = new_pos = hash_function(h->size, n);
 
	while (h->cells[new_pos].info != Empty && h->cells[new_pos].val != n)
	{
		coll_num++;
		new_pos = curr_pos + (coll_num * hash_function_two(r, n));
		while (new_pos >= h->size)
		{
			new_pos -= h->size;
		}
	}
 
	return new_pos;
}
 
//3.插入
void insert(Hash h, Item n)
{
	int pos = find(h, n);
 
	if (h->cells[pos].info != Legitimate)
	{
		h->cells[pos].val = n;
		h->cells[pos].info = Legitimate;
	}
	else
	{
		terminate("Error: hash table is full.");
	}
}
 
//4.删除                            
void delete(Hash h, Item n)
{
	int pos = find(h, n);
 
	if (h->cells[pos].info == Legitimate)
	{
		h->cells[pos].info = Deleted;              /*懒惰删除*/
	}
	else
	{
		return;                                    /*找不到n*/
	}
}
 
//5.再散列
Hash rehash(Hash h)
{
	Hash new_hash = create(2 * h->size);           /*新哈希表至少是老哈希表两倍大*/
 
	for (int i = 0; i < h->size; i++)
	{
		if (h->cells[i].info == Legitimate)
		{
			insert(new_hash, h->cells[i].val);
		}
	}
 
	free(h);
	return new_hash;
}

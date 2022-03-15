//二叉查找树(binary search tree)
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
typedef int Item;
typedef struct node* Tree;
 
struct node                  /*树结点的定义*/
{
	Item val;
	struct node* left;
	struct node* right;
};
 
//辅助函数：错误处理函数
static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
 
/***************************************************
* 二叉查找树的操作：
*              1.创建新树
*              2.插入
*              3.查找
*              4.找最小元素
*              5.找最大元素
*              6.删除
*              7.清空树     
*
****************************************************/
 
//1.创建新树
Tree create(void)
{
	Tree t = malloc(sizeof(struct node));
	if (t == NULL)
	{
		terminate("Error: malloc failed in create.");
	}
 
	t = NULL;
	return t;
}
 
//2.插入
Tree insert(Tree t, Item n)
{
	if (t == NULL)
	{
		t = malloc(sizeof(struct node));
		if (t == NULL)
		{
			terminate("Error: malloc failed in insert.");
		}
 
		t->val = n;
		t->left = NULL;
		t->right = NULL;
	}
	else if (n < t->val)
	{
		t->left = insert(t->left, n);
	}
	else if (n > t->val)
	{
		t->right = insert(t->right, n);
	}
	/*如果n=t->val,说明n已经在树里面了，那么什么都不做*/
 
	return t;          /*不要忘记返回t*/
}
 
/****************************************
* 递归实现：
*       3.查找
*       4.找最小元素
*       5.找最大元素
*
*****************************************/
 
//3.查找
Tree find(Tree t, Item n)
{
	if (t == NULL)               /*1:树为空*/
	{                            /*2:树不为空，但n不在树中*/
		return NULL;
	}
 
	if (n < t->val)
	{
		return find(t->left, n);
	}
	else if (n > t->right)
	{
		return find(t->right, n);
	}
	else
	{
		return t;
	}
}
 
//4.找最小元素
Tree find_min(Tree t)
{
	if (t == NULL)           /*如果树为空，返回NULL*/
	{
		return NULL;
	}
	else if (t->left == NULL)
	{
		return t;
	}
	else
	{
		return find_min(t->left);
	}
}
 
//5.找最大元素
Tree find_max(Tree t)
{
	if (t == NULL)            /*如果树为空，返回NULL*/
	{
		return NULL;
	}
	else if (t->right == NULL)
	{
		return t;
	}
	else
	{
		return find_max(t->right);
	}
}
/****************************************
* 迭代实现：
*       3.查找
*       4.找最小元素
*       5.找最大元素
*
*****************************************/
 
//3.查找
Tree find(Tree t, Item n)
{
	while (t != NULL)
	{
		if (n < t->val)
		{
			t = t->left;
 
		}
		else if (n > t->val)
		{
			t = t->right;
		}
		else
		{
			return t;
		}
	}
 
	return NULL;                 
}
 
//4.找最小元素
Tree find_min(Tree t)
{
	if (t == NULL)
	{
		return NULL;             
	}
	while (t->left != NULL)
	{
		t = t->left;
	}
	return t;
}
 
//5.找最大元素
Tree find_max(Tree t)
{
	if (t == NULL)
	{
		return NULL;            
	}
	while (t->right != NULL)
	{
		t = t->right;
	}
	return t;
}
 
//6.删除
Tree delete(Tree t, Item n)
{
	if (t == NULL)             /*1.树为空*/	                        						   
	{                          /*2.树不空但n不在树中*/
		return NULL;              
	}
	else if (n < t->val)
	{
		t->left = delete(t->left, n);
	}
	else if (n > t->val)
	{
		t->right = delete(t->right, n);
	}
	else                       /*找到n了,下面进行删除操作*/
	{
		Tree temp = malloc(sizeof(struct node));
		if (t->left != NULL && t->right != NULL)       /*n有两个儿子*/
		{
			temp = find_min(t->right);                 /*用该结点右子树中最小的数据代替其数据并递归地删除那个结点*/
			t->val = temp->val;                        
			t->right = delete(t->right, t->val);
			//也可以用该结点左子树中最大的数据代替其数据并递归地删除那个结点，如下：
			//temp = find_max(t->left);
			//t->val = temp->val;
			//t->left = delete(t->left, t->val);
		}
		else
		{
			temp = t;
			if (t->left != NULL)                      /*n只有左儿子*/
			{
				t = t->left;
			}
			else if (t->right != NULL)                /*n只有右儿子*/
			{
				t = t->right;
			}
			else                                      /*n没有儿子*/
			{
				t = NULL;
			}
			free(temp);
		}
	}
 
	return t;
}
 
//7.清空树
Tree make_empty(Tree t)
{
	if (t != NULL)
	{
		make_empty(t->left);
		make_empty(t->right);
		free(t);
	}
	return NULL;
}
 
int main(void)
{
	Tree t1 = create();      /*注意：当t1调用这三个函数时，一定要用返回值“更新”t1，不然t1是不会改变的*/
	t1 = insert(t1, 2);
	t1 = delete(t1, 2);
	t1 = make_empty(t1);
}

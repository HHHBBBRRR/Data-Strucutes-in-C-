#include<stdio.h>
#include<stdlib.h>
 
typedef int Item;
typedef struct node* Tree;
 
struct node                    /*AVL树结点定义*/
{
	Item val;
	int height;
	struct node* left;
	struct node* right;
};
 
/*******************************************************
* 辅助函数：
*       1.错误处理
*       2.找最小元素
*       3.找最大元素
*
********************************************************/
 
//1.错误处理
static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
 
//2.找最小元素
Tree find_min(Tree t)
{
	if (t == NULL)               /*如果树为空，返回NULL*/
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
 
//3.找最大元素
Tree find_max(Tree t)
{
	if (t == NULL)              /*如果树为空，返回NULL*/
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
 
/************************************************************
* AVL树的操作：
*          1.结点高度
*          2.单左旋
*          3.单右旋
*          4.双左旋
*          5.双右旋
*          6.插入
*          7.删除
* 注：
*   1.Tree create(void)
*	2.Tree find(Tree t, Item n)
*	3.Tree find_min(Tree t)
*	4.Tree find_max(Tree t)
*	5.Tree make_empty(Tree t)
*   在AVL树中，这五个函数与二叉查找树的操作完全一样，
*	所以这里不再列出
*
*************************************************************/
 
//1.结点高度
int height(Tree t)
{
	if (t == NULL)
	{
		return -1;
	}
	else
	{
		return t->height;
	}
}
 
//2.单左旋
Tree single_rotate_with_left(Tree t)                         /*1.对root的右儿子的右子树进行一次插入*/
{                                                            /*2.对root的左儿子的右子树进行一次删除*/
	Tree new_root;
 
	new_root = t->right;
	t->right = new_root->left;
	new_root->left = t;
 
	t->height = max(height(t->left), height(t->right)) + 1;
	new_root->height = max(t->height, height(new_root->right)) + 1;
 
	return new_root;
}
 
//3.单右旋
Tree single_rotate_with_right(Tree t)                       /*1.对root的左儿子的左子树进行一次插入*/
{                                                           /*2.对root的右儿子的左子树进行一次删除*/
	Tree new_root;
 
	new_root = t->left;
	t->left = new_root->right;
	new_root->right = t;
 
	t->height = max(height(t->left), height(t->right)) + 1;
	new_root->height = max(height(new_root->left), t->height) + 1;
 
	return new_root;
}
 
//4.双左旋
Tree double_rotate_with_left(Tree t)                        /*对root的右儿子的左子树进行一次插入*/
{                                                           
	t->right = single_rotate_with_right(t->right);
	return single_rotate_with_left(t);
}
 
//5.双右旋
Tree double_rotate_with_right(Tree t)                       /*对root的左儿子的右子树进行一次插入*/
{
	t->left = single_rotate_with_left(t->left);
	return single_rotate_with_right(t);
}
 
//6.插入
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
		t->height = 0;
		t->left = t->right = NULL;
	}
	else if (n < t->val)
	{
		t->left = insert(t->left, n);
 
		if (height(t->left) - height(t->right) == 2)
		{
			if (n < t->left->val)
			{
				t = single_rotate_with_right(t);
			}
			else
			{
				t = double_rotate_with_right(t);
			}
		}
	}
	else if (n > t->val)
	{
		t->right = insert(t->right, n);
 
		if (height(t->right) - height(t->left) == 2)
		{
			if (n > t->right->val)
			{
				t = single_rotate_with_left(t);
			}
			else
			{
				t = double_rotate_with_left(t);
			}
		}
	}
	/*如果n=t->val,说明n已经在树里面了，那么什么都不做*/
 
	t->height = max(height(t->left), height(t->right)) + 1;         /*不要忘记更新结点高度*/
	return t;
}
 
//7.删除
Tree delete(Tree t, Item n)
{
	if (t == NULL)                      /*1.树为空*/
	{                                   /*2.树不空但n不在树中*/
		return NULL;
	}
	else if (n < t->val)
	{
		t->left = delete(t->left, n);
 
		if (height(t->right) - height(t->left) == 2)
		{
			if (n < t->val)
			{
				t = single_rotate_with_left(t);
			}
			else
			{
				t = double_rotate_with_left(t);
			}
		}
	}
	else if (n > t->val)
	{
		t->right = delete(t->right, n);
 
		if (height(t->left) - height(t->right) == 2)
		{
			if (n > t->val)
			{
				t = single_rotate_with_right(t);
			}
			else
			{
				t = double_rotate_with_right(t);
			}
		}
	}
	else
	{
		Tree temp;
 
		if (t->left != NULL && t->right != NULL)
		{
			if (height(t->left) >= height(t->right))
			{
				temp = find_max(t->left);
				t->val = temp->val;
				t->left = delete(t->left, t->val);
			}
			else
			{
				temp = find_min(t->right);
				t->val = temp->val;
				t->right = delete(t->right, t->val);
			}
		}
		else
		{
			temp = t;
			if (t->left != NULL)
			{
				t = t->left;
			}
			else if (t->right != NULL)
			{
				t = t->right;
			}
			else
			{
				t = NULL;
			}
			free(temp);
		}
	}
 
	if (t != NULL)
	{
		t->height = max(height(t->left), height(t->right)) + 1;
	}
 
	return t;
}

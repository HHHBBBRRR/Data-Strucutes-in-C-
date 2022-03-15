#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
typedef struct node* Tree;
 
struct node
{
	int val;
	struct node* left;
	struct node* right;
};
 
void preoreder(Tree t)
{
	Stack s = create();
 
	while (t != NULL || is_empty(s) == false)
	{
		while (t != NULL)
		{
			printf("%d ", t->val);
			push(s, *t);
			t = t->left;
		}
 
		if (is_empty(s) == false)
		{
			struct node temp = pop(s);
			t = &temp;
			t = t->right;
		}
	}
}
 
void inorder(Tree t)
{
	Stack s = create();
 
	while (t != NULL || is_empty(s) == false)
	{
		while (t != NULL)
		{
			push(s, *t);
			t = t->left;
		}
 
		if (is_empty(s) == false)
		{
			struct node temp = pop(s);
			t = &temp;
			printf("%d ", t->val);
			t = t->right;
		}
	}
}
 
 
void preorder(Tree t)
{
	if (t == NULL)
	{
		return;
	}
 
	if (t != NULL)
	{
		printf("%d", t->val);
		preorder(t->left);
		preorder(t->right);
	}
}
 
void inorder(Tree t)
{
	if (t == NULL)
	{
		return;
	}
 
	if (t != NULL)
	{
		inorder(t->left);
		printf("%d", t->val);
		inorder(t->right);
	}
}
 
void postorder(Tree t)
{
	if (t == NULL)
	{
		return;
	}
 
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		printf("%d", t->val);
	}
}

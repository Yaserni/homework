#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include<malloc.h>

typedef struct node
{
	char data[5];
	struct node* left;
	struct node* right;
}node;
typedef struct stack
{
	struct node* data;
	struct stack* next;

}stack;
void create_stack(stack** head)
{
	*head = NULL;
}
void push_stack(stack** s , node** n)
{
	stack* newitem = (stack*)malloc(sizeof(stack));
	newitem->data = *n;
	newitem->next = *s;
	*s = newitem;
}
node* pop_stack(stack** s)
{
	if (empty(*s))
	{
		printf("error");
		return NULL;
	}
	else
	{
	node* p = (*s)->data;
	*s = (*s)->next;
	return p;
	}
}
int empty(stack *head)
{
	if (head == NULL)
		return 1;
	else
		return 0;
}


node* create_expr_tree(char *postfix)
{
	// ADD YOUR CODE HERE
	stack s;
	create_stack(&s);
	char n[5];
	int j = 0;
	char token;
	node* NewNode;
	node* right;
	node* left;
	for (int  i = 0; i < strlen(postfix); i++)
	{
		j = 0;
		token = postfix[i];
		if (token >= '0'&& token <= '9')
		{
			do
			{
				i++;
				n[j] = token;
				token = postfix[i];
				j++;
			} while (token >= '0'&& token <= '9');
			n[j] = '\0';
			NewNode = (node*)malloc(sizeof(node));
			strcpy(NewNode->data, n);
			NewNode->left = NULL;
			NewNode->right = NULL;
			push_stack(&s, &NewNode);

		}
		else if (token == '+' || token == '*' || token == '/' || token == '-' || token == '^')
		{
			j = 0;
			n[j] = token;
			j++;
			n[j] = '\0';

			right = pop_stack(&s);
			left = pop_stack(&s);
			NewNode = (node*)malloc(sizeof(node));
			NewNode->left = left;
			NewNode->right = right;
			strcpy(NewNode->data,n);
			push_stack(&s, &NewNode);
		}
	}
	node* result=pop_stack(&s);
	return result;
}



void inOrder(node *treeNode)
{
	// ADD YOUR CODE HERE
	if (treeNode != NULL)
	{
		if (treeNode->left != NULL)
		{
			printf("( ");
			inOrder(treeNode->left);
		}



		printf("%s ", treeNode->data);
		if (treeNode->left != NULL)
		{
		inOrder(treeNode->right);
			printf(") ");
		}

	}
}

void postOrder(node *treeNode)
{
	// ADD YOUR CODE HERE
	if (treeNode != NULL)
	{
		postOrder(treeNode->left);
		postOrder(treeNode->right);
		printf("%s ",treeNode->data);
	}
}

void preOrder(node *treeNode)
{
	// ADD YOUR CODE HERE
	if (treeNode != NULL)
	{
		printf("%s ", treeNode->data);
		preOrder(treeNode->left);
		preOrder(treeNode->right);
	}
}

int evaluateExpression(node *treeNode)
{
	// ADD YOUR CODE HERE
	/*
		switch (c)
		{
		case '+':
			break;

		case '-':
			break;

		case '*':
			break;

		case '/':
			break;

		case '^':
			break;

		default:
			break;
		}


	*/
}

int main()
{
	char ex[][50] = { { "2 8 + 7 3 ^ *" }, { "98 2 * 8 +" }, { "2 5 * 6 4 / ^ 2 3 + +" },
	{ "1 2 3 4 + + +" }, { "12 32 + 3 + 4 +" } };
	node* treeRoot;
	int i;
	for (i = 0; i < 5; i++) {
		treeRoot = create_expr_tree(ex[i]);

		//Traversal Operation on expression tree
		printf("\nIn-Order Traversal :   ");
		inOrder(treeRoot);
		printf("\nPre-Order Traversal :   ");
		preOrder(treeRoot);
		printf("\nPost-Order Traversal :   ");
		postOrder(treeRoot);
		//evaluate expression from the expression tree:
		printf("\nEvaluate the expression from the tree: %d\n", evaluateExpression(treeRoot));
	}
	getchar();
	return 0;
}
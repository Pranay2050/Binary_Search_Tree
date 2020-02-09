#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct TreeNode{
	int value;
	struct TreeNode* left,*right;
};

struct TreeNode* insert(struct TreeNode* r,int val)
{
	struct TreeNode* newNode;
	struct TreeNode* temp;
	newNode= (struct TreeNode*)malloc(sizeof(struct TreeNode));

	if(newNode == NULL)
	{
		printf("Malloc Failed");
		exit(-1);
	}

	newNode->value = val;
	newNode->left= NULL;
	newNode->right= NULL;

	if(r == NULL)
	{
		r=newNode;
		return r;
	}

	temp = r;
	while(1)
	{
		if(val<temp->value)
		{
			if(temp->left == NULL)
			{
				temp->left = newNode;
				break;
			}
			temp=temp->left;
		}
		else
		{
			if(temp->right == NULL)
			{
				temp->right=newNode;
				break;
			}
			temp=temp->right;
		}
	}
	return r;
}

void traverse_postorder(struct TreeNode* root)
{
     if (root == NULL)
        return;

     traverse_postorder(root->left);
     traverse_postorder(root->right);
     printf("%d ", root->value);
}

void traverse_inorder(struct TreeNode* root)
{
     if (root == NULL)
          return;

     traverse_inorder(root->left);
     printf("%d ", root->value);
     traverse_inorder(root->right);
}

void traverse_preorder(struct TreeNode* root)
{
     if (root == NULL)
          return;

     printf("%d ", root->value);
     traverse_preorder(root->left);
     traverse_preorder(root->right);
}

struct TreeNode** createQueue(int *front, int *rear)
{
    struct TreeNode **queue =
        (struct TreeNode**)malloc(sizeof(struct TreeNode*)*100);

    *front = *rear = 0;
    return queue;
}

void enQueue(struct TreeNode **queue, int *rear, struct TreeNode *new_node)
{
    queue[*rear] = new_node;
    (*rear)++;
}

struct TreeNode* deQueue(struct TreeNode **queue, int *front)
{
    (*front)++;
    return queue[*front - 1];
}

void traverse_levelorder(struct TreeNode* root)
{
    int rear, front;
    struct TreeNode **queue = createQueue(&front, &rear);
    struct TreeNode *temp_node = root;

    while (temp_node)
    {
        printf("%d ", temp_node->value);

        if (temp_node->left)
            enQueue(queue, &rear, temp_node->left);

        if (temp_node->right)
            enQueue(queue, &rear, temp_node->right);

        temp_node = deQueue(queue, &front);
    }
}

struct TreeNode* findmin(struct TreeNode * ptr)
{
	while(ptr->left != NULL)
		ptr  =ptr->left;
	return ptr;
}

struct TreeNode* delete(struct TreeNode* root, int val)
{
	struct TreeNode* ptr, *temp;
	if(root == NULL)
		return root;

	else if(val<(root->value))
		root->left=delete(root->left,val);

	else if(val>(root->value))
		root->right = delete(root->right,val);

	else
	{
		if((root->left)==NULL && (root->right)==NULL)
		{
			free(root);
			return NULL;
		}

		else if(root->left==NULL)
		{
			temp=root->right;
			free(root);
			return temp;
		}

		else if(root->right==NULL)
		{
			temp=root->left;
			free(root);
			return temp;
		}

		else
		{
			ptr= findmin(root->right);
			root->value=ptr->value;
			root->right=delete(root->right,ptr->value);
		}
	}
return root;
}

struct TreeNode* clone(struct TreeNode* root)
{
	struct TreeNode *groot;
	groot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	if(root == NULL)
	return NULL;

	groot->value=root->value;
	groot->left=clone(root->left);
	groot->right=clone(root->right);
	return groot;
}


void main()
{
	struct TreeNode* root=NULL;
	struct TreeNode* groot=NULL;
	int value,h,c,delete_val;
	while(1)
	{
		printf("Enter the value (-1 to exit) : ");
		scanf("%d",&value);
		if(value==-1) break;
		root=insert(root,value);
	}

	printf("\nThe Pre-Order Traversal : ");
	traverse_preorder(root);

	printf("\nThe In-Order Traversal : ");
	traverse_inorder(root);

	printf("\nThe Post-Order Traversal : ");
	traverse_postorder(root);

	printf("\nThe Level-Order Traversal : ");
	traverse_levelorder(root);

	printf("\nEnter the value to be deleted : ");
	scanf("%d",&delete_val);
	delete(root, delete_val);

	groot = clone(root);
	printf("\nThe cloned Tree : ");
	traverse_inorder(groot);

}

/* OUTPUT
Enter the value (-1 to exit) : 1
Enter the value (-1 to exit) : 2
Enter the value (-1 to exit) : 3
Enter the value (-1 to exit) : 4
Enter the value (-1 to exit) : 5
Enter the value (-1 to exit) : 6
Enter the value (-1 to exit) : 8
Enter the value (-1 to exit) : -1

The Pre-Order Traversal : 1 2 3 4 5 6 8
The In-Order Traversal : 1 2 3 4 5 6 8
The Post-Order Traversal : 8 6 5 4 3 2 1
The Level-Order Traversal : 1 2 3 4 5 6 8
Enter the value to be deleted : 3

The cloned Tree : 1 2 4 5 6 8 */

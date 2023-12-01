#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node           //same as binary tree
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *create()                                       //same as binary tree
{
    struct node *new = malloc(sizeof(struct node));
    printf("Enter the data for the node (-1 for no node): ");
    scanf("%d", &new->data);

    if (new->data == -1)
        return NULL;

    new->left = NULL;
    new->right = NULL;

    printf("Enter left child of %d\n", new->data);
    new->left = create();

    printf("Enter right child of %d\n", new->data);
    new->right = create();

    return new;
}

struct node *insertNode(struct node *root, int data)
{
    if (root == NULL)
    {
        struct node *newNode = malloc(sizeof(struct node));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (data < root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insertNode(root->right, data);
    }

    return root;
}

void displayTree(struct node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 5;

    // Process right child first
    displayTree(root->right, space);

    // Print current node after space
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // Process left child
    displayTree(root->left, space);
}

int height(struct node * ptr){
    if (ptr==NULL)
    return 0;
    else
    {
        int leftheight = height(ptr->left);
        int rightheight = height(ptr->right);
    return 1 + ((leftheight > rightheight) ? leftheight: rightheight);
    }
}

void print_lvl(struct node *ptr, int lvl_no)
{
    if (!ptr)
        return;
    if (lvl_no == 0)
        printf("%d ", ptr->data);
    else
    {
        print_lvl(ptr->left, lvl_no - 1);
        print_lvl(ptr->right, lvl_no - 1);
    }
}

void lvlwise(struct node *ptr)
{
    int tree_height = height(ptr);
    for (int i = 0; i <= tree_height; i++)
    {
        printf("Level %d: ", i);
        print_lvl(ptr, i);
        printf("\n");
    }
}




int main()
{
    struct node *root = NULL;
    int choice;

    while (true)
    {
        printf("\nFunction:\n");
        printf("1. Create Binary Search Tree\n");
        printf("2. Insert Node\n");
        printf("3. Display Tree\n");
        printf("4.Level");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (root == NULL)
            {
                root = create();
                printf("Binary Search Tree created successfully!\n");
            }
            else
            {
                printf("Binary Search Tree already exists!\n");
            }
            break;
        case 2:
            {
                int data;
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
            }
            break;
        case 3:
            printf("Binary Search Tree:\n");
            displayTree(root, 0);
            break;
        case 4:
            printf("Level Wise:\n");
            lvlwise(root);
            printf("\n");
            break;
        case 0:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

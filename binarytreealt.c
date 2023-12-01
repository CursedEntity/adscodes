#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *create()
{
    struct node *new = malloc(sizeof(struct node));
    printf("Enter the data for the root node (-1 for no node): ");
    scanf("%d", &new->data);
    printf("\n");
            
    if(new->data == -1)
        return NULL;
    printf("Enter the left child of %d\n", new->data);
    new->left = create();
    printf("Enter the right child of %d\n", new->data);
    new->right = create();
        
    return new;
}

void inorder(struct node *ptr)
{
    if(ptr)
    {
        inorder(ptr->left);
        printf("%d ", ptr->data);
        inorder(ptr->right);
    }
}

void preorder(struct node *ptr)
{
    if(ptr)
    {
        printf("%d ", ptr->data);
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void postorder(struct node *ptr)
{
    if(ptr)
    {
        postorder(ptr->left);
        postorder(ptr->right);
        printf("%d ", ptr->data);
    }
}

void print_lvl(struct node *ptr, int lvl_no)
{
    if(!ptr)
        return;
    if(lvl_no == 0)
        printf("%d ", ptr->data);
    else
    {
        print_lvl(ptr->left, lvl_no - 1);
        print_lvl(ptr->right, lvl_no - 1);
    }
}

int height(struct node *ptr)
{
    if(ptr == NULL)
        return -1;
    else
    {
        int left_height = height(ptr->left);
        int right_height = height(ptr->right);
        if(left_height > right_height)
            return left_height + 1;
        else
            return right_height + 1;
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

void mirror_img(struct node *ptr)
{
    if(ptr == NULL)
        return;
    else
    {
        struct node *temp;
        mirror_img(ptr->left);
        mirror_img(ptr->right);
        temp = ptr->left;
        ptr->left = ptr->right;
        ptr->right = temp;
    }
}

void leaf(struct node *ptr)
{
    if(ptr == NULL)
        return;
    else if(ptr->left == NULL && ptr->right == NULL)
        printf("%d ", ptr->data);
    else
    {
        leaf(ptr->left);
        leaf(ptr->right);
    }
}

// struct node* insert(struct node* root)
// {
//     int data;
//     if (root == NULL)
//     {
//         struct node* newNode = malloc(sizeof(struct node));
//         scanf("%d", &data);
//         newNode->data = data;
//         newNode->left = newNode->right = NULL;
//         return newNode;
//     }
    
//     if (data < root->data)
//         root->left = insert(root->left);
//     else if (data > root->data)
//         root->right = insert(root->right);
    
//     return root;
// }

int total_nodes(struct node *ptr)
{
    if(ptr == NULL)
        return 0;
    else
        return 1 + total_nodes(ptr->left) + total_nodes(ptr->right);
}


int main()
{
    struct node *root = create();
    int choice;
    while(1)
    {
        printf("Enter your choice:\n 1.Insert\n 2.Traversals \n 3.Mirrored\n 4.Height\n 5.Leaf\n 6.Total\n 7.Exit\n ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1: printf("Insert a node:\n"); insert(root);
                    printf("Inorder traversal after insertion: ");
                    inorder(root);
                    printf("\n\n");
                    break;

            case 2: printf("Inorder traversal: ");
                    inorder(root);
                    printf("\n");
                    
                    printf("Preorder traversal: ");
                    preorder(root);
                    printf("\n");
                    
                    printf("Postorder traversal: ");
                    postorder(root);
                    printf("\n");
                    
                    printf("Level-wise traversal:\n");
                    lvlwise(root);
                    printf("\n");
                    break;

            case 3: printf("Mirrored Tree Inorder traversal: ");
                    mirror_img(root);
                    inorder(root);
                    printf("\n\n");
                    break;

            case 4: printf("Height of the tree: %d\n\n", height(root));
                    break;

            case 5: printf("Leaf nodes: ");
                    leaf(root);
                    printf("\n\n");
                    break;
                
            case 6: printf("Total number of nodes in the tree: %d\n\n", total_nodes(root));
                    break;
                
            case 7: exit(0);
        }
    }
    
    return 0;
}

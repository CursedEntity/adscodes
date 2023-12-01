#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
    int height;
};

int getheight(struct node* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

struct node* create(int data) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getbalancefactor(struct node* n) {
    if (n == NULL) {
        return 0;
    }

    return getheight(n->left) - getheight(n->right);
}

struct node* rightrotate(struct node* y) {
    struct node* x = y->left;
    struct node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(getheight(y->right), getheight(y->left)) + 1;
    x->height = max(getheight(x->right), getheight(x->left)) + 1;

    return x;
}

struct node* leftrotate(struct node* x) {
    struct node* y = x->right;
    struct node* t2 = y->left;

    y->left = x;
    x->right = t2;

    y->height = max(getheight(y->right), getheight(y->left)) + 1;
    x->height = max(getheight(x->right), getheight(x->left)) + 1;

    return y;
}

void displayTreeByLevels(struct node* root) {
    if (root == NULL) {
        printf("AVL Tree is empty.\n");
        return;
    }

    struct node* queue[100];
    int front = -1, rear = -1;
    int currentLevel = 1, nextLevel = 0;

    queue[++rear] = root;
    while (front != rear) {
        struct node* temp = queue[++front];
        printf("%d ", temp->data);
        currentLevel--;

        if (temp->left) {
            queue[++rear] = temp->left;
            nextLevel++;
        }
        if (temp->right) {
            queue[++rear] = temp->right;
            nextLevel++;
        }

        if (currentLevel == 0) {
            printf("\n");
            currentLevel = nextLevel;
            nextLevel = 0;
        }
    }
}

struct node* insert(struct node* node, int data) {
    // Insertion code remains the same

    if (node == NULL)
        return create(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data >= node->data)
        node->right = insert(node->right, data);

    node->height = 1 + max(getheight(node->left), getheight(node->right));
    int bf = getbalancefactor(node);

    if (bf > 1 && data < node->left->data)
        return rightrotate(node);

    if (bf < -1 && data > node->right->data)
        return leftrotate(node);

    if (bf > 1 && data > node->left->data) {
        node->left = leftrotate(node->left);
        return rightrotate(node);
    }

    if (bf < -1 && data < node->right->data) {
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }

    return node;
}

struct node* findMinNode(struct node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct node* deleteNode(struct node* root, int data) {
    // Deletion code remains the same

    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    root->height = 1 + max(getheight(root->left), getheight(root->right));
    int bf = getbalancefactor(root);

    if (bf > 1 && data < root->left->data)
        return rightrotate(root);

    if (bf < -1 && data > root->right->data)
        return leftrotate(root);

    if (bf > 1 && data > root->left->data) {
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }

    if (bf < -1 && data < root->right->data) {
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }

    return root;
}

int main() {
    struct node* root = NULL;
    int n, del, data1, data2;
    printf("Enter the number of nodes you want to insert: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter data for node/s %d: ", i + 1);
        scanf("%d", &data1);
        root = insert(root, data1);
    }

    printf("\nAVL Tree after insertion:\n");
    displayTreeByLevels(root);

    printf("\nEnter the number of nodes you want to delete: ");
    scanf("%d", &del);

    for (int i = 0; i < del; i++) {
        printf("Enter data for node/s %d: ", i + 1);
        scanf("%d", &data2);
        root = deleteNode(root, data2);
    }

    printf("\nAVL Tree after deletion:\n");
    displayTreeByLevels(root);

    return 0;
}

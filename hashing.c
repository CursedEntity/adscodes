#include <stdio.h>
#include <stdlib.h>

// Define a structure for a key-value pair
struct KeyValue {
    int key;
    int value;
    struct KeyValue* next;
};

// Define a hash table
struct HashTable {
    struct KeyValue** table;
    int size;
};

// Initialize the hash table
void initHashTable(struct HashTable* ht, int size) {
    ht->table = (struct KeyValue**)malloc(size * sizeof(struct KeyValue*));
    ht->size = size;

    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
}

// Custom hash function
int customHash(int key, int size) {
    // Replace this with your custom hash function
    return key % size;
}

// Insert a key-value pair into the hash table
void insert(struct HashTable* ht, int key, int value, int (*hashFunction)(int, int)) {
    int index = hashFunction(key, ht->size);
    struct KeyValue* newPair = (struct KeyValue*)malloc(sizeof(struct KeyValue));
    newPair->key = key;
    newPair->value = value;
    newPair->next = ht->table[index];
    ht->table[index] = newPair;
}

// Search for a key in the hash table and return its value
int search(struct HashTable* ht, int key, int (*hashFunction)(int, int)) {
    int index = hashFunction(key, ht->size);
    struct KeyValue* current = ht->table[index];

    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    return -1; // Key not found
}

// Display the contents of the hash table
void display(struct HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("Index %d: ", i);
        struct KeyValue* current = ht->table[i];
        while (current != NULL) {
            printf("(%d, %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    int size, choice;

    printf("Enter the size of the hash table: ");
    scanf("%d", &size);
    struct HashTable ht;
    initHashTable(&ht, size);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert a key-value pair\n");
        printf("2. Search for a key\n");
        printf("3. Display the hash table\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int key, value;
        switch (choice) {
            case 1:
                
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter value: ");
                scanf("%d", &value);
                insert(&ht, key, value, customHash);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                int result = search(&ht, key, customHash);
                if (result != -1) {
                    printf("Key %d found with value %d\n", key, result);
                } else {
                    printf("Key %d not found\n", key);
                }
                break;
            case 3:
                display(&ht);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

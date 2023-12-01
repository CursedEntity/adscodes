#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Adjacency Matrix representation of a graph
int adjMatrix[MAX_VERTICES][MAX_VERTICES];

// Adjacency List representation of a graph
struct Node {
    int data;
    struct Node* next;
};
struct Node* adjList[MAX_VERTICES];

int visited[MAX_VERTICES];
int queue[MAX_VERTICES];
int front = -1, rear = -1;

int numVertices;

// Function to add an edge to the graph (adjacency matrix)
void addEdgeMatrix(int from, int to) {
    adjMatrix[from][to] = 1;
    adjMatrix[to][from] = 1;
}

// Function to add an edge to the graph (adjacency list)
void addEdgeList(int from, int to) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = to;
    newNode->next = adjList[from];
    adjList[from] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = from;
    newNode->next = adjList[to];
    adjList[to] = newNode;
}


// Depth-First Search (DFS) using adjacency matrix
void DFSMatrix(int vertex) {
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFSMatrix(i);
        }
    }
}

// Depth-First Search (DFS) using adjacency list
void DFSList(int vertex) {
    printf("%d ", vertex);
    visited[vertex] = 1;

    struct Node* currentNode = adjList[vertex];
    while (currentNode != NULL) {
        int adjVertex = currentNode->data;
        if (!visited[adjVertex]) {
            DFSList(adjVertex);
        }
        currentNode = currentNode->next;
    }
}

// Breadth-First Search (BFS) using adjacency matrix
void BFSMatrix(int startVertex) {
    int i, currentVertex;

    visited[startVertex] = 1;
    printf("%d ", startVertex);
    front = 0;
    rear = 0;
    queue[rear] = startVertex;

    while (front <= rear) {
        currentVertex = queue[front++];
        
        for (i = 0; i < numVertices; i++) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                printf("%d ", i);
                queue[++rear] = i;
            }
        }
    }
}

// Breadth-First Search (BFS) using adjacency list
void BFSList(int startVertex) {
    int i, currentVertex;

    visited[startVertex] = 1;
    printf("%d ", startVertex);
    front = 0;
    rear = 0;
    queue[rear] = startVertex;

    while (front <= rear) {
        currentVertex = queue[front++];
        
        struct Node* currentNode = adjList[currentVertex];
        while (currentNode != NULL) {
            int adjVertex = currentNode->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                printf("%d ", adjVertex);
                queue[++rear] = adjVertex;
            }
            currentNode = currentNode->next;
        }
    }
}

// Function to initialize the visited array
void initializeVisited() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }
}

// Function to display the adjacency matrix
void displayMatrix() {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to display the adjacency list
void displayList() {
    printf("Adjacency List:\n");
    for (int i = 0; i < numVertices; i++) {
        struct Node* currentNode = adjList[i];
        printf("Vertex %d -> ", i);
        while (currentNode != NULL) {
            printf("%d -> ", currentNode->data);
            currentNode = currentNode->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, startVertex, from, to;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    for (int i = 0; i < numVertices; i++) {
        adjList[i] = NULL;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add an edge\n");
        printf("2. Depth-First Search (DFS)\n");
        printf("3. Breadth-First Search (BFS)\n");
        printf("4. Display the graph\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the starting vertex: ");
                scanf("%d", &from);
                printf("Enter the ending vertex: ");
                scanf("%d", &to);
                addEdgeMatrix(from, to);
                addEdgeList(from, to);
                break;
            case 2:
                initializeVisited();
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &startVertex);
                printf("DFS using adjacency matrix: ");
                DFSMatrix(startVertex);
                printf("\n");
                initializeVisited();
                printf("DFS using adjacency list: ");
                DFSList(startVertex);
                printf("\n");
                break;
            case 3:
                initializeVisited();
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &startVertex);
                printf("BFS using adjacency matrix: ");
                BFSMatrix(startVertex);
                printf("\n");
                initializeVisited();
                printf("BFS using adjacency list: ");
                BFSList(startVertex);
                printf("\n");
                break;
            case 4:
                displayMatrix();
                displayList();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}


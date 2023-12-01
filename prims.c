#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int minKey(int key[], bool mstSet[], int V) { // find min edge
    int min = INT_MAX, min_index;  // initialize min value

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

int printMST(int parent[], int** graph, int V) {   // print MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int** graph, int V) {          // construct and print MST
    
    int parent[V]; // Array to store constructed MST
    int key[V]; // Key values used to pick minimum weight edge in cut
    bool mstSet[V]; // To represent set of vertices included in MST

    for (int i = 0; i < V; i++)         // Initialize all keys as INFINITE
        key[i] = INT_MAX, mstSet[i] = false;

    
    key[0] = 0; //include first 1st vertex in MST. Make key 0 so that this vertex is picked as first
    parent[0] = -1; // First node is always root of MST

    
    for (int count = 0; count < V - 1; count++) { // The MST will have V vertices

        int u = minKey(key, mstSet, V); // Pick the minimum key vertex
       
        mstSet[u] = true;  // Add the picked vertex to the MST Set

        for (int v = 0; v < V; v++) // Update key value and parent index

            // graph[u][v] is non zero only for adjacent
            // vertices of m mstSet[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // print the constructed MST
    printMST(parent, graph, V);
}

// Driver's code
int main() {
    int V;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    int** graph = (int**)malloc(V * sizeof(int*)); //allocate memory for the adjacency matrix
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }

    printf("Enter the adjacency matrix for the graph (%dx%d):\n", V, V);  // input adjacency matrix 
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, V);  // Print graph

    for (int i = 0; i < V; i++) {  // free allocated memory
        free(graph[i]);
    }
    free(graph);

    return 0;
}

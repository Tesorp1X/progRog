#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>


//Adjacency List Node
typedef struct AdjListNode { 
	int dest; 
	int weight; 
	struct AdjListNode *next; 
}AdjListNode; 

//Adjacency List
typedef struct AdjList { 
	AdjListNode *head;
}AdjList; 

typedef struct Graph { 
	int ammountOfVertex; 
	AdjList *array; 
}Graph;

typedef struct MinHeapNode { 
	int vertex; 
	int cost; 
}MinHeapNode;

typedef struct MinHeap { 
	int size; 
	int capacity;
	int *pos;	 
	struct MinHeapNode **array; 
}MinHeap;

AdjListNode *AdjListNode_make(int dest, int weight) { 
	AdjListNode *newNode = (AdjListNode *) malloc(sizeof(AdjListNode));
    if (!newNode) {
        printf("Error");
		exit(1);
    }
	newNode->dest = dest; 
	newNode->weight = weight; 
	newNode->next = NULL; 
	return newNode; 
}


Graph *Graph_make(int ammountOfVertex) { 
	Graph *graph = (Graph *) malloc(sizeof(Graph));
    if (!graph) {
        printf("Error");
		exit(1);
    }
	graph->ammountOfVertex = ammountOfVertex; 

	// Create an array of adjacency lists. Size of array will be ammountOfVertex
	graph->array = (AdjList *) malloc(ammountOfVertex * sizeof(AdjList)); 
	if (!graph->array) {
		printf("Error");
		exit(1);
	}

	for (int i = 0; i < ammountOfVertex; ++i) 
		graph->array[i].head = NULL; 

	return graph; 
}

void Graph_free(Graph *graph, int ammountOfVertex) {
    for (int i = 0; i < ammountOfVertex; ++i) free(graph->array[i].head);
    free(graph->array);
    free(graph);
}



void Graph_addEdge(Graph *graph, int from, int to, int weight) { 
	AdjListNode *newNode = AdjListNode_make(to, weight); 
	newNode->next = graph->array[from].head; 
	graph->array[from].head = newNode; 

	newNode = AdjListNode_make(from, weight); 
	newNode->next = graph->array[to].head; 
	graph->array[to].head = newNode; 
} 


MinHeapNode *MinHeapNode_make(int vertex, int cost) { 
	MinHeapNode *minHeapNode = (MinHeapNode *) malloc(sizeof(MinHeapNode));
	if (!minHeapNode) {
		printf("Error");
		exit(1);
	}

	minHeapNode->vertex = vertex;
	minHeapNode->cost = cost;
	return minHeapNode;
} 

MinHeap *MinHeap_make(int capacity) { 
	MinHeap *minHeap = (MinHeap *) malloc(sizeof(MinHeap));
    if (!minHeap) {
        printf("Error");
		exit(1);
    }

	minHeap->pos = (int *) malloc(capacity * sizeof(int));
	if (!minHeap->pos) {
		printf("Error");
		exit(1);
	}

	minHeap->size = 0; 
	minHeap->capacity = capacity;
	minHeap->array = (MinHeapNode **) malloc(capacity * sizeof(MinHeapNode *));
	if (!minHeap->array) {
		printf("Error");
		exit(1);
	}
	
	return minHeap; 
} 

void MinHeap_free(MinHeap *minHeap) {
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

void MinHeapNode_swap(MinHeapNode **a, MinHeapNode **b) { 
	MinHeapNode *t = *a; 
	*a = *b; 
	*b = t; 
} 
/*  Restores the balance in minHeap. */
void MinHeap_heapify(MinHeap *minHeap, int index) { 
	int smallest, left, right; 
	smallest = index; 
	left = 2 * index + 1; 
	right = 2 * index + 2; 

	if (left < minHeap->size && minHeap->array[left]->cost < minHeap->array[smallest]->cost) 
	smallest = left; 

	if (right < minHeap->size && minHeap->array[right]->cost < minHeap->array[smallest]->cost) 
	smallest = right; 

	if (smallest != index) { 
		/* The nodes to be swapped in min heap */
		MinHeapNode *smallestNode = minHeap->array[smallest]; 
		MinHeapNode *idxNode = minHeap->array[index]; 

		/* Swap positions */
		minHeap->pos[smallestNode->vertex] = index; 
		minHeap->pos[idxNode->vertex] = smallest; 

		/* Swap nodes */
		MinHeapNode_swap(&minHeap->array[smallest], &minHeap->array[index]); 

		MinHeap_heapify(minHeap, smallest); 
	} 
} 


int MinHeap_isEmpty(MinHeap *minHeap) { 
	return minHeap->size == 0; 
} 

// Function to extract minimum node from heap 
MinHeapNode *MinHeap_extractMin(MinHeap *minHeap) { 
	if (MinHeap_isEmpty(minHeap)) 
		return NULL; 

	// Store the root node 
	MinHeapNode *root = minHeap->array[0]; 

	// Replace root node with last node 
	MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node 
	minHeap->pos[root->vertex] = minHeap->size-1;
	minHeap->pos[lastNode->vertex] = 0;

	// Reduce heap size and heapify root 
	--(minHeap->size);
	MinHeap_heapify(minHeap, 0);

	return root;
}

/* Function to decreas cost value of a given vertex. This function 
 uses pos[] of min heap to get the current index of node in min heap */
void MinHeap_decreaseKey(MinHeap *minHeap, int vertex, int cost) {
	// Get the index of v in heap array 
	int i = minHeap->pos[vertex];

	// Get the node and update its cost value 
	minHeap->array[i]->cost = cost;

	// Travel up while the complete tree is not hepified. 
	while (i && minHeap->array[i]->cost < minHeap->array[(i - 1) / 2]->cost) {
		// Swap node with its parent
		minHeap->pos[minHeap->array[i]->vertex] = (i-1)/2;
		minHeap->pos[minHeap->array[(i-1)/2]->vertex] = i;
		MinHeapNode_swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		// move to parent index 
		i = (i - 1) / 2;
	} 
} 

bool MinHeap_isInMinHeap(MinHeap *minHeap, int v) { 
	if (minHeap->pos[v] < minHeap->size) 
		return true; 
	return false; 
}

/**
 * Finds answer for the task using dijkstra algorithm.
 * Finds min cost for any node from start.
*/
int FindMaxGold(Graph *graph, int start, int *gold, int amuletPower) { 
	int ammountOfVertex = graph->ammountOfVertex;
	int *cost = (int *) malloc(ammountOfVertex * sizeof(int));	
    int max_gold = gold[0];
	MinHeap *minHeap = MinHeap_make(ammountOfVertex); 

	for (int i = 0; i < ammountOfVertex; ++i) { 
		cost[i] = INT_MAX;
		minHeap->array[i] = MinHeapNode_make(i, cost[i]); 
		minHeap->pos[i] = i; 
	} 
	minHeap->array[start] = MinHeapNode_make(start, cost[start]); 
	minHeap->pos[start] = start; 
	cost[start] = 0; 
	MinHeap_decreaseKey(minHeap, start, cost[start]);

	minHeap->size = ammountOfVertex; 

	while (!MinHeap_isEmpty(minHeap)) {  
		MinHeapNode *minHeapNode = MinHeap_extractMin(minHeap); 
		int u = minHeapNode->vertex;
		
		AdjListNode *pCrawl = graph->array[u].head;
		if (amuletPower - cost[u] < 0) break;
		if (amuletPower - cost[u] > 0 && max_gold < gold[u]) {
			max_gold = gold[u];
			break;
		}
		if (amuletPower - cost[u] > 0 && max_gold < gold[u]) max_gold = gold[u];
		while (pCrawl != NULL) {
			int v = pCrawl->dest;
			if (MinHeap_isInMinHeap(minHeap, v) && cost[u] != INT_MAX && pCrawl->weight + cost[u] < cost[v]) { 
				cost[v] = cost[u] + pCrawl->weight;
				MinHeap_decreaseKey(minHeap, v, cost[v]);
			}
			pCrawl = pCrawl->next; 
		}
        
	}
    free(cost);
    MinHeap_free(minHeap);

	return max_gold;
} 

int main() {
	char *a = NULL;
	char b = *a;
    FILE *IN, *OUT;
    int amuletPower;      
    int ammountOfVertex;  
    int ammountOfEdges;   
    IN = fopen("input.txt", "r");
    fscanf(IN, "%d %d %d", &amuletPower, &ammountOfVertex, &ammountOfEdges);
    Graph *graph = Graph_make(ammountOfVertex);
	int from, to, cost; 
	for (int i = 0; i < ammountOfEdges; ++i) {
		fscanf(IN, "%d %d %d", &from, &to, &cost);
        Graph_addEdge(graph, from, to, cost);
	}
	int *gold = (int *) malloc(ammountOfVertex * sizeof(int));
	if (!gold) {
		printf("Error");
		exit(1);
	}
	for (int i = 0; i < ammountOfVertex; ++i) fscanf(IN, "%d", &gold[i]);
    fclose(IN);
	int result = FindMaxGold(graph, 0, gold, amuletPower);
    OUT = fopen("output.txt", "w+");
	fprintf(OUT, "%d\n", result);
    fclose(OUT);
    Graph_free(graph, ammountOfVertex);
    free(gold);

    return 0;
}
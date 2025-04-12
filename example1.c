#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjList;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int *array;
} Stack;

Node *create_node(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjList = malloc(vertices * sizeof(Node *));
    graph->visited = calloc(vertices, sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *newNode = create_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->array[++stack->top] = value;
    }
}

void DFS(Graph *graph, Stack *stack, int vertex) {
    graph->visited[vertex] = 1;
    push(stack, vertex);

    Node *temp = graph->adjList[vertex];

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, stack, connectedVertex);
        }
        temp = temp->next;
    }
}

void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void insert_edges(Graph *graph, int edgeCount) {
    int src, dest;
    for (int i = 0; i < edgeCount; i++) {
        scanf("%d %d", &src, &dest);
        if (src >= 0 && src < graph->vertices && dest >= 0 && dest < graph->vertices) {
            add_edge(graph, src, dest);
        }
    }
}

int is_reachable(Graph *graph, int src, int dest) {
    Stack *stack = create_stack(graph->vertices);
    DFS(graph, stack, src);

    int reachable = 0;
    for (int i = 0; i <= stack->top; i++) {
        if (stack->array[i] == dest) {
            reachable = 1;
            break;
        }
    }

    free(stack->array);
    free(stack);
    reset_visited(graph);

    return reachable;
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        Node *temp = graph->adjList[i];
        while (temp) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjList);
    free(graph->visited);
    free(graph);
}

int main() {
    int vertices, edges;
    int src, dest;

    scanf("%d", &vertices);
    scanf("%d", &edges);

    Graph *graph = create_graph(vertices);
    insert_edges(graph, edges);

    scanf("%d %d", &src, &dest);

    if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
        if (is_reachable(graph, src, dest)) {
            printf("DA\n");
        } else {
            printf("NU\n");
        }
    } else {
        printf("NU\n");
    }

    free_graph(graph);

    return 0;
}

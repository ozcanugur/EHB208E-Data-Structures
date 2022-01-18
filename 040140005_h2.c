//
//  main.c
//  DSHomework2
//
//  Created by Uğur Özcan on 4.06.2020.
//  Copyright © 2020 Uğur Özcan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

// Defining the number of vertices in the graph
#define CITY_NUM 7

// Defining the linked list nodes
typedef struct node {
    int val;
    struct node * next;
} Node_l;

// Defining the stack to store the path
typedef struct stack {
    int top;
    int cities[CITY_NUM];
} Stack;

// Defining the graph nodes
typedef struct Node {
    int dest, weight;
    struct Node* next;
}Node_g;

// Defining the edges of the graph
typedef struct edge {
    int source, dest, weight;
}Edge;

// Defining the graph
typedef struct graph {
    Node_g * head[CITY_NUM];
    int visited[CITY_NUM]; //Indicator showing if the node has been visited. Necessary for pathfinding.
}Graph;

// Defining the function pushing the given integer to the given linked list.
void pushlist(Node_l * head, int newVal) {
    Node_l * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (Node_l *) malloc(sizeof(Node_l));
    current->next->val = newVal;
    current->next->next = NULL;
}

// Defining the function pushing the given integer to the given stack.
void pushstack(Stack *s, int newCity) {
    s->top++;
    s->cities[s->top] = newCity;
}

// Defining the function deleting the last element of the given stack.
void popstack(Stack *s) {
    if(s->top!=-1) {
        s->cities[s->top] = -1;
        s->top=s->top-1;
    }
}

// Defining the function forming the graph with given edges and edge number.
Graph* createGraph(Edge edges[], int n)
{
    // Allocating the memory for graph data structure
    Graph* g = (Graph *)malloc(sizeof(Graph));
    int i;
    
    // Initializing the head pointers for all vertices
    for (i = 0; i < CITY_NUM; i++){
        g->head[i] = NULL;
    }
    
    // Adding given edges to the graph
    for (i = 0; i < n; i++)
    {
        int source = edges[i].source;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        
        // Allocating a new node of adjacency list from source to destination
        Node_g* newNode = (Node_g*)malloc(sizeof(Node_g));
        newNode->dest = dest;
        newNode->weight = weight;
        
        // Pointing the new node to the current head
        newNode->next = g->head[source];
        
        // Pointing the head pointer to the new node
        g->head[source] = newNode;
    }
    
    // Initializing all the vertices as not visited.
    for (i = 0; i < CITY_NUM; i++){
        g->visited[i] = 0;
    }
    
    // Returning the formed graph
    return g;
}

// Defining the function finding the path and its lenght between given two vertices (first and second).
// Here vertex stands for a dummy variable.
void findPath(Graph* g, int first, int vertex, int second, Stack* path){
    
    //Initializing a temporary node with the value of vertex's node
    Node_g* adjList = g->head[vertex];
    Node_g* temp = adjList;
    //Initializing another temporary node with the value of first node.
    //It is stored seperately to reach all the destination of the nodes.
    //Otherwise the recursiveness deletes the initial point.
    Node_g* adjList2 = g->head[first];
    Node_g* temp2 = adjList2;
    
    //Marking the vertex as visited.
    g->visited[vertex] = 1;
    
    //Storing the visited vertex to follow the path.
    pushstack(path,vertex);
    
    //As long as the node exists with given vertex this loop continues.
    while (temp != NULL) {
        //Finding the first destination.
        int connectedVertex = temp->dest;
        //Checking if the node is visited
        if (g->visited[connectedVertex] == 0) {
            //Checking if the node is the destination
            if(connectedVertex==second){
                //Adding the destination to the path.
                pushstack(path,second);
                //Printing the cities on the path.
                printf("Path Found: ");
                for(int j=0;j<=path->top;j++) {
                    switch (path->cities[j]) {
                        case 0:
                            printf("Prague, ");
                            break;
                        case 1:
                            printf("Helsinki, ");
                            break;
                        case 2:
                            printf("Beijing, ");
                            break;
                        case 3:
                            printf("Tokyo, ");
                            break;
                        case 4:
                            printf("Jakarta, ");
                            break;
                        case 5:
                            printf("London, ");
                            break;
                        case 6:
                            printf("New York, ");
                            break;
                        default:
                            break;
                    }
                }
                //Calculating the total distance along the path.
                int TotalDist = 0;
                //This function compares the adjacent vertices in the stack to find the way between two cities.
                for(int k=path->top;k>0;k--){
                    struct Node* adj = g->head[path->cities[k-1]];
                    struct Node* tmp = adj;
                    //This loop continues until the distance between adjacent two cities in the stack is found.
                    while(tmp!=NULL){
                        //Checking if the destination of the previous node is the same with the current.
                        if(path->cities[k]== tmp->dest){
                            TotalDist = TotalDist + tmp->weight;}
                        tmp = tmp->next;}
                }
                printf("\nTotal distance is %d\n",TotalDist);
                // Breaking the loop when the result is found
                break;
            }else{
                //If the vertex is not the wanted one, the function recurs itself with the destination vertex.
                findPath(g, first, connectedVertex, second,  path);
            }
            break;
        }
        
        //That the funtion reaches here means that the deepest point has been reached in the graph
        //from the first vertex; however, the destination cannot have been achieved.
        //And the wrong path is deleted until the first vertex is reached.
        for(int k=path->top;k>-1;k--){
            if(path->cities[k]!=first){
                g->visited[path->cities[k]] = 0;
                popstack(path);
            }else{break;}}
        
        //The next node in the adjacency list of the first vertex is given to the funciton to search the
        //other branches coming from the first vertex.
        if(temp2->next!=NULL){
            temp = temp2->next;
            first = temp->dest;
        }//If there is not another vertex connected to the first one, the lower level branches are given to the function.
        else{
            temp2 = g->head[temp->dest];
            first = temp->dest;
        }
    }
}


int main(void){
    
    //The edges as given in the homework.
    Edge edges[] =
    {
        { 0, 1, 1845 }, { 0, 5, 1264 }, { 1, 3, 7815 }, { 2, 5, 8132 }, { 2, 6, 11550 }, { 3, 4, 5782 },
        { 3, 6, 10838 }, { 4, 2, 4616 }, { 5, 3, 9566 }, { 6, 5, 5567 }
    };
    
    //Finding the number of edges
    int n = sizeof(edges)/sizeof(edges[0]);
    
    //Forming the graph from given edges
    Graph *g = createGraph(edges, n);
    
    //Initializing the stack "path" to hold the path data
    Stack * path = NULL;
    path = (Stack *) malloc(sizeof(Stack));
    path->top= -1;
    
    int firstCity;
    int secondCity;
    
    printf("Cities:\nPrague = 0\nHelsinki = 1\nBeijing = 2\nTokyo = 3\nJakarta = 4\nLondon = 5\nNew York = 6\n");
    
    printf("\nEnter the number of the first city:");
    scanf("%d",&firstCity);
    
    printf("\nEnter the number of the second city:");
    scanf("%d",&secondCity);
    
    findPath(g, firstCity, firstCity, secondCity,path);
    printf("--------------------------------------\n");
    
    return 0;
}


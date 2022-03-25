#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <bits/stdc++.h>

using namespace std;




/** 
 *
 * Custom Struct Defination 
 */


/// Single Node of AdjList
struct Node{
	int dest;
	int weight;
	int fromSource;
	Node* next;
};






/**
 *
 * Function Utitlitis 
 */
Node* newNode(int dest, int weight)
{
	Node* node = (Node*)malloc(sizeof(Node*));
	node->dest = dest;
	node->weight = weight;
	node->next = NULL;
	node->fromSource = INT_MAX;
	return node;
}

vector<Node*> createGraph(int V)
{
	vector<Node*> graph;
	graph.resize(V);
	return graph;
}

void addEdge(vector<Node*> *graph, int src, int dest, int weight)
{
	Node* node = newNode(dest, weight); // create new node
	// add this node to beginning.
	node->next = (*graph)[src];
	(*graph)[src] = node;

	// add edge from dest to src [unDirected graph]
	node = newNode(src, weight);
	node->next = (*graph)[dest]; 
	(*graph)[dest] = node;
}

void printNode(Node* node)
{
	while(node){
		cout << "->" << node->dest;
		node = node->next;
	}
	printf("\n");

}


void printGraph(vector<Node*> graph)
{
	//for (auto i = graph->adjList->begin(); i!=graph->adjList->end(); i++){
	for (unsigned int i = 0; i < graph.size(); i++ ){
		cout << "\n Adjacency List of vertex " << i
			<< "\n head ";
		
		printNode(graph[i]);
	}

}

class EdgeInfoByEffortComparator {
	public:
        /// Comparing method
        /** Minimum Heap */
        bool operator()(const Node* nod1,const Node* nod2) {
            if (nod1->weight == nod2->weight) {
				return nod1->dest > nod2->dest;
			}
            return nod1->weight > nod2->weight;						
		
        }
    };


void dijkstra(vector<Node*>* graph, int src)
{
	EdgeInfoByEffortComparator comparator;
	/** Set Destance from Source to Source to be Zero ! */
	(*graph)[src]->fromSource = 0;
	Node* node = graph->front();
	cout<< "front Element: " << node->dest<< endl;
	printNode(node);

	make_heap(graph->begin(), graph->end(), comparator);
	node = graph->front();
	cout<< "front Element: " << node->dest <<endl;
	printNode(node);
	
}

int main()
{
	vector<Node*> graph = createGraph(9);
	
	addEdge(&graph, 0, 1, 4);
    addEdge(&graph, 0, 7, 8);
    addEdge(&graph, 1, 2, 8);
    addEdge(&graph, 1, 7, 11);
    addEdge(&graph, 2, 3, 7);
    addEdge(&graph, 2, 8, 2);
    addEdge(&graph, 2, 5, 4);
    addEdge(&graph, 3, 4, 9);
    addEdge(&graph, 3, 5, 14);
    addEdge(&graph, 4, 5, 10);
    addEdge(&graph, 5, 6, 2);
    addEdge(&graph, 6, 7, 1);
    addEdge(&graph, 6, 8, 6);
    addEdge(&graph, 7, 8, 7);
	
	printGraph(graph);

	dijkstra(&graph, 0);

	return 0;
}

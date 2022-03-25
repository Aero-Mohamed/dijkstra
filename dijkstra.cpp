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
	char name;
	char parent_name;
	int dest;
	int weight;
	int effort;
	Node* next;
};


/**
 *
 * Function Utitlitis 
 */
Node* newNode(int dest, int weight)
{
	Node* node = (Node*)malloc(sizeof(Node*));
	node->name = dest+65;
	node->dest = dest;
	node->weight = weight;
	node->effort = INT_MAX;
	node->next = NULL;
	node->parent_name = ' ';
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

void optimizeGraphHead(vector<Node*> *graph)
{
	for(auto i=0; i< graph->size(); i++){
		Node* node = newNode(i, (*graph)[i]->weight);
		node->next = (*graph)[i];
		(*graph)[i] = node;
	}
}

void printNode(Node* node)
{
	while(node){
		cout << node->name << "(" << node->weight << ") ";
		node = node->next;
		if(node){
			cout << "->";
		}
	}
	printf("\n");

}


void printGraph(vector<Node*> graph)
{
	//for (auto i = graph->adjList->begin(); i!=graph->adjList->end(); i++){
	for (unsigned int i = 0; i < graph.size(); i++ ){
		cout << "\n Adjacency List of vertex " << graph[i]->name
			<< "\n head = ";
		
		printNode(graph[i]);
	}

}

class EdgeInfoByEffortComparator {
	public:
        /// Comparing method
        /** Minimum Heap */
        bool operator()(const Node* nod1,const Node* nod2) {
            if (nod1->effort == nod2->effort) {
				return nod1->dest > nod2->dest;
			}
            return nod1->effort > nod2->effort;						
		
        }
    };


void dijkstra(vector<Node*>* graph, int src)
{
	EdgeInfoByEffortComparator comparator;
	/** Set Destance from Source to Source to be Zero ! */
	(*graph)[src]->effort = 0;

	make_heap(graph->begin(), graph->end(), comparator);

	int it = 0;
	while(!graph->empty() && it < 15){
		Node* u = graph->front();
		pop_heap(graph->begin(), graph->end(), comparator);
		graph->pop_back();
		it++;
		cout<< "dest = " << u->name << " - effort = "<< u->effort << " - parent = " << u->parent_name << endl;

		Node* v = u->next;
		while(v){
			// check if v in Heap
			Node* v_in_Heap = NULL;
			for(int i = 0; i< graph->size(); i++){
				if((*graph)[i]->dest == v->dest){
					v_in_Heap = (*graph)[i];
					break;
				}
			}
			
			if(v_in_Heap){
				if(v->weight + u->effort < v_in_Heap->effort){
					v_in_Heap->effort = v->weight + u->effort;
					v_in_Heap->parent_name = u->name;
				}
			}
			v = v->next;
		}
		
	}	
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

	optimizeGraphHead(&graph);
	
	printGraph(graph);

	dijkstra(&graph, 0);

	return 0;
}

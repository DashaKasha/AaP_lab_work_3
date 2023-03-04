#include "Matrix.h"
#include <list>

using namespace std;

template <typename Tnode = double, typename Tweight = double>
class Graph {

private:
	int size;
	list<Tnode> nodes;
	Matrix<Tweight> adj;

public:

	Graph() {
		size = 0;
		adj(0,0);
	}


	//Graph(Matrix adj_, list nodes_) {
	//
	//	nodes = nodes_;
	//	size = nodes.size();
	//	adj = adj_;

	//}

	Graph(const Graph& graph)
	{
		size = graph.size;
		nodes = graph.nodes;
		adj = graph.adj;

	}

	Graph(Graph&& other)
	{
		size = other.size;
		nodes = other.nodes;
		adj = other.adj;
		other.size = 0;
		other.nodes = nullptr;
		other.adj = {};

	}

	Graph operator = (const Graph graph) 
	{
		size = graph.size;
		nodes = graph.nodes;
		adj = graph.adj;
	}

	Graph& operator=(Graph&& other)
	{
		size = other.size;
		nodes = other.nodes;
		adj = other.adj;
		other.size = 0;
		other.nodes = nullptr;
		other.adj = {};
	}


	bool empty() {
		return nodes.empty();
	}

	size_t size() {
		return nodes.size();
	}

	void clear() {
		nodes.clear();
		adj = {};  // разобраться с matrix.clear()
		size = 0;
	}

	void swap(Graph g) {
		
		Graph other = this;
		this = g;
		g = this;
		
		other.clear();
	
	}









	~Graph() {	}

};


int main()
{

	return 0;
}


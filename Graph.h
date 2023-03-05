#pragma once
#include "Node.h"
#include "Matrix.h"
#include <set>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;



template <typename Tnode = int, typename Tweight = int>
struct Edge {
	Tnode a_node;
	Tnode b_node;
	Tweight weight;
};


template <typename Tnode, typename Tweight>
class Graph {

private:
//int size;
	//list<Node<Tnode>> nodes;
	//map <Tkey, Tnode> nodes;
	set<Tnode> nodes;
	Matrix<Tweight> adj;
	int g_size;
	//using iterator = typename map<Tkey, Tnode>::iterator;
	//using const_iterator = typename map<Tkey, Tnode>::const_iterator;

public:

//	typedef OwnIterator	<Node<Tnode>> iterator;
//	typedef OwnIterator <const Node<Tnode>> const_iterator;


	Graph() = default;


	//Graph(Matrix adj_, list nodes_) {
	//
	//	nodes = nodes_;
	//	size = nodes.size();
	//	adj = adj_;

	//}

	Graph(const Graph<Tnode, Tweight>& graph)
	{
		g_size = graph.g_size;
		nodes = graph.nodes;
		adj = graph.adj;

	}

	Graph(Graph<Tnode, Tweight>&& other)
	{
		g_size = other.g_size;
		nodes = other.nodes;
		adj = other.adj;
		other.g_size = 0;
		other.nodes = nullptr;
		other.adj = {};

	}

	Graph<Tnode, Tweight> operator = (const Graph<Tnode, Tweight> graph)
	{
		g_size = graph.g_size;
		nodes = graph.nodes;
		adj = graph.adj;
		return *this;
	}

	Graph<Tnode, Tweight>& operator=(Graph<Tnode, Tweight>&& other)
	{
		g_size = other.g_size;
		nodes = other.nodes;
		adj = other.adj;
		other.g_size = 0;
		other.nodes = nullptr;
		other.adj = {};
		return *this;
	}


	bool empty() const {
		return nodes.empty();
	}

	size_t size() const{
		return nodes.size();
	}

	void clear() {
		nodes.clear();
		adj.clear();  // разобратьс€ с matrix.clear()
		g_size = 0;
	}

	void swap(Graph<Tnode, Tweight> g) {

		Graph<Tnode, Tweight> *tmp = this;
		this = &g;
		&g = this;
		//наверное лучше прописать своп у матриц и у ноды
		tmp.clear();

	}


	auto begin() {
		return nodes.begin();
	}

	auto c_begin() {
		return nodes.cbegin();
	}

	auto end() {
		return nodes.end();
	}

	auto c_end() {
		return nodes.begin();
	}



	size_t degree_in(Tnode key) {
		size_t count = 0;
		int index = 0;
		try {
			for (auto it = nodes.begin(); it != nodes.end( ); it++) {
				if (*it == key) { break; }
				index++;
			}
			
			for (int i = 0; i < nodes.size(); i++)
			{
				if (adj[i][index] != 0) { count++; } // или индексы наоборот, проверить
			}
			
			if (!count) {
				exception error("key hasn't been found");
				throw error;
			}
		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}

		return count;
	}

	size_t degree_out(Tnode key) {
	
		size_t count = 0;
		int index = 0;
		try {
			
			for (auto it = nodes.begin(); it != nodes.end(); it++) {
				if (*it == key) { break; }
				index++;
			}

			for (int i = 0; i < nodes.size(); i++)
			{
				if (adj[index][i] != 0) { count++; } // или индексы наоборот, проверить
			}

			if (!count) {
				exception error("key hasn't been found");
				throw error;
			}
		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}

		return count;
	
	}


	bool loop(Tnode key) {
		bool res = false;
		int index = 0;

		size_t count = 0;
		try {
			for (auto it = nodes.begin(); *it != key; it++) {
				index++;
			}

			if (adj[index][index] == 0) { res = true; }

			if (nodes.count(key) == 0) {
				exception error("key hasn't been found");
				throw error;
			}
		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}

		return res;


	}
	 


	auto insert_node(Tnode node)

	{	
		auto tmp_ = nodes.insert(node);
		int count = 0;
		Graph<Tnode, Tweight>* tmp = tmp.first(); ///////хз
		

		for (auto it = nodes.begin(); it = tmp; it++)
		{
			count++;
		}
		
		Matrix<Tweight> m(g_size + 1, g_size + 1);

		for (int i = 0; i < g_size; i++)
		{
			for (int j = 0, j < g_size; j++)
			{
				m[i][j] = adj[i][j];
			}
		}

		g_size++;

		for (int i = 0; i < g_size; i++) {

			m[i][g_size] = 0;
			m[g_size][i] = 0;

		}


		adj = m;
		return nodes.insert(node);
	}



	auto insert_edge(Tnode a, Tnode b, Tweight w) {
		
		bool res = true;
		try {
			if (nodes.count(a)==0 || nodes.count(b) == 0){
				res = false;
				exception error("key hasn't been found");
				throw error;
			}

		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}
		
		/*
		int index_a = 0;
		int index_b = 0;

		for (auto it = nodes.begin(); *it != a; it++)
		{
			index_a++;
		}

		for (auto it = nodes.begin(); *it != b; it++)
		{
			index_b++;
		}
		*/
		int index_a = distance(nodes.begin(), nodes.find(a));
		int index_b = distance(nodes.begin(), nodes.find(b));

		adj[index_a][index_b] = w; ////или индексы по другому
		
		auto answer = make_pair(nodes.find(a), res);
		return res;
	}

	auto insert_or_assign_edge(Tnode a, Tnode b, Tweight w) {
	
		bool res = true;
		try {
			if (nodes.count(a) == 0 || nodes.count(b) == 0) {
				res = false;
				exception error("key hasn't been found");
				throw error;
			}

		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}
	
		int index_a = distance(nodes.begin(), nodes.find(a));
		int index_b = distance(nodes.begin(), nodes.find(b));

		adj[index_a][index_b] = w; ////или индексы по другому
		
		auto answer = make_pair(nodes.find(a), res);
		return res;
	
	
	}


	void clear_edges() {
		
		Matrix<Tweight> tmp();
		adj = tmp;

	
	}

	bool erase_edges_go_from(Tnode key) {
		
		if (!nodes.count(key)) { return false; }

		int index = distance(nodes.begin(), nodes.find(key));///ѕроверить что правильно идет файнд
		for (int i = 0; i < g_size; i++)
		{
			adj[index][i] = 0;
		}
		
		return true;
	}

	bool erase_edges_go_to(Tnode key) {
	
		if (!nodes.count(key)) { return false; }

		int index = distance(nodes.begin(), nodes.find(key));///ѕроверить что правильно идет файнд
		for (int i = 0; i < g_size; i++)
		{
			adj[i][index] = 0;
		}

		return true;
	
	}

	bool erase_node(Tnode key) {
		
		if (!nodes.count(key)) { return false; }
	
		int index = distance(nodes.begin(), nodes.find(key));

		nodes.erase(key);

		for (int i = 0; i < g_size-1; i++)
		{
			for (int j = index; j < g_size-1; j++)
			{
				adj[i][index] = adj[i][index + 1];
				adj[index][i] = adj[index + 1][i];
			}
		}

		Matrix<Tweight> m(g_size - 1, g_size - 1);

		for (int i = 0; i < g_size; i++)
		{
			for (int j = 0; j < g_size; j++)
			{
				m[i][j] = adj[i][j];
			}
		}

		adj = m;

		return true;
	
	}



	bool load_from_file(const string &path) {
		
		ifstream in(path);
		if (in.is_open()) {
			string line;
			int condition = 0;

		}

	
	}


	void save_to_file(const string &path) {}



	~Graph() {	}

};
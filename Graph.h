#pragma once
#include "Matrix.h"
#include <set>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;


template <typename Tnode = double, typename Tweight = double>
class Graph {

private:

	set<Tnode> nodes;
	Matrix<Tweight> adj;
	int g_size;

public:


	Graph() = default;

	Graph(set<Tnode> nodes_, Matrix<Tweight> adj_) {

		nodes = nodes_;
		g_size = nodes.size();
		adj = adj_;

	}

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

	size_t size() const {
		return nodes.size();
	}

	void clear() {
		nodes.clear();
		adj.clear();  
		g_size = 0;
	}

	void swap(Graph<Tnode, Tweight> g) {

		Graph<Tnode, Tweight>* tmp = this;
		this = &g;
		&g = this;
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

			int flag = nodes.count(key);

			for (auto it = nodes.begin(); it != nodes.end(); it++) {
				if (*it == key) { break; }
				index++;
			}

			for (int i = 0; i < nodes.size(); i++)
			{
				if (adj(i, index) != 0) { count++; }
			}

			if (!flag) {
				std::invalid_argument error("key hasn't been found");
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
		int flag = nodes.count(key);
		try {

			for (auto it = nodes.begin(); it != nodes.end(); it++) {
				if (*it == key) { break; }
				index++;
			}

			for (int i = 0; i < nodes.size(); i++)
			{
				if (adj(index, i) != 0) { count++; }
			}

			if (!flag) {
				std::invalid_argument error("key hasn't been found");
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
			if (nodes.count(key) == 0) {
				std::invalid_argument error("key hasn't been found");
				throw error;
			}

			for (auto it = nodes.begin(); *it != key; it++) {
				index++;
			}

			if (adj(index, index) != 0) { res = true; }

		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}

		return res;


	}


	//////////
	auto insert_node(Tnode node) 

	{
		auto a = nodes.insert(node);

		int count = 0;


		for (auto it = nodes.begin(); it != nodes.find(node); it++)
		{
			count++;
		}

		Matrix<Tweight> m(g_size + 1, g_size + 1);

		for (int i = 0; i < g_size; i++)
		{
			for (int j = 0; j < g_size; j++)
			{
				m(i, j) = adj(i, j);
			}
		}

		g_size++;

		for (int i = 0; i < g_size; i++) {

			m(i, g_size) = 0;
			m(g_size, i) = 0;

		}

		adj = m;

		return a;
	}



	auto insert_edge(Tnode a, Tnode b, Tweight w) {

		bool res = true;
		try {
			if (nodes.count(a) == 0 || nodes.count(b) == 0) {
				res = false;
				std::invalid_argument error("key hasn't been found");
				throw error;
			}

		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}

		
		int index_a = distance(nodes.begin(), nodes.find(a));
		int index_b = distance(nodes.begin(), nodes.find(b));

		adj(index_a, index_b) = w; 

		auto answer = make_pair(nodes.find(a), res);
		return res;
	}

	auto insert_or_assign_edge(Tnode a, Tnode b, Tweight w) {

		bool res = true;
		try {
			if (nodes.count(a) == 0 || nodes.count(b) == 0) {
				res = false;
				std::invalid_argument error("key hasn't been found");
				throw error;
			}

		}
		catch (exception& err) {
			cout << err.what() << "\n";
		}

		int index_a = distance(nodes.begin(), nodes.find(a));
		int index_b = distance(nodes.begin(), nodes.find(b));

		adj(index_a, index_b) = w; 

		auto answer = make_pair(nodes.find(a), res);
		return res;


	}


	void clear_edges() {
		adj = adj.zero();
	}

	bool erase_edges_go_from(Tnode key) {

		if (!nodes.count(key)) { return false; }

		int index = distance(nodes.begin(), nodes.find(key));
		for (int i = 0; i < g_size; i++)
		{
			adj(index, i) = 0;
		}

		return true;
	}

	bool erase_edges_go_to(Tnode key) {

		if (!nodes.count(key)) { return false; }

		int index = distance(nodes.begin(), nodes.find(key));
		for (int i = 0; i < g_size; i++)
		{
			adj(i, index) = 0;
		}

		return true;

	}

	bool erase_node(Tnode key) {

		if (!nodes.count(key)) { return false; }

		int index = distance(nodes.begin(), nodes.find(key));

		nodes.erase(key);

		for (int i = 0; i < g_size - 1; i++)
		{
			for (int j = index; j < g_size - 1; j++)
			{
				adj(i, index) = adj(i, index + 1);
				adj(index, i) = adj(index + 1, i);
			}
		}

		g_size--;

		Matrix<Tweight> m(g_size, g_size);

		for (int i = 0; i < g_size; i++)
		{
			for (int j = 0; j < g_size; j++)
			{
				m(i, j) = adj(i, j);
			}
		}

		adj = m;

		return true;

	}


	bool load_from_file(const string& path) {
	
		ifstream in;
		in.open(path);
		if (!in) { return false; }

		int n;
		in >> n;
		for (auto i = 0; i < n; i++)
		{
			Tnode tmp;
			in >> tmp;
			insert_node(tmp);
		}

		in >> adj;
		in.close();
		return true;
	
	}



	bool save_to_file(const string &path) {
	
		ofstream out;
		out.open(path);
		if (!out) { return false; }

		out << g_size;
		out << "\nnodes: \n";
		for (auto it = nodes.begin(); it!=nodes.end(); it++)
		{
			out << *it;
		}

		out << "\nadjacency matrix: \n";
		out << adj;
		out.close();
		return true;
	}



	~Graph() {	}

};
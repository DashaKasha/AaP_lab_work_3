#include "Graph.h"
#include <set>

using namespace std;




int main()
{

    Matrix<int> matrix = { {0, 1, 0, 1},
                             {0, 1, 1, 0},
                             {0, 0, 0, 1},
                             {0, 0, 0, 0} };
    set<string> nodes = { "A", "B", "C", "D" };



    Graph<string, int> graph(nodes, matrix);


    // empty()
    cout << "graph is empty: " << graph.empty() << endl;
    // size()
    cout << "the size of graph: " << graph.size() << endl;
    // begin(), end()
    cout << "the begining of graph: " << *graph.begin() << endl;
    cout << "the second element in graph: " << *(++graph.begin()) << endl;
    cout << "the end of graph: " << *(--graph.end()) << endl;
    cout << "the second to lat element of the graph: " << *(--(--(graph.end()))) << endl << endl;
    // degree_in/out
    cout << "degree_in node A: " << graph.degree_in("A") << endl;
    cout << "degree_out node B: " << graph.degree_out("B") << endl;
    // loop
    cout << "loop node B: " << graph.loop("B") << endl;
    cout << "loop node aaaa: " << graph.loop("aaaa") << endl << endl;


    // insert_edge/node

    //graph.erase_node("A");
    //cout << "the size of graph after deleting A: " << graph.size() << endl;
    //graph.insert_node("A");


    graph.insert_edge("B", "D", 2);
    cout << "degree_out node B (after insert_edge B-D): " << graph.degree_out("B") << endl;

    cout << "degree_out node A (before insert_or_assign_edge A-B): " << graph.degree_out("A") << endl;
    graph.insert_or_assign_edge("A", "B", 3);
    cout << "degree_out node A (after insert_or_assign_edge A-B): " << graph.degree_out("A") << endl;


    graph.erase_edges_go_from("B");
    cout << "degree_out node B (after erase_edges_go_from B): " << graph.degree_out("B") << endl;

    graph.erase_edges_go_to("D");
    cout << "degree_in node D (after erase_edges_go_to D): " << graph.degree_in("D") << endl;

    Graph<string, int> graph1 = graph;
    cout << graph1.size() << endl;
    graph1.erase_node("D");
    cout << "the size of graph1 after erase_node D: " << graph1.size() << endl;


    graph1.clear_edges();
    cout << "degree_out node A (after graph1.clear_edges): " << graph1.degree_out("A") << endl;

    cout << "saving to file: " << graph.save_to_file("D:/учеба/C++/lab_work_3/lab_work_3/graph.txt");
    

	return 0;
}


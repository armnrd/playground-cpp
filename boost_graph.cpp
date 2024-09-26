//
// Created by Arindam on 23/09/2024.
//

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

using namespace std;
using namespace boost;

// Define the graph type
typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main() {
    Graph g;

    // Add edges to the graph
    add_edge(0, 1, g);
    add_edge(0, 2, g);
    add_edge(1, 3, g);
    add_edge(2, 3, g);
    add_edge(3, 4, g);

    // Output graph edges
    typedef graph_traits<Graph>::edge_iterator edge_iterator;
    pair<edge_iterator, edge_iterator> ei;
    for (ei = edges(g); ei.first != ei.second; ++ei.first) {
        cout << source(*ei.first, g) << " -> " << target(*ei.first, g) << endl;
    }

    return 0;
}

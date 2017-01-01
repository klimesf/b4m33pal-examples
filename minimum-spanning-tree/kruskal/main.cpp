#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*

 0 ==  8 == 1 == 15 == 2 == 13 == 3 ==  7 == 4 == 11 == 5
 |          |          ||         |          ||         |
 18         27          2         26          3         20
 |          |          ||         |          ||         |
 6 == 12 == 7 == 14 == 8 -- 17 -- 9 == 10 == 10 ==  5 ==11
 |          ||         |          |          |          |
 22          9         23         24         25         19
 |          ||         |          |          |          |
 12== 21 == 13==  4 == 14==  1 == 15== 16 == 16==  6 == 17


 */

#define NUMBER_OF_VERTICES 18
#define MINIMUM_SPANNING_TREE_PRICE 157

int adjacency_matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES] = {
        //0, 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17
        {0,  8,  0,  0,  0,  0,  18, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 0
        {8,  0,  15, 0,  0,  0,  0,  27, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 1
        {0,  15, 0,  13, 0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 2
        {0,  0,  13, 0,  7,  0,  0,  0,  0,  26, 0,  0,  0,  0,  0,  0,  0,  0}, // 3
        {0,  0,  0,  7,  0,  11, 0,  0,  0,  0,  3,  0,  0,  0,  0,  0,  0,  0}, // 4
        {0,  0,  0,  0,  11, 0,  0,  0,  0,  0,  0,  20, 0,  0,  0,  0,  0,  0}, // 5
        {18, 0,  0,  0,  0,  0,  0,  12, 0,  0,  0,  0,  22, 0,  0,  0,  0,  0}, // 6
        {0,  27, 0,  0,  0,  0,  12, 0,  14, 0,  0,  0,  0,  9,  0,  0,  0,  0}, // 7
        {0,  0,  2,  0,  0,  0,  0,  14, 0,  17, 0,  0,  0,  0,  23, 0,  0,  0}, // 8
        {0,  0,  0,  26, 0,  0,  0,  0,  17, 0,  10, 0,  0,  0,  0,  24, 0,  0}, // 9
        {0,  0,  0,  0,  3,  0,  0,  0,  0,  10, 0,  5,  0,  0,  0,  0,  25, 0}, // 10
        {0,  0,  0,  0,  0,  20, 0,  0,  0,  0,  5,  0,  0,  0,  0,  0,  0,  19}, // 11
        {0,  0,  0,  0,  0,  0,  22, 0,  0,  0,  0,  0,  0,  21, 0,  0,  0,  0}, // 12
        {0,  0,  0,  0,  0,  0,  0,  9,  0,  0,  0,  0,  21, 0,  4,  0,  0,  0}, // 13
        {0,  0,  0,  0,  0,  0,  0,  0,  23, 0,  0,  0,  0,  4,  0,  1,  0,  0}, // 14
        {0,  0,  0,  0,  0,  0,  0,  0,  0,  24, 0,  0,  0,  0,  1,  0,  16, 0}, // 15
        {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  25, 0,  0,  0,  0,  16, 0,  6}, // 16
        {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  19, 0,  0,  0,  0,  6,  0}, // 17
};

struct edge {
    int from, to, price;
};

struct tree_node {
    int index;
    tree_node *parent;

    tree_node() {
        parent = nullptr;
    }

    tree_node *find_parent() {
        if (this->parent == nullptr) {
            return this;
        } else {
            return this->parent->find_parent();
        }
    }

    void set_parent(tree_node *parent) {
        if (parent == nullptr) {
            throw "fuck";
        }
        this->parent = parent;
    }
};

bool compare_edges(edge i, edge j) { return (i.price < j.price); }

// Converts adjacency matrix to list of edges.
vector<edge> create_graph(int matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES]) {
    vector<edge> graph;
    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        for (int j = i; j < NUMBER_OF_VERTICES; ++j) {
            if (matrix[i][j] == 0) {
                continue;
            }
            edge e;
            e.from = i;
            e.to = j;
            e.price = matrix[i][j];
            graph.push_back(e);
        }
    }
    return graph;
}

// Naive kruskals algorithm with O(n) union find
unsigned naive_kruskals_algorithm(vector<edge> &graph) {
    sort(graph.begin(), graph.end(), compare_edges);

    unsigned price = 0;
    unsigned component[NUMBER_OF_VERTICES], number_of_components = NUMBER_OF_VERTICES;
    for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
        component[i] = i;
    }

    for (const auto e : graph) {
        if (number_of_components < 2) {
            break;
        }
        if (component[e.from] != component[e.to]) {
            unsigned to_merge = component[e.to];
            // If the edge doesn't make edge, merge
            for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
                if (component[i] == to_merge) {
                    component[i] = component[e.from];
                }
            }
            --number_of_components;
            price += e.price;
        }
    }

    return price;
}

// Kruskals algorithm with union find implemented by directed tree
unsigned directed_tree_kruskals_algorithm(vector<edge> &graph) {
    sort(graph.begin(), graph.end(), compare_edges);

    unsigned price = 0, number_of_components = NUMBER_OF_VERTICES;
    tree_node *tree = new tree_node[NUMBER_OF_VERTICES];
    for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
        tree[i].index = i;
    }

    for (const auto e : graph) {
        if (number_of_components < 2) {
            break;
        }
        if (tree[e.from].find_parent()->index != tree[e.to].find_parent()->index) {
            tree[e.to].find_parent()->set_parent(tree[e.from].find_parent());
            --number_of_components;
            price += e.price;
        }
    }
    delete[] tree;

    return price;
}

int main() {
    vector<edge> graph = create_graph(adjacency_matrix);
    cout << "Kruskal's algorithm output with naive union find: " << naive_kruskals_algorithm(graph) << endl;
    cout << "Kruskal's algorithm output with directed tree union find: " << directed_tree_kruskals_algorithm(graph)
         << endl;
    cout << "Correct price: " << MINIMUM_SPANNING_TREE_PRICE << endl;
    return 0;
}

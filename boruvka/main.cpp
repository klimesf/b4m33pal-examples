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

unsigned adjacency_matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES] = {
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
    unsigned from, to, price;
};

vector<edge> *create_adjacency_list(unsigned matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES]) {
    vector<edge> *list = new vector<edge>[NUMBER_OF_VERTICES];

    for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
        for (unsigned j = 0; j < NUMBER_OF_VERTICES; ++j) {
            if (matrix[i][j] < 1) {
                continue;
            }
            edge e;
            e.from = i;
            e.to = j;
            e.price = matrix[i][j];
            list[i].push_back(e);
        }
    }

    return list;
}

unsigned boruvka_algorithm(vector<edge> *list) {

    unsigned price = 0, number_of_components = NUMBER_OF_VERTICES;

    unsigned components[NUMBER_OF_VERTICES];
    for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
        components[i] = i;
    }

    // Iterate through every vertex and choose the edge with minimum price
    vector<edge> used_edges;
    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        unsigned min_price = -1;
        const edge *min_edge;
        for (const auto &e : list[i]) {
            if (e.price < min_price) {
                min_price = e.price;
                min_edge = &e;
            }
        }
        used_edges.push_back(*min_edge);
    }
    // Merge components using the cheapest edges
    for (const auto &e : used_edges) {
        if (components[e.from] == components[e.to]) {
            // Protection from duplicate edges
            continue;
        }
        unsigned to_merge = components[e.to];
        price += e.price;
        for (int j = 0; j < NUMBER_OF_VERTICES; ++j) {
            if (components[j] == to_merge) {
                components[j] = components[e.from];
            }
        }
        --number_of_components;
    }

    // Iterate through components and choose the edge with minimum price
    while (number_of_components > 1) {
        vector<edge> *edges = new vector<edge>[NUMBER_OF_VERTICES];
        unsigned min_price[NUMBER_OF_VERTICES];
        const edge *min_edge[NUMBER_OF_VERTICES];
        for (int k = 0; k < NUMBER_OF_VERTICES; ++k) {
            min_edge[k] = nullptr;
        }

        // Find the cheapest edges from components
        for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
            for (const auto &e : list[i]) {
                if (components[e.from] == components[e.to]) {
                    // Protection from inter-component edge
                    continue;
                }
                if (e.price < min_price[components[i]]) {
                    min_price[components[i]] = e.price;
                    min_edge[components[i]] = &e;
                }
            }
        }

        // Merge components using the cheapest edges
        for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
            if (min_edge[i] == nullptr) {
                continue;
            }
            edge e = *min_edge[i];
            unsigned to_merge = components[e.to];
            price += e.price;
            for (int j = 0; j < NUMBER_OF_VERTICES; ++j) {
                if (components[j] == to_merge) {
                    components[j] = components[e.from];
                }
            }
            --number_of_components;
        }

        delete[] edges;
    }

    return price;
}

int main() {
    vector<edge> *list = create_adjacency_list(adjacency_matrix);
    cout << "Boruvka's algorithm price: " << boruvka_algorithm(list) << endl;
    cout << "Correct price: " << MINIMUM_SPANNING_TREE_PRICE << endl;
    delete[] list;
    return 0;
}

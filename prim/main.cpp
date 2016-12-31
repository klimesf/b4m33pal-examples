#include <iostream>

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
        //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17
        { 0, 8, 0, 0, 0, 0,18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
        { 8, 0,15, 0, 0, 0, 0,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
        { 0,15, 0,13, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
        { 0, 0,13, 0, 7, 0, 0, 0, 0,26, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
        { 0, 0, 0, 7, 0,11, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0}, // 4
        { 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,20, 0, 0, 0, 0, 0, 0}, // 5
        {18, 0, 0, 0, 0, 0, 0,12, 0, 0, 0, 0,22, 0, 0, 0, 0, 0}, // 6
        { 0,27, 0, 0, 0, 0,12, 0,14, 0, 0, 0, 0, 9, 0, 0, 0, 0}, // 7
        { 0, 0, 2, 0, 0, 0, 0,14, 0,17, 0, 0, 0, 0,23, 0, 0, 0}, // 8
        { 0, 0, 0,26, 0, 0, 0, 0,17, 0,10, 0, 0, 0, 0,24, 0, 0}, // 9
        { 0, 0, 0, 0, 3, 0, 0, 0, 0,10, 0, 5, 0, 0, 0, 0,25, 0}, // 10
        { 0, 0, 0, 0, 0,20, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0,19}, // 11
        { 0, 0, 0, 0, 0, 0,22, 0, 0, 0, 0, 0, 0,21, 0, 0, 0, 0}, // 12
        { 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0,21, 0, 4, 0, 0, 0}, // 13
        { 0, 0, 0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 4, 0, 1, 0, 0}, // 14
        { 0, 0, 0, 0, 0, 0, 0, 0, 0,24, 0, 0, 0, 0, 1, 0,16, 0}, // 15
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,25, 0, 0, 0, 0,16, 0, 6}, // 16
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19, 0, 0, 0, 0, 6, 0}, // 17
};

int prims_algorithm(int matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES], unsigned starting_vertex) {
    int price = 0;
    bool tree[NUMBER_OF_VERTICES] = {}; // Very naive implementation
    tree[starting_vertex] = true;
    int connected_vertices = 1;

    while (connected_vertices < NUMBER_OF_VERTICES) {
        unsigned min_price = -1, add = starting_vertex;
        for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
            if (tree[i]) {
                for (unsigned j = 0; j < NUMBER_OF_VERTICES; ++j) {
                    if (matrix[i][j] > 0 && matrix[i][j] < min_price && !tree[j]) {
                        min_price = (unsigned int) matrix[i][j];
                        add = j;
                    }
                }
            }
        }
        tree[add] = true;
        price += min_price;
        ++connected_vertices;
    }

    return price;
}

int main() {
    cout << "Prims algorithm output: " << prims_algorithm(adjacency_matrix, 0) << endl;
    cout << "Correct price: " << MINIMUM_SPANNING_TREE_PRICE << endl;
    return 0;
}

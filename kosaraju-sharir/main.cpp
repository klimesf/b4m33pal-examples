#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
              <- 
  A -> B -> C -> D
  ^  / |    |   ^|
  | ˇ  ˇ    ˇ   |ˇ
  E -> F -> G <- H
         <-

  3 strongly connected components:
  A B E
  F G
  C D H
 */

#define NUMBER_OF_VERTICES 8

#define UNVISITED 0
#define OPEN 1
#define CLOSED 2

typedef unsigned matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];
typedef unsigned vector<unsigned> *adjacency_list;
typedef unsigned vertex_state[NUMBER_OF_VERTICES];

matrix adjacency_matrix = {
        //A B  C  D  E  F  G  H
        {0, 1, 0, 0, 0, 0, 0, 0}, // A
        {0, 0, 1, 0, 1, 1, 0, 0}, // B
        {0, 0, 0, 1, 0, 0, 1, 0}, // C
        {0, 0, 1, 0, 0, 0, 0, 1}, // D
        {1, 0, 0, 0, 0, 1, 0, 0}, // E
        {0, 0, 0, 0, 0, 0, 1, 0}, // F
        {0, 0, 0, 0, 0, 1, 0, 0}, // G
        {0, 0, 0, 1, 0, 0, 1, 0}, // H
};

adjacency_list adjacency_matrix_to_list(matrix) {

}

void copy_matrix(matrix a, matrix &b) {
    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        for (int j = 0; j < NUMBER_OF_VERTICES; ++j) {
            b[i][j] = a[i][j];
        }
    }
}

void swap_directions(matrix a, matrix &b) {
    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        for (int j = 0; j < NUMBER_OF_VERTICES; ++j) {
            if (a[i][j] == 1 && a[j][i] == 0) {
                b[i][j] = 0;
                b[j][i] = 1;
            }
        }
    }
}

void dfs_walk(matrix adjacency_matrix,
              unsigned index,
              vertex_state &data,
              stack<unsigned> &stack,
              bool on_stack[NUMBER_OF_VERTICES],
              bool push) {
    data[index] = OPEN;
    for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
        if (adjacency_matrix[index][i] == 1 && data[i] == UNVISITED) {
            dfs_walk(adjacency_matrix, i, data, stack, on_stack, push);
        }
    }
    data[index] = CLOSED;
    if (push) {
        on_stack[index] = true;
        stack.push(index);
    } else {
        cout << (char) ((int) 'A' + index) << endl;
    }
}

void kosaraju_sharir(matrix adjacency_matrix) {
    stack<unsigned> stack;
    vertex_state state;
    bool on_stack[NUMBER_OF_VERTICES];
    unsigned time;

    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        state[i] = UNVISITED;
        on_stack[i] = false;
    }

    // While stack doesn't contain all vertices, dfs_walk and push to stack
    while (stack.size() < NUMBER_OF_VERTICES) {
        unsigned index = 0;
        for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
            if (!on_stack[i]) {
                index = i;
                break;
            }
        }
        dfs_walk(adjacency_matrix, index, state, stack, on_stack, true);
    }

    // Swap directions of edges in graph
    matrix swapped_matrix;
    copy_matrix(adjacency_matrix, swapped_matrix);
    swap_directions(adjacency_matrix, swapped_matrix);
    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        state[i] = UNVISITED;
    }

    // While stack is non-empty, dfs_walk swapped graph and search for components
    unsigned counter = 1;
    while (stack.size() > 0) {
        unsigned index = stack.top();
        stack.pop();
        if (state[index] != UNVISITED) {
            continue;
        }

        cout << "Component " << counter++ << ":" << endl;
        dfs_walk(swapped_matrix, index, state, stack, on_stack, false);
        cout << endl;
    }
}

int main() {
    kosaraju_sharir(adjacency_matrix);
    return 0;
}

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

struct linked_list_element {
    unsigned data;
    linked_list_element *next;

    void add(unsigned data) {
        if (next != nullptr) {
            next->add(data);
            return;
        }
        next = new linked_list_element();
        next->data = data;
    }

    linked_list_element() {
        next = nullptr;
    }

    linked_list_element(unsigned data) : data(data) {
        next = nullptr;
    }

    virtual ~linked_list_element() {
        if (next != nullptr) {
            delete next;
        }
    }
};

typedef unsigned matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];
typedef linked_list_element **adjacency_list;
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

adjacency_list matrix_to_list(matrix adjacency_matrix) {
    adjacency_list list = new linked_list_element *[NUMBER_OF_VERTICES];
    for (unsigned i = 0; i < NUMBER_OF_VERTICES; ++i) {
        list[i] = nullptr;
        for (unsigned j = 0; j < NUMBER_OF_VERTICES; ++j) {
            if (adjacency_matrix[i][j] == 1) {
                if (list[i] == nullptr) {
                    list[i] = new linked_list_element(j);
                } else {
                    list[i]->add(j);
                }
            }
        }
    }
    return list;
}

void swap_directions(adjacency_list a, adjacency_list &b) {
    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        linked_list_element *current = a[i];
        while (current != nullptr) {
            if (b[current->data] == nullptr) {
                b[current->data] = new linked_list_element(i);
            } else {
                b[current->data]->add(i);
            }
            current = current->next;
        }
    }
}

void dfs_walk(adjacency_list list, unsigned index, vertex_state &state, stack<unsigned> &stack,
              bool on_stack[NUMBER_OF_VERTICES], bool push) {

    state[index] = OPEN;

    linked_list_element *current = list[index];
    while (current != nullptr) {
        if (state[current->data] == UNVISITED) {
            dfs_walk(list, current->data, state, stack, on_stack, push);
        }
        current = current->next;
    }

    state[index] = CLOSED;
    if (push) {
        on_stack[index] = true;
        stack.push(index);
    } else {
        cout << (char) ((int) 'A' + index) << endl;
    }
}

void kosaraju_sharir(adjacency_list list) {
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
        dfs_walk(list, index, state, stack, on_stack, true);
    }

    // Swap directions of edges in graph
    adjacency_list swapped_list = new linked_list_element *[NUMBER_OF_VERTICES];
    for (int j = 0; j < NUMBER_OF_VERTICES; ++j) {
        swapped_list[j] = nullptr;
    }

    swap_directions(list, swapped_list);
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
        dfs_walk(swapped_list, index, state, stack, on_stack, false);
        cout << endl;
    }

    delete[] swapped_list;
}

int main() {
    adjacency_list list = matrix_to_list(adjacency_matrix);
    kosaraju_sharir(list);
    delete[] list;
    return 0;
}

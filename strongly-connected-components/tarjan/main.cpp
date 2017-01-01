#include <iostream>
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

struct linked_list_element {
    unsigned v;
    linked_list_element *next;

    void add(unsigned v) {
        if (next != nullptr) {
            next->add(v);
            return;
        }
        next = new linked_list_element();
        next->v = v;
    }

    linked_list_element() {
        next = nullptr;
    }

    linked_list_element(unsigned v) : v(v) {
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

// --- Tarjan ----------------------------------------------------------------------------------------------------------

unsigned lowlink[NUMBER_OF_VERTICES] = {};
unsigned v_index[NUMBER_OF_VERTICES] = {};
int predecessor[NUMBER_OF_VERTICES] = {};
bool instack[NUMBER_OF_VERTICES] = {};
unsigned SCC_count = 0;
stack<unsigned> S;
unsigned current_index = 0;


void push(unsigned v, stack<unsigned> &S) {
    if (S.size() < 1) {
        predecessor[v] = -1;
    } else {
        predecessor[v] = S.top();
    }
    instack[v] = true;
    S.push(v);
}

unsigned pop(stack<unsigned> &S) {
    unsigned v = S.top();
    S.pop();
    predecessor[v] = -1;
    instack[v] = false;
    return v;
}

void find_scc(unsigned v, adjacency_list list) {
    v_index[v] = lowlink[v] = ++current_index;
    push(v, S);

    linked_list_element *current = list[v];
    while (current != nullptr) {
        if (v_index[current->v] == 0) {
            find_scc(current->v, list);
            lowlink[v] = lowlink[v] < lowlink[current->v] ? lowlink[v] : lowlink[current->v];
        } else if (instack[current->v]) {
            lowlink[v] = lowlink[v] < v_index[current->v] ? lowlink[v] : v_index[current->v];
        }
        current = current->next;
    }

    if (lowlink[v] == v_index[v]) {
        ++SCC_count;
        unsigned x;
        linked_list_element *component = nullptr;
        do {
            x = pop(S);
            if (component == nullptr) {
                component = new linked_list_element(x);
            } else {
                component->add(x);
            }
        } while (x != v);

        cout << "Component " << SCC_count << ":" << endl;
        current = component;
        while (current != nullptr) {
            cout << (char) ((int) 'A' + current->v) << " ";
            current = current->next;
        }
        cout << endl;
    }
}


int main() {
    adjacency_list list = matrix_to_list(adjacency_matrix);

    for (int i = 0; i < NUMBER_OF_VERTICES; ++i) {
        if (v_index[i] == 0) {
            find_scc(i, list);
        }
    }

    delete[] list;
    return 0;
}

// --- End Tarjan ------------------------------------------------------------------------------------------------------

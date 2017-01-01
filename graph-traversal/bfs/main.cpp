#include <iostream>
#include <queue>

using namespace std;

//    B     D
//  /      /
// A     C -- E
//  \  /  \   |
//   I    F   |
//    \  /    |
//     G ---- H

#define MATRIX_SIZE 9

int adjacency_matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        //A,B, C, D, E, F, G, H, I
        {0, 1, 0, 0, 0, 0, 0, 0, 1}, //A
        {1, 0, 0, 0, 0, 0, 0, 0, 0}, //B
        {0, 0, 0, 1, 1, 1, 0, 0, 1}, //C
        {0, 0, 1, 0, 0, 0, 0, 0, 0}, //D
        {0, 0, 1, 0, 0, 0, 0, 1, 0}, //E
        {0, 0, 1, 0, 0, 0, 1, 0, 0}, //F
        {0, 0, 0, 0, 0, 1, 0, 1, 1}, //G
        {0, 0, 0, 0, 1, 0, 1, 0, 0}, //H
        {1, 0, 1, 0, 0, 0, 1, 0, 0}, //I
};

void breadth_first_search(int matrix[MATRIX_SIZE][MATRIX_SIZE], int start) {
    queue<int> queue;
    bool visited[MATRIX_SIZE] = {};
    visited[start] = true;

    queue.push(start);
    while (queue.size() > 0) {
        int current = queue.front();
        queue.pop();

        // Do your logic here
        cout << (char)(current + (int)'A') << endl;

        for (int i = MATRIX_SIZE - 1; i >= 0; --i) { // Reverse for to go in alphabet order
            if (current == i) {
                continue;
            }
            if (matrix[current][i] > 0 && !visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    breadth_first_search(adjacency_matrix, 0);
    return 0;
}

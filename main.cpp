#include <iostream>
#include "Node.h"
#include "helpfunctions.h"
using namespace std;

vector<Node> expand(int puzzle[N][N]) {
    int temp_array[N][N];
    int row, col = 0;
    find_zero(puzzle, row, col);
    vector<Node> list;
    for (int i = 0; i < 4; i++) {
        copy(&puzzle[0][0], &puzzle[0][0] + N * N, &temp_array[0][0]);
        //up
        if (row > 0) {
            if (i == 0) {
                move_up(temp_array);
                Node temp(temp_array);
                list.push_back(temp);
            }
        }
        //down
        if (row < 2) {
            if (i == 1) {
                move_down(temp_array);
                Node temp(temp_array);
                list.push_back(temp);
            }
        }
        //left
        if (col > 0) {
            if (i == 2) {
                move_left(temp_array);
                Node temp(temp_array);
                list.push_back(temp);
            }
        }
        //right
        if (col < 2) {
            if (i == 3) {
                move_right(temp_array);
                Node temp(temp_array);
                list.push_back(temp);
            }
        }
    }
    return list;
}
void general_search(){

}
int main() {
    int array[N][N];
    int puzzle_mode = 0;
    vector<Node> list;
    string puzzle_row_one, puzzle_row_two, puzzle_row_three;
    print_intro();
    cin >> puzzle_mode;
    if (puzzle_mode == 1) {
        init_default_puzzle();
        select_and_init_algo();
    }
    if (puzzle_mode == 2) {
        print_CreateOwn();
        user_input_puzzle();
        select_and_init_algo();
    }
    Node test(user_puzzle);
    print_Puzzle(test.nodePuzzle);
}
//How to copy array to another
//copy(&trivial[0][0],&trivial[0][0]+ N*N,&user_puzzle[0][0]);
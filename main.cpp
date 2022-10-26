#include <iostream>
#include <queue>
#include "Node.h"
#include "helpfunctions.h"
using namespace std;
//https://cplusplus.com/reference/queue/priority_queue/priority_queue/
//referenced from priority_queue c++
struct comp{
    bool operator()(const Node lhs, const Node rhs)const{
        return (lhs.g_of_n+lhs.h_of_n > rhs.g_of_n+rhs.h_of_n);
    }
};


vector<Node> expand(int puzzle[N][N],const unordered_map<string,bool>seen) {
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
                if(seen.count(temp.current_state)==0){
                    list.push_back(temp);
                }
            }
        }
        //down
        if (row < 2) {
            if (i == 1) {
                move_down(temp_array);
                Node temp(temp_array);
                if(seen.count(temp.current_state)==0){
                    list.push_back(temp);
                }
            }
        }
        //left
        if (col > 0) {
            if (i == 2) {
                move_left(temp_array);
                Node temp(temp_array);
                if(seen.count(temp.current_state)==0){
                    list.push_back(temp);
                }
            }
        }
        //right
        if (col < 2) {
            if (i == 3) {
                move_right(temp_array);
                Node temp(temp_array);
                if(seen.count(temp.current_state)==0){
                    list.push_back(temp);
                }
            }
        }
    }
    return list;
}
void general_search(int puzzle[N][N],int heuristic){
    Node head_puzzle(puzzle);

    //https://cplusplus.com/reference/queue/priority_queue/priority_queue/
    priority_queue<Node,vector<Node>,comp> states;
    unordered_map<string,bool>seen;
    unsigned int size = states.size();
    unsigned int nodes_size =0;
    states.push(head_puzzle);

}
int main() {
    unordered_map<string,bool> map_test;
    int array[N][N];
    int puzzle_mode = 0;
    vector<Node> list;
    string puzzle_row_one, puzzle_row_two, puzzle_row_three;
    print_intro();
    cin >> puzzle_mode;
    if (puzzle_mode == 1) {
        init_default_puzzle();
        general_search(user_puzzle,select_and_init_algo());
    }
    if (puzzle_mode == 2) {
        print_CreateOwn();
        user_input_puzzle();
        general_search(user_puzzle,select_and_init_algo());
    }
    Node test(user_puzzle);
    print_Puzzle(test.nodePuzzle);

}
//How to copy array to another
//copy(&trivial[0][0],&trivial[0][0]+ N*N,&user_puzzle[0][0]);

//how to insert into list and map
/*map_test.insert(pair<string,bool>(test.current_state,false));
list=expand(test.nodePuzzle,map_test);
for(int i=0;i<list.size();i++){
    cout<<"i: "<<i<<endl;
    print_Puzzle(list[i].nodePuzzle);
    cout<<endl;
    map_test.insert(pair<string,bool>(list[i].current_state,false));
}
list = expand(list[0].nodePuzzle,map_test);
for(int i=0;i<list.size();i++){
    cout<<"i: "<<i<<endl;
    print_Puzzle(list[i].nodePuzzle);
    cout<<endl;
}*/
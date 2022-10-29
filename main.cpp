#include <iostream>
#include <queue>
#include "Node.h"
#include "helpfunctions.h"
#include <chrono>
using namespace std;
//https://cplusplus.com/reference/queue/priority_queue/priority_queue/
//referenced from priority_queue c++
struct comp{
    bool operator()(const Node& lhs, const Node& rhs) const{
        return ((lhs.getF_of_N()) > (rhs.getF_of_N()));
    }
};

//used an unordered set to improve lookup times of strings worst case O(n) but best case O(1) linear time
vector<Node> expand(Node& current,unordered_set<string>&seen,int heuristic) {
    int row, col = 0;
    find_zero(current.nodePuzzle, row, col);
    vector<Node> list;
    for (int i = 0; i < 4; i++) {
        //up
        if (row > 0) {
            if (i == 0) {
                Node temp(current);
                temp.move_up();
                if(seen.count(temp.current_state)==0){
                    temp.g_of_n++;
                    temp.depth++;
                    temp.setF_of_N(heuristic);
                    current.child_u=&temp;
                    list.push_back(temp);
                    seen.insert(temp.current_state);
                }
            }
        }
        //down
        if (row < 2) {
            if (i == 1) {
                Node temp(current);
                temp.move_down();
                if(seen.count(temp.current_state)==0){
                    temp.g_of_n++;
                    temp.depth++;
                    temp.setF_of_N(heuristic);
                    current.child_d=&temp;
                    list.push_back(temp);
                    seen.insert(temp.current_state);
                }
            }
        }
        //left
        if (col > 0) {
            if (i == 2) {
                Node temp(current);
                temp.move_left();
                if(seen.count(temp.current_state)==0){
                    temp.g_of_n++;
                    temp.depth++;
                    temp.setF_of_N(heuristic);
                    current.child_l=&temp;
                    list.push_back(temp);
                    seen.insert(temp.current_state);
                }
            }
        }
        //right
        if (col < 2) {
            if (i == 3) {
                Node temp(current);
                temp.move_right();
                if(seen.count(temp.current_state)==0){
                    temp.g_of_n++;
                    temp.depth++;
                    temp.setF_of_N(heuristic);
                    current.child_r=&temp;
                    list.push_back(temp);
                    seen.insert(temp.current_state);
                }
            }
        }
    }
    return list;
}
void general_search(int puzzle[N][N],int heuristic){
    //make head node
    auto start = chrono::steady_clock::now();
    Node head_puzzle(puzzle);
    vector<Node>list;
    bool first = true;
    //make queue
    priority_queue<Node,vector<Node>,comp> pq;
    unordered_set<string> seen_before;
    unsigned int pq_size = pq.size(); //max pq size
    unsigned int nodes_size =0;
    pq.push(head_puzzle);
    while(!pq.empty()){
        if(pq.empty()){
            cout<<"Failure!"<<endl;
            return;
        }
        pq_size<pq.size() ? pq_size=pq.size() : pq_size;
        Node temp = pq.top();
        pq.pop();
        if(first){
            seen_before.insert(temp.current_state);
            cout<<"Starting Board: "<<endl;
            first = false;
        }
        if(temp.isGoal()){
            auto end = chrono::steady_clock::now();
            cout<<"Goal State!: "<<endl;
            print_Puzzle(temp.nodePuzzle);
            cout<<"Solution depth was: "<<temp.depth<<endl;
            cout<<"Number of nodes expanded: "<<nodes_size<<endl;
            cout<<"Max queue size: "<<pq_size<<endl;
            cout<<"Elapsed Time in seconds: "<<chrono::duration_cast<chrono::seconds>(end-start).count()<<endl;
            return;
        }
        if(pq_size > 1){
            cout<<"Best solution to expand with a g(n)= "<<temp.g_of_n<<" and h(n) = "<<temp.h_of_n<<" is..."<<endl;
        }
        print_Puzzle(temp.nodePuzzle);
        list=expand(temp,seen_before,heuristic);
        for(auto & i : list){
            pq.push(i);
        }
        nodes_size++;
    }

}
int main() {
    int puzzle_mode = 0;
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


}

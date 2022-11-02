//
// Created by Dexter on 10/23/2022.
//
#ifndef EIGHT_PUZZLE_NODE_H
#define EIGHT_PUZZLE_NODE_H
#include <iostream>
#include "bits/stdc++.h"
#include "helpfunctions.h"
using namespace std;
class Node {
public:
    //Empty intializer to create temp Nodes
    Node(){
        h_of_n =0;
        depth = 0;
        g_of_n = 0;
        current_state="";
        //used but not implemented
        child_u= nullptr;
        child_d= nullptr;
        child_l= nullptr;
        child_r= nullptr;
    }
    //Uses a Node to initialize the class (mainly used to create new nodes for expand function)
    explicit Node(Node* prev){
        this->h_of_n=prev->h_of_n;
        this->depth=prev->g_of_n;
        this->g_of_n=prev->g_of_n;
        copyPuzzle(prev->nodePuzzle);
        this->current_state= prev->current_state;
        //used but not implemented (was working on returning optimal path)
        this->child_u= nullptr;
        this->child_d= nullptr;
        this->child_l= nullptr;
        this->child_r= nullptr;
    }
    //Uses a 2d array to initialize the Node (mainly used for the 2d array that is passed in by the user)
    explicit Node(int puzzle [N][N]){
        this->h_of_n=0;
        this->depth=0;
        this->g_of_n=0;
        copyPuzzle(puzzle);
        this->current_state= change_to_string(puzzle);
        //used but not implemented (was working on returning optimal path)
        this->child_u= nullptr;
        this->child_d= nullptr;
        this->child_l= nullptr;
        this->child_r= nullptr;
    }
    //create variables for Node puzzles
    int nodePuzzle [N][N]{};
    Node* child_u;
    Node* child_d;
    Node* child_l;
    Node* child_r;
    int h_of_n;
    int depth;
    int g_of_n;
    string current_state;

    //--------------------------Functions--------------------------------

    //Function copyPuzzle(int puzzle[N][N]): This function will copy a puzzle into its current nodePuzzle variable
    // copy() referenced from https://stackoverflow.com/questions/18709577/stdcopy-two-dimensional-array
    void copyPuzzle(int puzzle[N][N]){
        copy(&puzzle[0][0],&puzzle[0][0]+ N*N,&nodePuzzle[0][0]);
    }
    //Function getF_of_N(): This puzzle will return the Node's f(n)
    int getF_of_N() const{
        return (this->g_of_n+this->h_of_n);
    }
    //Function change_to_string(int puzzle[N][N]): Given a 2d puzzle, this function will change its 2d araray
    // into a 1d string which goes in order from top left -> bottom right
    static string change_to_string(int puzzle[N][N]){
        string output;
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                output.push_back(puzzle[i][j]+'0');
            }
        }
        return output;
    }
    //Function isGoal(): This function checks to see if the current Node is the goal state by examining its puzzle
    bool isGoal(){
        for(int i=0; i< N;i++){
            for(int j=0; j<N;j++){
                if(this->nodePuzzle[i][j] != eight_goal_state[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    //Function setF_of_N(int heuristic): This function sets the Node's h_of_n to the heuristic chosen by the user
    void setF_of_N(int heuristic){
        //uniform cost search (hard coded to 0)
        if(heuristic==1){
            this->h_of_n=0;
        }
        //A* misplaced
        else if(heuristic==2){
            this->h_of_n=misplaced();
        }
        //A* manhattan distance
        else if(heuristic==3){
            this->h_of_n=manhattan_distance();
        }
    }
    //Function misplaced(): This function is used to calculate the current Node puzzle h(n), using misplaced heuristic
    int misplaced(){
        int total_count=0;
        for(int i=0; i<goal_state.size();i++){
            if((this->current_state[i] != goal_state[i]) && this->current_state[i]!=0){
                total_count++;
            }
        }
        return total_count;
    }
    //Function manhattan_distance(): This function is used to calculate the current Node h(n), using manhattan_distance
    int manhattan_distance(){
        int total_count=0;
        int cur_r,cur_c=0;
        int goal_r,goal_c=0;
        bool node_set = false;
        bool goal_set = false;
        //for each number in the 8 puzzle 1-8 (not counting 0) loop
        for(int num = 1; num<this->current_state.size();num++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if(this->nodePuzzle[i][j]==num){ //check all of the numbers in the puzzle to see if it matches the num
                        cur_r=i;
                        cur_c=j;
                        node_set=true;
                    }
                    if(eight_goal_state[i][j]==num){ //check to see if the goal state matches the num
                        goal_r=i;
                        goal_c=j;
                        goal_set=true;
                    }
                    if(goal_set && node_set){ //this will cause it to break out of the iteration so its not that long of a loop
                        break;
                    }
                }
            }
            node_set=false;
            goal_set=false;
            total_count +=(abs(goal_r-cur_r)+abs(goal_c-cur_c)); //now just calulate the distance
        }
        return total_count;
    }
    //Function move_up(): This function moves the Node's puzzle up
    //Swap function referenced from https://cplusplus.com/reference/algorithm/swap/
    void move_up() {
        int i, j = 0;
        find_zero(this->nodePuzzle, i, j);                  //find blank
        swap(this->nodePuzzle[i][j], this->nodePuzzle[i - 1][j]); //swap it with the element directly above it
        this->current_state= change_to_string(this->nodePuzzle);
    }
    //Function move_down(): This function moves the Node's puzzle up
    //Swap function referenced from https://cplusplus.com/reference/algorithm/swap/
    void move_down(){
        int i,j=0;
        find_zero(this->nodePuzzle,i,j);
        swap(this->nodePuzzle[i][j],this->nodePuzzle[i+1][j]);
        this->current_state= change_to_string(this->nodePuzzle);
    }
    //Function move_left(): This function moves the Node's puzzle up
    //Swap function referenced from https://cplusplus.com/reference/algorithm/swap/
    void move_left(){
        int i,j=0;
        find_zero(this->nodePuzzle,i,j);
        swap(this->nodePuzzle[i][j],this->nodePuzzle[i][j-1]);
        this->current_state= change_to_string(this->nodePuzzle);
    }
    //Function move_right(): This function moves the Node's puzzle up
    //Swap function referenced from https://cplusplus.com/reference/algorithm/swap/
    void move_right(){
        int i,j=0;
        find_zero(this->nodePuzzle,i,j);
        swap(this->nodePuzzle[i][j],this->nodePuzzle[i][j+1]);
        this->current_state= change_to_string(this->nodePuzzle);
    }
    //unused, wanted to print the direct path to the goal state
    void printOptimalPath(){

    }

};


#endif //EIGHT_PUZZLE_NODE_H

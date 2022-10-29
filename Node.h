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
    Node(){
        h_of_n =0;
        depth = 0;
        g_of_n = 0;
        current_state="";
        child_u= nullptr;
        child_d= nullptr;
        child_l= nullptr;
        child_r= nullptr;
    }
    explicit Node(Node* prev){
        this->h_of_n=prev->h_of_n;
        this->depth=prev->g_of_n;
        this->g_of_n=prev->g_of_n;
        copyPuzzle(prev->nodePuzzle);
        this->current_state= prev->current_state;
        this->child_u= prev->child_u;
        this->child_d= prev->child_d;
        this->child_l= prev->child_l;
        this->child_r= prev->child_r;
    }
    explicit Node(int puzzle [N][N]){
        this->h_of_n=0;
        this->depth=0;
        this->g_of_n=0;
        copyPuzzle(puzzle);
        this->current_state= change_to_string(puzzle);
        this->child_u= nullptr;
        this->child_d= nullptr;
        this->child_l= nullptr;
        this->child_r= nullptr;
    }
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
    //This will copy the puzzle into the node class.
    void copyPuzzle(int puzzle[N][N]){
        copy(&puzzle[0][0],&puzzle[0][0]+ N*N,&nodePuzzle[0][0]);
    }
    int getF_of_N() const{
        return (this->g_of_n+this->h_of_n);
    }
    static string change_to_string(int puzzle[N][N]){
        string output;
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                output.push_back(puzzle[i][j]+'0');
            }
        }
        return output;
    }
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
    void setF_of_N(int heuristic){
        if(heuristic==1){
            this->h_of_n=0;
        }
        else if(heuristic==2){
            this->h_of_n=misplaced();
        }
    }
    int misplaced(){
        int total_count=0;
        for(int i=0; i<goal_state.size();i++){
            if((this->current_state[i] != goal_state[i]) && this->current_state[i]!=0){
                total_count++;
            }
        }
        return total_count;
    }
    void move_up() {
        int array[N][N];
        int i, j = 0;
        find_zero(this->nodePuzzle, i, j);
        swap(this->nodePuzzle[i][j], this->nodePuzzle[i - 1][j]);
        this->current_state= change_to_string(this->nodePuzzle);
    }
    void move_down(){
        int i,j=0;
        find_zero(this->nodePuzzle,i,j);
        swap(this->nodePuzzle[i][j],this->nodePuzzle[i+1][j]);
        this->current_state= change_to_string(this->nodePuzzle);
    }
    void move_left(){
        int i,j=0;
        find_zero(this->nodePuzzle,i,j);
        swap(this->nodePuzzle[i][j],this->nodePuzzle[i][j-1]);
        this->current_state= change_to_string(this->nodePuzzle);
    }
    void move_right(){
        int i,j=0;
        find_zero(this->nodePuzzle,i,j);
        swap(this->nodePuzzle[i][j],this->nodePuzzle[i][j+1]);
        this->current_state= change_to_string(this->nodePuzzle);
    }

};


#endif //EIGHT_PUZZLE_NODE_H

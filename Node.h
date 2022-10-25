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
    }
    Node(int puzzle[N][N]){
        h_of_n=0;
        depth=0;
        g_of_n=0;
        copyPuzzle(puzzle);
        current_state= change_to_string(puzzle);
    }
    Node operator =(Node &rhs){
        this->depth=rhs.depth;
        copy(&this->nodePuzzle[0][0],&this->nodePuzzle[0][0]+ N*N,&rhs.nodePuzzle[0][0]);
        this->h_of_n=rhs.h_of_n;
        this->g_of_n=rhs.g_of_n;
        this->current_state=rhs.current_state;

    }
    int nodePuzzle [N][N];
    Node *parent;
    int h_of_n;
    int depth;
    int g_of_n;
    string current_state;
    //--------------------------Functions--------------------------------
    //This will copy the puzzle into the node class.
    void copyPuzzle(int puzzle[N][N]){
        copy(&puzzle[0][0],&puzzle[0][0]+ N*N,&nodePuzzle[0][0]);
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
};


#endif //EIGHT_PUZZLE_NODE_H

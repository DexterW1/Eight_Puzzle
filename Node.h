//
// Created by Dexter on 10/23/2022.
//

#ifndef EIGHT_PUZZLE_NODE_H
#define EIGHT_PUZZLE_NODE_H
#include <iostream>
#include "bits/stdc++.h"
using namespace std;
const int N=3;
class Node {
public:
    Node(){
        h_of_n =0;
        depth = 0;
        g_of_n = 0;
    }
    Node(int puzzle[N][N]){
        h_of_n=0;
        depth=0;
        g_of_n=0;
        copyPuzzle(puzzle);
    }
    int nodePuzzle [N][N];
    int h_of_n;
    int depth;
    int g_of_n;
    vector<pair<int,int>> findEmpty;

    //--------------------------Functions--------------------------------
    //This will copy the puzzle into the node class.
    void copyPuzzle(int puzzle[N][N]){
        copy(&puzzle[0][0],&puzzle[0][0]+ N*N,&nodePuzzle[0][0]);
    }
    //Used to find the zero and passes the row and col back by reference
    bool find_zero(int& row, int& col){
        for(int i=0; i<N; i++){
            for(int j=0; j<N;j++){
                if(nodePuzzle[i][j]==0){
                    row=i;
                    col=j;
                    return true;
                }
            }
        }
        return false;
    }
    //swaps the zero to the one above
    void move_up(){
        int i,j=0;
        find_zero(i,j);
        swap(nodePuzzle[i][j],nodePuzzle[i-1][j]);
    }
    //swaps the zero to the one below
    void move_down(){
        int i,j=0;
        find_zero(i,j);
        swap(nodePuzzle[i][j],nodePuzzle[i+1][j]);
    }
    //swaps the zero to the one on the left
    void move_left(){
        int i,j=0;
        find_zero(i,j);
        swap(nodePuzzle[i][j],nodePuzzle[i][j-1]);
    }
    //swaps the zero to the one on the right
    void move_right(){
        int i,j=0;
        find_zero(i,j);
        swap(nodePuzzle[i][j],nodePuzzle[i][j+1]);
    }

};


#endif //EIGHT_PUZZLE_NODE_H

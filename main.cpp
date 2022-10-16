#include <iostream>
#include "bits/stdc++.h"
#include <algorithm>
using namespace std;
//Global Variables
const int N=3;
int user_puzzle[N][N];

//Quick Test puzzles
int trivial [N][N]= {{1,2,3},
                     {4,5,6},
                     {7,8,0}};

int veryEasy[N][N]={{1,2,3},
                    {4,5,6},
                    {7,0,8}};

int easy[N][N]{{1,2,0},
               {4,5,3},
               {7,8,6}};

int doable[N][N]{{0,1,2},
                 {4,5,3},
                 {7,8,6}};

int oh_boy[N][N]{{8,7,1},
                 {6,0,2},
                 {5,4,3}};

int impossible[N][N]{{8,6,7},
                 {2,5,4},
                 {3,0,1}};

int eight_goal_state[N][N]{{1,2,3},
                           {4,5,6},
                           {7,8,0}};

void print_intro(){
    cout<<"Welcome to my 8-Puzzle Solver. Type '1'to use a default puzzle, or '2' to create your own."<<endl;
}
void print_CreateOwn(){
    cout<<"Enter your puzzle, using a zero to represent a blank. Please only enter\nvalid 8-puzzles. Enter the puzzle demilimiting the numbers  with a space. Type\n"
          "RETURN only when finished."<<endl;
}
void print_SelectAlgo(){
    cout<<"Select Algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) the Manhattan Distance Heuristic."<<endl;
}
void print_Puzzle(int puzzle[N][N]){
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            if(j==0){
                cout<<"[";
            }
            cout<<puzzle[i][j];
            if(j==2){
                cout<<"]";
            }
            else{
                cout<<",";
            }
        }
        cout<<endl;
    }
}
void init_default_puzzle(){
    int choice;
    cout<<"You wish to use a default puzzle. Please enter a desired difficulty on a scale from 0 to 5."<<endl;
    cin>>choice;
    if(choice == 0){
        copy(&trivial[0][0],&trivial[0][0]+ N*N,&user_puzzle[0][0]);
    }
    else if(choice == 1){
        copy(&veryEasy[0][0],&veryEasy[0][0]+ N*N,&user_puzzle[0][0]);
    }
    else if(choice == 2){
        copy(&easy[0][0],&easy[0][0]+ N*N,&user_puzzle[0][0]);
    }
    else if(choice == 3){
        copy(&doable[0][0],&doable[0][0]+ N*N,&user_puzzle[0][0]);
    }
    else if(choice == 4){
        copy(&oh_boy[0][0],&oh_boy[0][0]+ N*N,&user_puzzle[0][0]);
    }
    else if(choice == 5){
        copy(&impossible[0][0],&impossible[0][0]+ N*N,&user_puzzle[0][0]);
    }
    else{
        cout<<"Error Not a valid number \n";
    }
}
int main() {
    int puzzle_mode =0;
    string puzzle_row_one, puzzle_row_two,puzzle_row_three;
    print_intro();
    cin>>puzzle_mode;
    if(puzzle_mode==1){
        init_default_puzzle();
    }
    if(puzzle_mode==2){
        print_CreateOwn();
        cin.ignore();
        cout<<"Enter the first row: ";
        getline(cin,puzzle_row_one);
        cout<<endl;
        cout<<"Enter the second row: ";
        getline(cin,puzzle_row_two);
        cout<<endl;
        cout<<"Enter the three row: ";
        getline(cin,puzzle_row_three);
        cout<<endl;
        for(int i=0; i<N;i++){
            for(int j=0;j<N;j++){
                if(i==0) {
                    remove(puzzle_row_one.begin(),puzzle_row_one.end(),' ');
                    user_puzzle[i][j] = puzzle_row_one[j] - '0';
                }
                else if(i==1){
                    remove(puzzle_row_two.begin(),puzzle_row_two.end(),' ');
                    user_puzzle[i][j] = puzzle_row_two[j] - '0';
                }
                else if(i==2){
                    remove(puzzle_row_three.begin(),puzzle_row_three.end(),' ');
                    user_puzzle[i][j] = puzzle_row_three[j] - '0';
                }
            }
        }
    }
    print_Puzzle(user_puzzle);
}
//How to copy array to another
//copy(&trivial[0][0],&trivial[0][0]+ N*N,&user_puzzle[0][0]);
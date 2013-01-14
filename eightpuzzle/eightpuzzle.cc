/*
Sam Lee
860957929
Project1: eight_puzzle.H
*/

#include "eight_puzzle.H"
#include <vector>
#include <iostream>

using namespace std;


int main(){
  
  int choice=0;
  eight_puzzle puzzle;
  //initial UI asking for puzzle choice
  cout<<"Sam Lee's 8 puzzle solver"<<endl<<endl
      <<"Choice:"<<endl
      <<"1 : default puzzle"<<endl
      <<"2 : create your own puzzle"<<endl<<endl;
  
  cin>>choice;

  if(choice==1){
    puzzle.premade_puzzle();
  }
  else{
    puzzle.make_puzzle();
  }
  
  //UI for search choice
  cout<<"Enter your choice of algorithm:"<<endl
      <<"1. Uniform Cost Search"<<endl
      <<"2. A* with the Misplaced Tile Heuristic"<<endl
      <<"3. A* with the Manhattan distance Heuristic"<<endl<<endl;

  cin>>choice;

  if(choice==1){
    puzzle.uniform_search();
  }
  else if(choice==2){
    puzzle.misplaced_search();
  }
  else if(choice==3){
    puzzle.man_search();
  }
}




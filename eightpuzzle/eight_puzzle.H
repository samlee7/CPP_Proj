/*
Sam Lee
860957929
Project1: eight_puzzle.H
*/

#ifndef __EIGHT_PUZZLE_H__
#define __EIGHT_PUZZLE_H__

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
#include <cmath>
#include "priority_queue.H"

using namespace std;

class eight_puzzle{
  int zero;
  vector<int> puzzle;

public:
  //function to create user created puzzle
  void  make_puzzle(){
    cout<<"Enter your puzzle with 0 representing blank"<<endl;
    cout<<"Example: 0 1 2 3 4 5 6 7 8"<<endl 
        <<"0 will be at top left"<<endl
        <<"8 will be at bottom right"<<endl;
    int input=0;
    int count=0;
    while(count<9){
      cin>>input;
      if(input==0) zero=count;
      puzzle.push_back(input);
      count++;
    }
  }

  void premade_puzzle(){
    puzzle.push_back(0);
    puzzle.push_back(6);
    puzzle.push_back(7);
    puzzle.push_back(8);
    puzzle.push_back(1);
    puzzle.push_back(4);
    puzzle.push_back(3);
    puzzle.push_back(2);
    puzzle.push_back(5);
    zero=8; 
  } 
 
  //move 0 up
  vector<int> move_up(vector<int> pz){ 
    int zloc=get_zero(pz);
    int store=pz[zloc-3];
    pz[zloc-3]=0;
    pz[zloc]=store;
    return pz;
  }

  //move 0 down
  vector<int> move_down(vector<int> pz){
    int zloc=get_zero(pz);
    int store=pz[zloc+3];
    pz[zloc+3]=0;
    pz[zloc]=store;
    return pz;
  }

  //move 0 right
  vector<int> move_right(vector<int> pz){
    int zloc=get_zero(pz);
    int store=pz[zloc+1];
    pz[zloc+1]=0;
    pz[zloc]=store;
    return pz;
  }

  //move 0 left
  vector<int> move_left(vector<int> pz){
    int zloc=get_zero(pz);
    int store=pz[zloc-1];
    pz[zloc-1]=0;
    pz[zloc]=store;
    return pz;
  }

  //This function checks if the puzzle is a solution
  bool check_puzzle(vector<int> pz){
    for(int i=0; i<8; i++){
      if(pz[i]!=i+1) return false;
    }
    return true;
  }

  void print(vector<int> pz){
    for(int i=0; i<9; i=i+3){
      cout<<pz[i]<<" "<<pz[i+1]<<" "<<pz[i+2]<<endl;
    }
  }

  //This function finds the 0 location in the puzzle
  int get_zero(vector<int> puzzle){
    for(int i=0; i<9; i++){
      if(puzzle[i]==0) return i;
    }
  }
  
  //misplaced tile heuristic
  int mt_h(vector<int> pz) {
    int ret=0;
    for(int i=0; i<8; i++){
      if(pz[i]!=i+1) ret++;
    }
    if(pz[8]!=0) ret++;
    return ret;
  }
  
  //manhattan heuristic
  int man_h(vector<int> pz) {
    int ret=0;
    int find=0;
    for(int i=0; i<9; i++){
      if(pz[i]==0) pz[i]=9;
    }

    for(int i=1; i<10; i++){
      for(int j=0;j<9;j++){
        if(pz[j]==i) find=j;
      }
    find++;
    //if distance between find and i is a certain number
    //it is x distance from right spot.
    if(abs(find-i)==3) ret+=1; 
    else if(abs(find-i)==0) ret+=0; 
    else if(abs(find-i)==6) ret+=2;
    else if(abs(find-i)==5) ret+=3; 
    else if(abs(find-i)==7) ret+=3; 
    else if(abs(find-i)==8) ret+=4; 
    else if(abs(find-i)==2) ret+=2; 
    else if((i==3 && find==4)||(i==4 && find==3)) ret+=3;
    else if((i==6 && find==7)||(i==7 && find==6)) ret+=3; 
    else if((i==3 && find==7)||(i==7 && find==3)) ret+=4; 
    else if(abs(find-i)==4) ret+=2; 
    else ret+=1; 
 

    }
    return ret;
  }

  void uniform_search(){
    priority_queue< vector<int> > pq;
    //map to keep track of distance from starting node
    map<vector<int>,int> dist;

    //initial state
    dist[puzzle]=0;
    pq.push(puzzle,0);
    cout<<"Expanding state:" <<endl;
    print(puzzle);
    vector<int> top;
    int expanded=0;
    int maxq=0;
 
    while(!pq.empty()){
      top=pq.top();
      cout<<"Current puzzle:"<<endl;
      print(top);

      cout<<"g(n): "<<dist[top]<<endl;
      //check if top is a solution
      if(check_puzzle(top)==true){
        cout<<"Solution is found"<<endl;
        cout<<"Expanded: "<<expanded<<" nodes"<<endl;
        cout<<"Max queue size: "<<maxq<<endl;
        cout<<"Depth of the solution: "<<dist[top]<<endl;
        exit(0);
      }

      pq.pop();

      //for every expansion, add one to distance 
      //then push it on to the queue
      switch(get_zero(top)) {
        case 0:
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          pq.push(move_right(top),dist[move_right(top)]);
          expanded+=2;
          break;
        case 1:
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          pq.push(move_right(top),dist[move_right(top)]);
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]);
          expanded+=3;
          break;
        case 2:
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]);
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]);
          expanded+=2;
          break;
        case 3:
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          pq.push(move_right(top),dist[move_right(top)]);
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]);
          expanded+=3;
          break;
        case 4:
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          pq.push(move_right(top),dist[move_right(top)]);
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]);
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]);
          expanded+=4;
          break;
        case 5:
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]);
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]);
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]);
          expanded+=3;
          break;
        case 6:
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]);
          dist[move_right(top)]=dist[top]+1;
          pq.push(move_right(top),dist[move_right(top)]);
          expanded+=2;
          break;
        case 7:
          dist[move_right(top)]=dist[top]+1;
          pq.push(move_right(top),dist[move_right(top)]);
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]);
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]);
          expanded+=3;
          break;
        case 8:
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]);
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]);
          expanded+=2;
          break;
      }

      if(pq.size()>maxq) maxq=pq.size();
     
    }
    cout<<"failure: queue empty"<<endl;
    exit(0);
  }

  void misplaced_search(){
    priority_queue< vector<int> > pq;
    //map to keep track of distance from starting node
    //and the heuristics
    map<vector<int>,int> dist;
    map<vector<int>,int> hlist;
    dist[puzzle]=0;
    //h(n) uses misplaced tile heuristic
    hlist[puzzle]=mt_h(puzzle);
    pq.push(puzzle,0+hlist[puzzle]);
    cout<<"Expanding state:" <<endl;
    print(puzzle);
    vector<int> top;
    int expanded=0;
    int maxq=0;
 
    while(!pq.empty()){
      top=pq.top();
      cout<<"Current puzzle:"<<endl;
      print(top);

      cout<<"g(n): "<<dist[top]<<endl;
      cout<<"h(n): "<<hlist[top]<<endl;
      //check solution
      if(check_puzzle(top)==true){
        cout<<"Solution is found"<<endl;
        cout<<"Expanded: "<<expanded<<" nodes"<<endl;
        cout<<"Max queue size: "<<maxq<<endl;
        cout<<"Depth of the solution: "<<dist[top]<<endl;
        exit(0);
      }

      pq.pop();

      //dist is now g(n)+h(n) with mt_h
      switch(get_zero(top)) {
        case 0:
          hlist[move_down(top)]=mt_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=mt_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          expanded+=2;
          break;
        case 1:
          hlist[move_down(top)]=mt_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=mt_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_left(top)]=mt_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          expanded+=3;
          break;
        case 2:
          hlist[move_down(top)]=mt_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          hlist[move_left(top)]=mt_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          expanded+=2;
          break;
        case 3:
          hlist[move_down(top)]=mt_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=mt_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_up(top)]=mt_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=3;
          break;
        case 4:
          hlist[move_down(top)]=mt_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=mt_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_left(top)]=mt_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          hlist[move_up(top)]=mt_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=4;
          break;
        case 5:
          hlist[move_down(top)]=mt_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          hlist[move_left(top)]=mt_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          hlist[move_up(top)]=mt_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=3;
          break;
        case 6:
          hlist[move_up(top)]=mt_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=mt_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          expanded+=2;
          break;
        case 7:
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=mt_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_left(top)]=mt_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          hlist[move_up(top)]=mt_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=3;
          break;
        case 8:
          hlist[move_up(top)]=mt_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          hlist[move_left(top)]=mt_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          expanded+=2;
          break;
      }
      if(pq.size()>maxq) maxq=pq.size();
     
    }
    cout<<"failure: queue empty"<<endl;
    exit(0);
  }

  void man_search(){
    priority_queue< vector<int> > pq;
    //map to keep track of distance from starting node
    //and the heuristics
    map<vector<int>,int> dist;
    map<vector<int>,int> hlist;
    dist[puzzle]=0;
    //h(n) uses manhattan distance
    hlist[puzzle]=man_h(puzzle);
    pq.push(puzzle,0+hlist[puzzle]);
    cout<<"Expanding state:" <<endl;
    print(puzzle);
    vector<int> top;
    int expanded=0;
    int maxq=0;
 
    while(!pq.empty()){
      top=pq.top();
      cout<<"Current puzzle:"<<endl;
      print(top);

      cout<<"g(n): "<<dist[top]<<endl;
      cout<<"h(n): "<<hlist[top]<<endl;
      if(check_puzzle(top)==true){
        cout<<"Solution is found"<<endl;
        cout<<"Expanded: "<<expanded<<" nodes"<<endl;
        cout<<"Max queue size: "<<maxq<<endl;
        cout<<"Depth of the solution: "<<dist[top]<<endl;
        exit(0);
      }

      pq.pop();

      //dist is now g(n)+h(n) with man_h
      switch(get_zero(top)) {
        case 0:
          hlist[move_down(top)]=man_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=man_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          expanded+=2;
          break;
        case 1:
          hlist[move_down(top)]=man_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=man_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_left(top)]=man_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          expanded+=3;
          break;
        case 2:
          hlist[move_down(top)]=man_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          hlist[move_left(top)]=man_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          expanded+=2;
          break;
        case 3:
          hlist[move_down(top)]=man_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=man_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_up(top)]=man_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=3;
          break;
        case 4:
          hlist[move_down(top)]=man_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=man_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_left(top)]=man_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          hlist[move_up(top)]=man_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=4;
          break;
        case 5:
          hlist[move_down(top)]=man_h(move_down(top));
          dist[move_down(top)]=dist[top]+1;
          pq.push(move_down(top),dist[move_down(top)]+hlist[move_down(top)]);
          hlist[move_left(top)]=man_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          hlist[move_up(top)]=man_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=3;
          break;
        case 6:
          hlist[move_up(top)]=man_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=man_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          expanded+=2;
          break;
        case 7:
          dist[move_right(top)]=dist[top]+1;
          hlist[move_right(top)]=man_h(move_right(top));
          pq.push(move_right(top),dist[move_right(top)]+hlist[move_right(top)]);
          hlist[move_left(top)]=man_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          hlist[move_up(top)]=man_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          expanded+=3;
          break;
        case 8:
          hlist[move_up(top)]=man_h(move_up(top));
          dist[move_up(top)]=dist[top]+1;
          pq.push(move_up(top),dist[move_up(top)]+hlist[move_up(top)]);
          hlist[move_left(top)]=man_h(move_left(top));
          dist[move_left(top)]=dist[top]+1;
          pq.push(move_left(top),dist[move_left(top)]+hlist[move_left(top)]);
          expanded+=2;
          break;
      }
      if(pq.size()>maxq) maxq=pq.size();
    
    }
    cout<<"failure: queue empty"<<endl;
    exit(0);
    
  }


};

#endif
